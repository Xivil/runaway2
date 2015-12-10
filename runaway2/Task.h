#pragma once

class Task{
public:
	virtual ~Task(){}
	virtual void Init(){}
	virtual void Final(){}
	virtual void Update() = 0;
	virtual void Draw() = 0;
};