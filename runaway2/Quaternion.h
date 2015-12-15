#pragma once
#include <math.h>
#include "VECTOR.h"
namespace km
{


	struct quaternion{
		float t;
		km::Vector3 V;
	};

	quaternion Multi(quaternion &a, quaternion &b);
	quaternion MakeRotationalQuaternion(float radian, float AxisX, float AxisY, float AxisZ);

	km::Vector3 AnyAxis(km::Vector3 &point, km::Vector3 c, float angle, float vx, float vy, float vz);
}