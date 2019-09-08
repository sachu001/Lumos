#include "LM.h"
#include "WindowsThread.h"

#ifdef PTHREAD_BSD_SET_NAME
#include <pthread_np.h>
#endif

namespace Lumos
{
    WindowsThread::WindowsThread(ThreadCreateCallback p_callback, void *p_user, const Settings &)
    {
        m_Callback = p_callback;
        m_User = p_user;
        m_Handle = CreateEvent(NULL, TRUE, FALSE, NULL);

	    QueueUserWorkItem(ThreadCallback, this, WT_EXECUTELONGFUNCTION);
    }   

    WindowsThread::~WindowsThread() 
    {
    }

    static void _thread_id_key_destr_callback(void *p_value) 
    {
        lmdel(static_cast<Thread::ID *>(p_value));
    }

    Thread::ID WindowsThread::GetID() const 
    {
        return m_ID;
    }

    DWORD WindowsThread::ThreadCallback(LPVOID userdata)
    {
        WindowsThread *t = reinterpret_cast<WindowsThread *>(userdata);
       
        t->m_ID = (ID)GetCurrentThreadId(); // must implement
        t->m_Callback(t->m_User);
        SetEvent(t->m_Handle);

        return 0;
    }

    Thread::ID WindowsThread::GetThreadIDFuncWindows()
    {
        return (ID)GetCurrentThreadId();
    }

    void WindowsThread::WaitToFinishFuncWindows(Thread *p_thread)
    {
        WindowsThread *tp = static_cast<WindowsThread *>(p_thread);
        //LUMOS_ASSERT(tp);
        WaitForSingleObject(tp->m_Handle, INFINITE);
        CloseHandle(tp->m_Handle);
    }

    void WindowsThread::MakeDefault() 
    {
        GetThreadIDFunc = GetThreadIDFuncWindows;
        WaitToFinishFunc = WaitToFinishFuncWindows;
        CreateFunc = CreateFuncWindows;
    }

    Thread* WindowsThread::CreateFuncWindows(ThreadCreateCallback p_callback, void *p_user, const Settings & p_settings)
    {
        return lmnew WindowsThread(p_callback, p_user, p_settings);
    }
}