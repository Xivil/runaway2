#include "Camera.h"

Camera::Camera(){
	position =  VGet(0, 5, -10);
	target = VGet(0, 0, 0);
	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 1000.0f);
}

void Camera::SetPosition(VECTOR a){
	position = a;
}

void Camera::SetTarget(VECTOR a){
	target = a;
}

void Camera::UseCamera(){
	
	//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(position, target);
}