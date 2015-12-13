#include "Object.h"

Object::Object() : Model(NULL){
	
}

//	コンストラクタ
Object::Object(const char* name) : position(NULL), unit(NULL), vector(NULL), direction(NULL), Model(name){
	position = new km::Vector3;
	unit = new km::Vector3;
	vector = new km::Vector3;
	direction = new km::Vector3;
}

//　コピーコンストラクタ
Object::Object(const Object &obj) : Model(obj.filelname){
	position = new km::Vector3;
	unit = new km::Vector3;
	vector = new km::Vector3;
	direction = new km::Vector3;
	position = obj.position;
	unit = obj.unit;
	vector = obj.vector;
	direction = obj.direction;
}

//	デストラクタ
Object::~Object(){
	delete direction;
	direction = 0;
	delete vector;
	vector = 0;
	delete unit;
	unit = 0;
	delete position;
	position = 0;
	delete model;
	model = 0;
}

//void Object::Init(){}
//void Object::Final(){}
void Object::Update(){
	MV1SetPosition(*model ,Vector3ToDxVector(*position));
}
void Object::Draw(){
	MV1DrawModel(*model);
}