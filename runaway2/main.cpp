#include <DxLib.h>
#include "Model.h"
#include "SceneMgr.h"
#include "Camera.h"
#include "Object.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	
	
	Camera c;
	SceneMgr sceneMgr;
	sceneMgr.Init();
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() ){
		c.UseCamera();
		
		sceneMgr.Update();
		sceneMgr.Draw();
	}

	sceneMgr.Final();
	DxLib_End();
	return 0;
}