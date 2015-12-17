#include "Model.h"
#include <stdio.h>
Model::Model(const char *modelname){
	model = new int;
	*model = MV1LoadModel(modelname);
	strcpy_s(filelname, modelname);
	if ( *model == -1 ){
		char buf[256];
		sprintf_s(buf, "%s���f���ǂݍ��݃G���[", modelname);
		MessageBox(NULL, buf, modelname, MB_ICONERROR);
	}
}

Model::~Model(){
	
	delete model;
	model = 0;
}

char* Model::GetName(){
	return filelname;
}
int Model::GetModelHandle(){
	return *model;
}
