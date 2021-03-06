#pragma once
#include <DxLib.h>

class Model{
public:
	int model;
	int material_num;
	int texture_num;
	int frame_num;
	int mesh_num;
	int shape_num;
	int triangle_list_num;

	char filelname[256];
public:
	Model();
	Model(const char *modelname);
	
	virtual ~Model();
	void SetModel(const char *modelname);
	char* GetName();
	int GetModelHandle();
};