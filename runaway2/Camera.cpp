#include "Camera.h"
#include "Func.h"
Camera::Camera(){
	position = km::GetVector3(0, 3, 0);
	target = km::GetVector3(0, 3, 5);
	//âúçs0.1Å`1000Ç‹Ç≈ÇÉJÉÅÉâÇÃï`âÊîÕàÕÇ∆Ç∑ÇÈ
	SetCameraNearFar(0.1f, 1000.0f);
	unit = km::GetVector3(0, 0, 1);
	direction = km::GetVector3(0, 0, 10);
}

void Camera::SetPosition(km::Vector3& a){
	position = a;
}

void Camera::SetTarget(km::Vector3& a){
	target = a;
}

void Camera::UseCamera(){
	position += vector;
	direction.Normalize();
	unit = direction;
	target = position + unit;
	SetCameraPositionAndTarget_UpVecY(Vector3ToDxVector(position), Vector3ToDxVector(target));
	if (Keyboard_Get(KEY_INPUT_LEFT)){
		
		direction += km::GetVector3(-0.1, 0, -0.1);
		
	}
	if (Keyboard_Get(KEY_INPUT_RIGHT)){
		direction += km::GetVector3(0.1, 0, 0.1);
	}
	if (Keyboard_Get(KEY_INPUT_UP)){
		vector = unit;
	}
	else{
		vector *= 0;
	}
	DrawFormatString(0, 0, GetColor(255,255,255), "%f, %f, %f", unit.x, unit.y, unit.z);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "%f, %f, %f", direction.x, unit.y, direction.z);
}