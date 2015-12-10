#include "Camera.h"

Camera::Camera(){
	position =  VGet(0, 5, -10);
	target = VGet(0, 0, 0);
	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.1f, 1000.0f);
}

void Camera::SetPosition(VECTOR a){
	position = a;
}

void Camera::SetTarget(VECTOR a){
	target = a;
}

void Camera::UseCamera(){
	
	//(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(position, target);
}