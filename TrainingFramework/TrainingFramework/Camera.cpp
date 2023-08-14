#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"


Camera::Camera(Vector3 Postiton, Vector3 Target)
{
    float PI = 3.14;
    this->m_AspectRatio = Globals::screenWidth / (float)Globals::screenHeight;//Ty le khung hinh
    m_FovY = PI / 4; //Goc nhin theo chieu doc
    m_Near = 0.1f; //MP cat gan
    m_Far = 100.f;  //Mp cat xa

    m_MoveSpeed = 4.0f; //Toc do di chuyen cua camera
    m_RotateSpeed = PI / 4.f; //Toc do xoay cua camera

    //Khoi tao vi tri va diem nhin ban dau cua camera
    this->m_cameraPos = Postiton;
    this->m_cameraTarget = Target;
    
    //Tinh toan ma tran perspective tu cac tham so khai bao o tren
    this->m_PerspectiveMatrix = m_PerspectiveMatrix.SetPerspective(m_FovY, m_AspectRatio, m_Near, m_Far);

    //cap nhat cac vector truc (xAxis, yAxis, zAxis) cua camera ban đau.
    UpdateCameraVector();

}

Matrix Camera::GetWorldMatrix()
{
    //Tra ve ma tran chuyen doi tu khong gian Camera ve không gian World
    return Matrix().SetCameraWorldMatrix(xAxis, yAxis, zAxis, m_cameraPos);
}

Matrix Camera::GetViewMatrix()
{
    // Tra ve ma tran chuyen doi tu khong gian World ve khong gian View cua Camera
    return Matrix().SetCameraViewMatrix(xAxis, yAxis, zAxis, m_cameraPos);
}

Matrix Camera::GetPerspectiveMatrix()
{
    //Tra ve ma tran chieu cua Perspective cua Camera
    return this->m_PerspectiveMatrix;
}

Matrix Camera::RotateAroundY(float angle)
{
    //Tra ve ma tran xoay camera quanh truc Y voi goc (0.5f, 0, 0)
    return Matrix().SetRotationAngleAxis(angle, 0.5f, 0, 0);
}

void Camera::UpdateCameraVector()
{
    zAxis = (m_cameraPos - m_cameraTarget).Normalize();
    Vector3 UP(0, 1, 0); // Vector truc Y mac dinh
    xAxis = (UP.Cross(zAxis)).Normalize();
    yAxis = (zAxis.Cross(xAxis)).Normalize();
}

//Xoay Camera theo chieu kim dong ho quanh cac truc
void Camera::RotateClockWise(Camera_Rotate rot, float deltaTime)
{
    //Tinh goc xoay dua vao  toc do xoay va thoi gian troi qua
    float angle = deltaTime * m_RotateSpeed;
    //Xac dinh truc can xoay dua vao tham so rot
    switch (rot) 
    {
        // Xoay quanh truc X
    case Camera_Rotate::xAxis:  
    {
        //Lay vecto diem tu toa do Local
        Vector4 localTarget = Vector4(0.f, 0.f, -(m_cameraTarget - m_cameraPos).Length(), 1.f);
        //Xoay localTarget quanh truc X voi goc angle
        Vector4 localNewTarget = localTarget * Matrix().SetRotationAngleAxis(angle, xAxis.x, xAxis.y, xAxis.z);
        //Chuyen tu local sang toa do world
        Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
        //Cap nhat lai toa do world
        m_cameraTarget = Vector3(worldNewTarget[0], worldNewTarget[1], worldNewTarget[2]);
        //Cap nhat la camera target
        m_cameraTarget.Display();
    }
    break;
    case Camera_Rotate::yAxis:
    {
        Vector4 localTarget = Vector4(0.f, 0.f, -(m_cameraTarget - m_cameraPos).Length(), 1.f);
        Vector4 localNewTarget = localTarget * Matrix().SetRotationAngleAxis(-angle, yAxis.x, yAxis.y, yAxis.z);
        Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
        m_cameraTarget = Vector3(worldNewTarget[0], worldNewTarget[1], worldNewTarget[2]);
    }
    break;
    case Camera_Rotate::zAxis:
    {
        Vector4 localTarget = Vector4(0.f, 0.f, -(m_cameraTarget - m_cameraPos).Length(), 1.f);
        Vector4 localNewTarget = localTarget * Matrix().SetRotationAngleAxis(angle, zAxis.x, zAxis.y, zAxis.z);
        Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
        m_cameraTarget = Vector3(worldNewTarget[0], worldNewTarget[1], worldNewTarget[2]);
    }
    break;
    default:
        break;
    }

}

//Xoay Camera theo chieu nguoc kim dong ho quanh cac truc
void Camera::RotateCounterClockWise(Camera_Rotate rot, float deltaTime)
{
    float angle = deltaTime * m_RotateSpeed;
    switch (rot)
    {
    case Camera_Rotate::xAxis:
    {
        Vector4 localTarget = Vector4(0.f, 0.f, -(m_cameraTarget - m_cameraPos).Length(), 1.f);
        Vector4 localNewTarget = localTarget * Matrix().SetRotationAngleAxis(-angle, xAxis.x, xAxis.y, xAxis.z);
        Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
        m_cameraTarget = Vector3(worldNewTarget[0], worldNewTarget[1], worldNewTarget[2]);
    }
    break;
    case Camera_Rotate::yAxis:
    {
        Vector4 localTarget = Vector4(0.f, 0.f, -(m_cameraTarget - m_cameraPos).Length(), 1.f);
        Vector4 localNewTarget = localTarget * Matrix().SetRotationAngleAxis(angle, yAxis.x, yAxis.y, yAxis.z);
        Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
        m_cameraTarget = Vector3(worldNewTarget[0], worldNewTarget[1], worldNewTarget[2]);
    }
    break;
    case Camera_Rotate::zAxis:
    {
        Vector4 localTarget = Vector4(0.f, 0.f, -(m_cameraTarget - m_cameraPos).Length(), 1.f);
        Vector4 localNewTarget = localTarget * Matrix().SetRotationAngleAxis(angle, zAxis.x, zAxis.y, zAxis.z);
        Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
        m_cameraTarget = Vector3(worldNewTarget[0], worldNewTarget[1], worldNewTarget[2]);
    }
    break;
    default:
        break;
    }
}


//Di chuyen Camera va diem nhin dua theo cac vector truc va van toc tinh duoc
void Camera::Move(Camera_Movement direction, float deltaTime) 
{
    //Tinh van toc dua tren toc do di chuyen va thoi gian
    float velocity = m_MoveSpeed * deltaTime;
    //Xac dinh huong di chuyen dua vao tham so direction
    switch (direction)
    {
        //Di chuyen ve phia truoc
    case FORWARD:
    {
        //Cap nhat vi tri va diem nhin camera dua tren truc Z
        m_cameraPos -= zAxis * velocity;
        m_cameraTarget -= zAxis * velocity;
    }
    break;
    case BACKWARD:
    {
        m_cameraPos += zAxis * velocity;
        m_cameraTarget += zAxis * velocity;
    }
    break;
    case LEFT:
    {
        m_cameraPos -= xAxis * velocity;
        m_cameraTarget -= xAxis * velocity;
    }
    break;
    case RIGHT:
    {
        m_cameraPos += xAxis * velocity;
        m_cameraTarget += xAxis * velocity;
    }
    break;
    default: break;
    }

}







