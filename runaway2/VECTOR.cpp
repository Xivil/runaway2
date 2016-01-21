#include "VECTOR.h"
using namespace km;

Vector3::Vector3(float ex, float why, float zee){
	x = ex;
	y = why;
	z = zee;
}

Vector3::Vector3(const Vector3 &obj){
	*this = obj;
}

float Vector3::get_x() const { return x; }
float Vector3::get_y() const { return y; }
float Vector3::get_z() const { return z; }
Vector3 Vector3::get_all() const { return *this; }
void Vector3::set_x(const float x){ this->x = x; }
void Vector3::set_y(const float y){ this->y = y; }
void Vector3::set_z(const float z){ this->z = z; }
void Vector3::set_all(const Vector3 &a){ *this = a; }

Vector3& Vector3::operator = (const Vector3 &v){
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
float Vector3::getMagnitude() const {
	return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::operator * (float num) const {
	return Vector3(x * num, y * num, z * num);
}

Vector3 operator * (float num, const Vector3 &v){
	return Vector3(num * v.x, num * v.y, num * v.z);
}

Vector3& Vector3::operator *= (float num){
	this->x *= num;
	this->y *= num;
	this->z *= num;
	return *this;
}

Vector3 Vector3::operator+(const Vector3 &P2)const{
	Vector3 temp;
	temp.x = this->x + P2.x;
	temp.y = this->y + P2.y;
	temp.z = this->z + P2.z;
	return temp;
}

Vector3& Vector3::operator+=(const Vector3 &P2){
	this->x += P2.x;
	this->y += P2.y;
	this->z += P2.z;
	return *this;
}

Vector3 Vector3::operator - (const Vector3 &v) const {
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3& Vector3::operator -= (const Vector3 &v){
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

//�x�N�g���̐��K��
Vector3 Vector3::Normalize(){
	float mag = getMagnitude();
	x /= mag;
	y /= mag;
	z /= mag;
	return *this;
}

//	2�̃x�N�g���̓���
float Vector3::Dot(const Vector3 &v){
	return (x * v.x + y * v.y + z * v.z);
}

//	2�̃x�N�g���̊O��
Vector3 Vector3::Cross(const Vector3 &v){
	return Vector3(
		y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x
		);
}

//�@�R���\�[���p�̊e�����o�ϐ��̕\��
void Vector3::print(){
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "z = " << z << endl;
}

//	���ς���p�x���v�Z
float km::Scalar(const km::Vector3 &v1, const km::Vector3 &v2){
	float scalar = v1.get_x() * v2.get_x() + v1.get_y() * v2.get_y() + v1.get_z() * v2.get_z();
	float tmp1 = sqrtf(v1.get_x() * v1.get_x() + v1.get_y() * v1.get_y() + v1.get_z() * v1.get_z());
	float tmp2 = sqrtf(v2.get_x() * v2.get_x() + v2.get_y() * v2.get_y() + v2.get_z() * v2.get_z());

	return acosf(scalar / (tmp1 * tmp2)) * 180 / PI;
}

Vector3 km::GetVector3(const float x, const float y, const float z){
	km::Vector3 temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	return temp;
}

VECTOR km::Vector3ToDxVector(const km::Vector3& a){
	return VGet(a.x, a.y, a.z);
}

Vector3 km::DxLibVECTORToVector3(const VECTOR &v){
	return Vector3(v.x, v.y, v.z);
}

float km::GetTwoVectorLength(const Vector3& a, const Vector3& b){
	Vector3 tmp = a - b;
	return tmp.getMagnitude();
}

bool km::Horizontal_Colision(const Vector3& a, const Vector3& b, const float length){
	Vector3 tmp = a - b;
	float col = tmp.get_x() * tmp.get_x() + tmp.get_z() * tmp.get_z();
	if (length * length > col){
		return true;
	}
	else{
		return false;
	}
}