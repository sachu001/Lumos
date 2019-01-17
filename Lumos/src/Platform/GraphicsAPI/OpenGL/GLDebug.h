#pragma once
#include "LM.h"
#include "GLRenderer.h"
#include "GL.h"
 //for crash()

namespace Lumos
{
	class Material;

	static const float biasValues[16] =
	{
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	};
	static const maths::Matrix4 biasMatrix(const_cast<float*>(biasValues));

	enum DebugDrawMode
	{
		DEBUGDRAW_ORTHO,
		DEBUGDRAW_PERSPECTIVE
	};

	struct DebugDrawData
	{
		std::vector<maths::Vector3> lines;
		std::vector<maths::Vector3> colours;

		uint array;
		uint buffers[2];

		DebugDrawData();
		void Draw();

		~DebugDrawData()
		{
			glDeleteVertexArrays(1, &array);
			glDeleteBuffers(2, buffers);
		}

		inline void Clear()
		{
			lines.clear();
			colours.clear();
		}

		inline void AddLine(const maths::Vector3 &from, const maths::Vector3 &to, const maths::Vector3 &fromColour, const maths::Vector3 &toColour)
		{
			lines.push_back(from);
			lines.push_back(to);

			colours.push_back(fromColour);
			colours.push_back(toColour);
		}
	};

	class GLDebug
	{
	public:
		GLDebug();
		~GLDebug();

		static void SwapBuffers();
		static void	DrawDebugLine(DebugDrawMode mode, const maths::Vector3 &from, const maths::Vector3 &to, const maths::Vector3 &fromColour = maths::Vector3(1, 1, 1), const maths::Vector3 &toColour = maths::Vector3(1, 1, 1));
		static void	DrawDebugBox(DebugDrawMode mode, const maths::Vector3 &at, const maths::Vector3 &scale, const maths::Vector3 &colour = maths::Vector3(1, 1, 1));
		static void	DrawDebugCross(DebugDrawMode mode, const maths::Vector3 &at, const maths::Vector3 &scale, const maths::Vector3 &colour = maths::Vector3(1, 1, 1));
		static void	DrawDebugCircle(DebugDrawMode mode, const maths::Vector3 &at, const float radius, const maths::Vector3 &colour = maths::Vector3(1, 1, 1));

		static void DrawDebugPerspective(maths::Matrix4* matrix = nullptr);
		static void DrawDebugOrtho(maths::Matrix4* matrix = nullptr);

		static DebugDrawData* s_OrthoDebugData;
		static DebugDrawData* s_PerspectiveDebugData;
		static bool	s_DrawnDebugOrtho;
		static bool	s_DrawnDebugPerspective;

		static GLRenderer*	s_DebugDrawingRenderer;
		static Material*	s_DebugDrawShader;
	};

#ifdef LUMOS_DEBUG
#ifdef glDebugMessageCallback
//#define GL_DEBUD_CALLBACK 1
#else
#define GL_DEBUG 1
#endif
#endif

#define OPENGLLOG "[OPENGL] - "

	static bool GLLogCall(const char* function, const char* file, const int32 line)
	{
		GLenum err(glGetError());
		bool Error = true;
		while (err != GL_NO_ERROR)
		{
			std::string error;

			switch (err) {
				case GL_INVALID_OPERATION:
					error = "INVALID_OPERATION";
					break;
				case GL_INVALID_ENUM:
					error = "INVALID_ENUM";
					break;
				case GL_INVALID_VALUE:
					error = "INVALID_VALUE";
					break;
				case GL_OUT_OF_MEMORY:
					error = "OUT_OF_MEMORY";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					error = "INVALID_FRAMEBUFFER_OPERATION";
					break;
				default:;
			}

			std::cerr << "GL_" << error.c_str() << " - " << file << " - " << function << ":" << line << std::endl;
			Error = false;
			err = glGetError();
		}
			return Error;
	}

	static void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}


}

#if GL_DEBUG
#define GLCall(x) GLClearError();\
		x; \
		if (!GLLogCall(#x, __FILE__, __LINE__)) crash();
#else
#define GLCall(x) x
#endif

