#include "Precompiled.h"
#include "Sprite.h"
#include "Graphics/Material.h"
#include "Graphics/API/Texture.h"
#include "Graphics/API/GraphicsContext.h"
#include "Mesh.h"
#include "Core/Application.h"
#include "MeshFactory.h"

#ifdef LUMOS_EDITOR
#include "Editor/Editor.h"
#endif

#include <imgui/imgui.h>

namespace Lumos
{
	namespace Graphics
	{
		Sprite::Sprite(const Maths::Vector2& position, const Maths::Vector2& scale, const Maths::Vector4& colour)
		{
			m_Position = position;
			m_Scale = scale;
			m_Colour = colour;
			m_UVs = GetDefaultUVs();
			m_Texture = nullptr;
		}

		Sprite::Sprite(const Ref<Texture2D>& texture, const Maths::Vector2& position, const Maths::Vector2& scale, const Maths::Vector4& colour)
		{
            m_Texture = texture;
			m_Position = position;
			m_Scale = scale;
			m_Colour = colour;
			m_UVs = GetDefaultUVs();
		}

		Sprite::~Sprite()
		{
		}
    
        void Sprite::SetSpriteSheet(const Ref<Texture2D>& texture, const Maths::Vector2& index, const Maths::Vector2& cellSize, const Maths::Vector2& spriteSize)
        {
            m_Texture = texture;
            Maths::Vector2 min = {(index.x * cellSize.x) / texture->GetWidth() , (index.y * cellSize.y) / texture->GetHeight() };
            Maths::Vector2 max = {((index.x + spriteSize.x) * cellSize.x) / texture->GetWidth() , ((index.y+ spriteSize.y) * cellSize.y) / texture->GetHeight() };
            
            m_UVs = GetUVs(min, max);
        }
    
        void Sprite::SetTextureFromFile(const std::string& filePath)
        {
            auto tex = Ref<Graphics::Texture2D>(Graphics::Texture2D::CreateFromFile(filePath, filePath));
            if(tex)
            {
                m_Texture = tex;
            }
        }

		void Sprite::OnImGui()
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
			ImGui::Columns(2);
			ImGui::Separator();
			
			ImGui::AlignTextToFramePadding();
			ImGui::TextUnformatted("Position");
			ImGui::NextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::InputFloat2("##Position", Maths::ValuePointer(m_Position));
			
			ImGui::PopItemWidth();
			ImGui::NextColumn();
			
			ImGui::AlignTextToFramePadding();
			ImGui::TextUnformatted("Scale");
			ImGui::NextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::InputFloat2("##Scale", Maths::ValuePointer(m_Scale));
			
			ImGui::PopItemWidth();
			ImGui::NextColumn();
			
			ImGui::AlignTextToFramePadding();
			ImGui::TextUnformatted("Colour");
			ImGui::NextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::ColorEdit4("##Colour", Maths::ValuePointer(m_Colour));
			
			ImGui::PopItemWidth();
			ImGui::NextColumn();
			
			if (ImGui::TreeNode("Texture"))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
				ImGui::Columns(2);
				ImGui::Separator();
				
				bool flipImage = Graphics::GraphicsContext::GetContext()->FlipImGUITexture();
				
				ImGui::AlignTextToFramePadding();
				auto tex = m_Texture;
				
				if(tex)
				{
					if(ImGui::ImageButton(tex->GetHandle(), ImVec2(64, 64), ImVec2(0.0f, flipImage ? 1.0f : 0.0f), ImVec2(1.0f, flipImage ? 0.0f : 1.0f)))
					{
#ifdef LUMOS_EDITOR
						Application::Get().GetEditor()->GetFileBrowserWindow().Open();
						Application::Get().GetEditor()->GetFileBrowserWindow().SetCallback(std::bind(&Sprite::SetTextureFromFile, this, std::placeholders::_1));
#endif
					}
					
					if(ImGui::IsItemHovered() && tex)
					{
						ImGui::BeginTooltip();
						ImGui::Image(tex->GetHandle(), ImVec2(256, 256), ImVec2(0.0f, flipImage ? 1.0f : 0.0f), ImVec2(1.0f, flipImage ? 0.0f : 1.0f));
						ImGui::EndTooltip();
					}
				}
				else
				{
					if(ImGui::Button("Empty", ImVec2(64, 64)))
					{
#ifdef LUMOS_EDITOR
						Application::Get().GetEditor()->GetFileBrowserWindow().Open();
						Application::Get().GetEditor()->GetFileBrowserWindow().SetCallback(std::bind(&Sprite::SetTextureFromFile, this, std::placeholders::_1));
#endif
					}
				}
				
				ImGui::NextColumn();
				ImGui::PushItemWidth(-1);
				ImGui::Text("%s", tex ? tex->GetFilepath().c_str() : "No Texture");
				
				ImGui::PopItemWidth();
				ImGui::NextColumn();
				
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::PopStyleVar();
				ImGui::TreePop();
			}
			
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::PopStyleVar();
		}
	}
}
