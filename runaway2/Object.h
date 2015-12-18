#pragma once
#include "VECTOR.h"
#include "Model.h"
#include "Task.h"
#include "MATRIX.h"

class Object : public Task, Model{
protected:
	km::Vector3 *position;
	km::Vector3 *unit;
	km::Vector3 *vector;
	km::Vector3 *direction;

public:
	Object();
	Object(const char* name);
	Object(const Object &obj);
	virtual ~Object();
	Object& operator = (const Object &obj);

	//void Init() override;
	//void Final() override;
	void Update() override;
	void Draw() override;
};

class Character : public Object{
protected:
	int life;
	MV1_COLL_RESULT_POLY_DIM HidDim;
public:
	Character();
	Character(const char* name);
	Character(const Character &obj);
	virtual ~Character();

	inline int get_life();
	void set_life(const int life);
	
	//void Init() override;
	//void Final() override;
	void Update() override;
	void Draw() override;
	
};