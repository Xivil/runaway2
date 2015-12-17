#include <DxLib.h>

#include "SceneMgr.h"
#include "Object.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetWindowSize(800, 600);
	
	SceneMgr sceneMgr;
	sceneMgr.Init();
	
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() ){
		sceneMgr.Update();
		sceneMgr.Draw();
	}

	sceneMgr.Final();
	DxLib_End();
	return 0;
}