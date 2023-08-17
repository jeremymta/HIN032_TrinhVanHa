#pragma once
#include "../Utilities/utilities.h"

//Dinh nghia 2 enum Camera_Movement va Camera_Rotate cho cac kieu di chuyen va xoay Camera
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
enum Camera_Rotate {
	xAxis,
	yAxis,
	zAxis
};

class Camera
{
public:
	//Constructor khoi tao tat ca cac trang thai ban dau can thiet cho camera hoat dong.
	Camera(Vector3 Postiton = Vector3(0.f, 0.f, -5.f), Vector3 Target = Vector3(0, 0, 0));

	//Lay cac ma tran bien doi
	Matrix GetWorldMatrix();
	Matrix GetViewMatrix();
	Matrix GetPerspectiveMatrix();

	//Vi tri va diem nhin nhin Camera
	Vector3 m_cameraPos;
	Vector3 m_cameraTarget;

	//Toc do di chuyen va xoay
	float  m_MoveSpeed, m_RotateSpeed;

	Matrix RotateAroundY(float angle); //Xoay Camera quanh truc Y 
	Vector3 zAxis, xAxis, yAxis; //Cac vector truc

private:

	Matrix m_PerspectiveMatrix; //Ma tran perspective
	//Cac tham so tinh toan perspective
	float m_FovY;
	float m_AspectRatio;
	float m_Near;

	float m_Far;

public:
	void UpdateCameraVector(); //Cap nhap cac vector truc

	//Xoay Camera
	void RotateClockWise(Camera_Rotate rot, float deltaTime);
	void RotateCounterClockWise(Camera_Rotate rot, float deltaTime);

	//Di chuyen Camera
	void Move(Camera_Movement direction, float deltaTime);

};

