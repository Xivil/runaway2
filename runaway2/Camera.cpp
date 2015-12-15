#include "Camera.h"
#include "Func.h"
#include "Quaternion.h"
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
	static float angley = 0;
	position += vector;
	direction.Normalize();
	unit = target - position;
	unit.Normalize();
	//target = position + unit;
	target = km::AnyAxis(target, position, 1,0, 1, 0 );
	SetCameraPositionAndTarget_UpVecY(Vector3ToDxVector(position), Vector3ToDxVector(target));
	//SetCameraPositionAndAngle(Vector3ToDxVector(position), 0, DEG_TO_RAD(angley), 0);
	
	if (Keyboard_Get(KEY_INPUT_LEFT)){
		
		//direction += km::GetVector3(-0.1, 0, -0.1);
		
	}
	if (Keyboard_Get(KEY_INPUT_RIGHT)){
		//direction += km::GetVector3(0.1, 0, 0.1);
	}
	if (Keyboard_Get(KEY_INPUT_UP)){
		vector = unit;
	}
	else{
		vector *= 0;
	}
	DrawFormatString(0, 0, GetColor(255,255,255), "%f, %f, %f", angley, unit.y, unit.z);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "%f, %f, %f", unit.x, unit.y, unit.z);
}