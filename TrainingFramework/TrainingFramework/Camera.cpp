#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"


Camera::Camera(Vector3 Postiton, Vector3 Target)
{
    float PI = 3.14;
    this->m_AspectRatio = Globals::screenWidth / (float)Globals::screenHeight;
    m_FovY = PI / 4;
    m_Near = 0.1f;
    m_Far = 500.f;

    this->m_cameraPos = Postiton;
    this->m_cameraTarget = Target;
    this->m_PerspectiveMatrix = m_PerspectiveMatrix.SetPerspective(m_FovY, m_AspectRatio, m_Near, m_Far);

    Vector3 zAxis = (m_cameraPos - m_cameraTarget).Normalize();
    Vector3 UP(0, 1, 0);
    Vector3 xAxis = (UP.Cross(zAxis)).Normalize();
    Vector3 yAxis = (zAxis.Cross(xAxis)).Normalize();

    Matrix Rotate;
    //Rotate.SetCameraRotateMatrix(xAxis, yAxis, zAxis);


    m_InverseRotateMatrix = Rotate.Transpose();
    m_InverseTransformMatrix.SetIdentity();
    m_InverseTransformMatrix.SetTranslation(-m_cameraPos);
}

Matrix Camera::CalculateWorldMatrix()
{
    return Matrix();
}

Matrix Camera::CalculateViewMatrix()
{
    return m_InverseTransformMatrix * m_InverseRotateMatrix;
}

Matrix Camera::GetPerspectiveMatrix()
{
    return this->m_PerspectiveMatrix;
}



