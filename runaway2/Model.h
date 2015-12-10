#pragma once
#include <DxLib.h>

class Model{
protected:
	int *model;
	char filelname[256];
public:
	Model(const char *modelname);
	~Model();

	char* GetName();
	int GetModelHandle();
};