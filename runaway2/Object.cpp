#include "Object.h"

//	コンストラクタ
Object::Object(const char* name) : position(NULL), unit(NULL), vector(NULL), direction(NULL), Model(name){
	position = new VECTOR;
	unit = new VECTOR;
	vector = new VECTOR;
	direction = new VECTOR;
}

//　コピーコンストラクタ
Object::Object(const Object &obj){
	position = new VECTOR;
	unit = new VECTOR;
	vector = new VECTOR;
	direction = new VECTOR;
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
}

//void Object::Init(){}
//void Object::Final(){}
void Object::Update(){
	MV1SetPosition(*model ,*position);
}
void Object::Draw(){
	MV1DrawModel(*model);
}