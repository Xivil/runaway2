#include "Model.h"
#include <stdio.h>

Model::Model(){
	
}

Model::Model(const char *modelname){
	
	model = MV1LoadModel(modelname);
	material_num = MV1GetMaterialNum(model);
	texture_num = MV1GetTextureNum(model);
	frame_num = MV1GetFrameNum(model);
	mesh_num = MV1GetMeshNum(model);
	shape_num = MV1GetShapeNum(model);
	triangle_list_num = MV1GetTriangleListNum(model);

	strcpy_s(filelname, modelname);

	if ( model == -1 ){
		char buf[256];
		sprintf_s(buf, "%s���f���ǂݍ��݃G���[", modelname);
		MessageBox(NULL, buf, modelname, MB_ICONERROR);
	}
}

Model::~Model(){
	
	
}

void Model::SetModel(const char* modelname){
	
		
		model = MV1LoadModel(modelname);
	
}

char* Model::GetName(){
	return filelname;
}
int Model::GetModelHandle(){
	return model;
}
