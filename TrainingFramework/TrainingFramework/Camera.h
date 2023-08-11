#pragma once
#include "../Utilities/utilities.h"


class Camera
{
public:
	Camera(Vector3 Postiton = Vector3(0.f, 0.f, -5.f), Vector3 Target = Vector3(0, 0, 0));

	Matrix CalculateWorldMatrix();
	Matrix CalculateViewMatrix();
	Matrix GetPerspectiveMatrix();

	Matrix m_PerspectiveMatrix;
	Matrix m_InverseRotateMatrix;
	Matrix m_InverseTransformMatrix;
private:
	Vector3 m_cameraPos;
	Vector3 m_cameraTarget;

	float m_FovY;
	float m_AspectRatio;
	float m_Near;
	float m_Far;

	float  m_MoveSpeed, m_RotateSpeed;

};

