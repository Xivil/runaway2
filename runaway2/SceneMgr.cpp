#include "DxLib.h"
#include "Game.h"
#include "Menu.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr() :
mNextScene(IScene::eScene::None) //次のシーン管理変数
{
	mScene = (BaseScene*) new Game(this);
}

//初期化
void SceneMgr::Init(){
	mScene->Init();
}

//終了処理
void SceneMgr::Final(){
	mScene->Final();
}

//更新
void SceneMgr::Update(){
	if (mNextScene != IScene::eScene::None){    //次のシーンがセットされていたら
		mScene->Final();//現在のシーンの終了処理を実行
		delete mScene;
		switch (mNextScene){       //シーンによって処理を分岐
		case IScene::eScene::Menu:        //次の画面がメニューなら
			mScene = (BaseScene*) new Menu(this);   //メニュー画面のインスタンスを生成する
			break;//以下略
		case IScene::eScene::Game:
			mScene = (BaseScene*) new Game(this);
			break;
		
		}
		mNextScene = IScene::eScene::None;    //次のシーン情報をクリア
		mScene->Init();    //シーンを初期化
	}

	mScene->Update(); //シーンの更新
}

//描画
void SceneMgr::Draw(){
	mScene->Draw(); //シーンの描画
}

// 引数 nextScene にシーンを変更する
void SceneMgr::ChangeScene(IScene::eScene NextScene){
	mNextScene = NextScene;    //次のシーンをセットする
}