#include "Object.h"

Object::Object() : Model(NULL){
	
}

//	コンストラクタ
Object::Object(const char* name) : position(NULL), unit(NULL), vector(NULL), direction(NULL), rotate(NULL), Model(name){
	position = new km::Vector3;
	unit = new km::Vector3;
	vector = new km::Vector3;
	direction = new km::Vector3;
	rotate = new km::Vector3[3];
}

//　コピーコンストラクタ
Object::Object(const Object &obj) : Model(obj.filelname){

	position = new km::Vector3(*obj.position);
	unit = new km::Vector3(*obj.unit);
	vector = new km::Vector3(*obj.vector);
	direction = new km::Vector3(*obj.direction);
	rotate = new km::Vector3(*obj.rotate);
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
	delete rotate;
	rotate = 0;
	delete model;
	model = 0;
}

Object& Object::operator = (const Object &obj){
	if (this != &obj)
	{
		*position = *obj.position;
		*unit = *obj.unit;
		*vector = *obj.vector;
		*direction = *obj.direction;
		*rotate = *obj.rotate;
	}
	return *this;
}

km::Vector3 Object::get_position(){
	return *position;
}
km::Vector3 Object::get_unit(){
	return *unit;
}
km::Vector3 Object::get_vector(){
	return *vector;
}
km::Vector3 Object::get_direction(){
	return *direction;
}
km::Vector3 Object::get_rotate(){
	return *rotate;
}

void Object::set_position(km::Vector3 vec){
	*position = vec;
}
void Object::set_unit(km::Vector3 vec){
	*unit = vec;
}
void Object::set_vector(km::Vector3 vec){
	*vector = vec;
}
void Object::set_direction(km::Vector3 vec){
	*direction = vec;
}
void Object::set_rotate(km::Vector3 vec){
	*rotate = vec;
}

//void Object::Init(){}
//void Object::Final(){}
void Object::Update(){
	*position += *vector;
	*direction += *vector;
	//*unit = *direction - *position;
	//unit->Normalize();
	MV1SetPosition(*model ,Vector3ToDxVector(*position));
	MV1SetRotationXYZ(*model, VGet(0, DEG_TO_RAD(rotate->get_x() * -1), 0));
}
void Object::Draw(){
	MV1DrawModel(*model);
}


/*-------------------------------------
	Character
---------------------------------------*/
Character::Character() : Object(NULL){
	
}

Character::Character(const char* name) : Object(name){
	enable_gravity();
}

Character::Character(const Character &obj){
	
}

Character::~Character(){

}


void Character::set_life(const int life){
	this->life = life;
}

void Character::enable_gravity(){
	flag |= gravity;
}

void Character::disable_gravity(){
	flag &= ~gravity;
}

void Character::Update(){
	Object::Update();

	if (flag & gravity)
	{
		position->y += -1;
		direction->y += -1;
	}
	else{
		vector->y = 0;
	}
}

void Character::Draw(){
	Object::Draw();
}


/*------------------------------------
	player
------------------------------------*/
Player::Player(const char *name) : Character(name){}