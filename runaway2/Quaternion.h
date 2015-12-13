#pragma once
#include <math.h>
#include "VECTOR.h"


struct quaternion{
	float t;
	km::Vector3 V;
};

quaternion Multi(quaternion &a, quaternion &b){
	quaternion temp;
	temp.t = a.t * b.t - (a.V.x * b.V.x + a.V.y * b.V.y + a.V.z * b.V.z);
	temp.V.x = a.t * b.V.x + b.t * a.V.x + (a.V.y * b.V.z - a.V.z * b.V.y);
	temp.V.y = a.t * b.V.y + b.t * a.V.y + (a.V.z * b.V.x - a.V.x * b.V.z);
	temp.V.z = a.t * b.V.z + b.t * a.V.z + (a.V.x * b.V.y - a.V.y * b.V.x);
	return temp;
}
quaternion MakeRotationalQuaternion(float radian, float AxisX, float AxisY, float AxisZ)
{
	quaternion ans;
	float   norm;
	float   ccc, sss;
	ans.t = ans.V.x = ans.V.y = ans.V.z = 0.0;

	norm = AxisX *  AxisX + AxisY *  AxisY + AxisZ *  AxisZ;
	if (norm <= 0.0) return ans;

	norm = 1.0 / sqrt(norm);
	AxisX *= norm;
	AxisY *= norm;
	AxisZ *= norm;

	ccc = cos(0.5 * radian);
	sss = sin(0.5 * radian);

	ans.t = ccc;
	ans.V.x = sss * AxisX;
	ans.V.y = sss * AxisY;
	ans.V.z = sss * AxisZ;
	return   ans;
}

km::Vector3 AnyAxis(km::Vector3 &point, km::Vector3 c, float angle, float vx, float vy, float vz){
	quaternion p, q, r, temp;
	km::Vector3 ret, buf;
	buf.x = point.x;
	buf.y = point.y;
	buf.z = point.z;
	angle = DEG_TO_RAD(angle);
	float tcos = cos(angle / 2);
	float tsin = sin(angle / 2);

	p.t = 0;
	p.V.x = point.x - c.x;	//	0
	p.V.y = point.y - c.y;	//	140 or -140
	p.V.z = point.z - c.z;	//	0
	//q.t = r.t = tcos;
	//q.V.x = vx * tsin;
	//q.V.y = vy * tsin;
	//q.V.z = vz * tsin;
	//r.V.x = -vx * tsin;
	//r.V.y = -vy * tsin;
	//r.V.z = -vz * tsin;
	q = MakeRotationalQuaternion(angle, vx, vy, vz);
	r = MakeRotationalQuaternion(-angle, vx, vy, vz);

	temp = Multi(r, p);
	temp = Multi(temp, q);

	ret.x = temp.V.x + c.x;
	ret.y = temp.V.y + c.y;
	ret.z = temp.V.z + c.z;
	point.x = temp.V.x + c.x;
	point.y = temp.V.y + c.y;
	point.z = temp.V.z + c.z;

	return ret;
}