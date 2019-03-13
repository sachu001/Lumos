#include "LM.h"
#include "Transform.h"

namespace Lumos
{
	namespace maths
	{
		Transform::Transform()
		{
			m_LocalScale = Vector3(1, 1, 1);
		}

		Transform::Transform(const Matrix4& matrix)
		{
			m_LocalMatrix = matrix;
			m_WorldMatrix = matrix;
		}

		Transform::Transform(const Vector3& position) 
		{
			SetWorldPosition(position);
		}

		Transform::~Transform()
		{
		}

		void Transform::UpdateMatrices() 
		{
			m_LocalMatrix = Matrix4::Translation(m_LocalPosition) * m_Orientation.ToMatrix4() * Matrix4::Scale(m_LocalScale);
			m_WorldMatrix = m_LocalMatrix;
		}

		void Transform::SetWorldPosition(const Vector3& worldPos) 
		{
			m_LocalPosition = worldPos;
		}

		void Transform::SetLocalPosition(const Vector3& localPos)
		{
			m_LocalPosition = localPos;
		}

		void Transform::SetWorldScale(const Vector3& worldScale) 
		{
			m_LocalScale = worldScale;
		}

		void Transform::SetLocalScale(const Vector3& newScale)
		{
			m_LocalScale = newScale;
		}
	}
}