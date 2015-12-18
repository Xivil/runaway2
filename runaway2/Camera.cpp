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
	target += vector;

	km::Vector3 a = km::AnyAxis(target, position, angley, 0, 1, 0);
	unit = a - position;
	unit.Normalize();
	SetCameraPositionAndTarget_UpVecY(Vector3ToDxVector(position), Vector3ToDxVector(a));
	
	if (Keyboard_Get(KEY_INPUT_LEFT)){
		angley++;
	}
	if (Keyboard_Get(KEY_INPUT_RIGHT)){
		angley--;
	}
	if (Keyboard_Get(KEY_INPUT_UP)){
		vector = unit;
	}
	else if (Keyboard_Get(KEY_INPUT_DOWN)){
		vector = unit * -1;
	}
	
	else{
		vector *= 0;
	}

	km::PrintVector3DxLib(a, 0, 0);
	km::PrintVector3DxLib(target, 0, 30);
	km::PrintVector3DxLib(position, 0, 60);
	km::PrintVector3DxLib(unit, 0, 90);
	km::PrintVector3DxLib(direction, 0, 120);
}