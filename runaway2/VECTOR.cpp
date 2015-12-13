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

inline float Vector3::get_x() const { return x; }
inline float Vector3::get_y() const { return y; }
inline float Vector3::get_z() const { return z; }
inline Vector3 Vector3::get_all() const { return *this; }
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

//ベクトルの正規化
void Vector3::Normalize(){
	float mag = getMagnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}

//	2つのベクトルの内積
float Vector3::Dot(const Vector3 &v){
	return (x * v.x + y * v.y + z * v.z);
}

//	2つのベクトルの外積
Vector3 Vector3::Cross(const Vector3 &v){
	return Vector3(
		y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x
		);
}

//　コンソール用の各メンバ変数の表示
void Vector3::print(){
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "z = " << z << endl;
}

//	内積から角度を計算
float km::Scalar(const km::Vector3 &v1, const km::Vector3 &v2){
	float scalar = v1.get_x() * v2.get_x() + v1.get_y() * v2.get_y() + v1.get_z() * v2.get_z();
	float tmp1 = sqrtf(v1.get_x() * v1.get_x() + v1.get_y() * v1.get_y() + v1.get_z() * v1.get_z());
	float tmp2 = sqrtf(v2.get_x() * v2.get_x() + v2.get_y() * v2.get_y() + v2.get_z() * v2.get_z());

	return acosf(scalar / (tmp1 * tmp2)) * 180 / PI;
}

Vector3 km::GetVector3(float x, float y, float z){
	km::Vector3 temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	return temp;
}

VECTOR km::Vector3ToDxVector(km::Vector3& a){
	return VGet(a.x, a.y, a.z);
}