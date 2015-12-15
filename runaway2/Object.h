#pragma once
#include "VECTOR.h"
#include "Model.h"
#include "Task.h"
#include "MATRIX.h"
class Object : public Task, Model{
public:
	km::Vector3 *position;
	km::Vector3 *unit;
	km::Vector3 *vector;
	km::Vector3 *direction;

public:
	Object();
	Object(const char* name);
	Object(const Object &obj);
	virtual ~Object();

	//void Init() override;
	//void Final() override;
	void Update() override;
	void Draw() override;
};