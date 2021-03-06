#pragma once
#include "VECTOR.h"
#include "MATRIX.h"
class Camera{
private:
	km::Vector3 position;
	km::Vector3 target;
	km::Vector3 unit;
	km::Vector3 vector;
	km::Vector3 direction;
	float AngleH;
	float AngleV;
	unsigned char flag;
public:
	Camera();
	virtual ~Camera(){}
	void SetPosition(const km::Vector3& a);
	void SetTarget(const km::Vector3& a);
	void UseCamera();
};