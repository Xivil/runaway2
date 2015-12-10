#pragma once
#include "DxLib.h"
#include "Model.h"
#include "Task.h"
class Object : public Task, Model{
private:
	VECTOR *position;
	VECTOR *unit;
	VECTOR *vector;
	VECTOR *direction;

public:
	Object(const char* name);
	Object(const Object &obj);
	~Object();
	//void Init() override;
	//void Final() override;
	void Update() override;
	void Draw() override;
};