#pragma once
#include "DxLib.h"
class Camera{
private:
	VECTOR position;
	VECTOR target;
public:
	Camera();
	~Camera(){}
	void SetPosition(VECTOR a);
	void SetTarget(VECTOR a);
	void UseCamera();
};