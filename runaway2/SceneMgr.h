#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"

class SceneMgr : public ISceneChanger, Task {

private:
	BaseScene* mScene;    //シーン管理変数
	IScene::eScene mNextScene;    //次のシーン管理変数

public:
	SceneMgr();
	void Init() override;//初期化
	void Final() override;//終了処理
	void Update() override;//更新
	void Draw() override;//描画

	// 引数 nextScene にシーンを変更する
	void ChangeScene(IScene::eScene NextScene) override;

};