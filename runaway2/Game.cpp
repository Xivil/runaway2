#include "Game.h"
Game::Game(ISceneChanger* changer) : BaseScene(changer){
	background = new Object("Graph/Model/Skydome_X8/Dome_X803.x");
	bridge = new Object("Graph/Model/�l�IUK�V�e�B_Ver1.10/model/�l�I�t�j�V�e�B(��i)_Ver1.10.pmx");
	camera = new Camera;
}

Game::~Game(){
	delete background;
	background = 0;
	delete bridge;
	bridge = 0;
	delete camera;
	camera = 0;
}

void Game::Init(){

}

void Game::Update(){
	background->Update();
	camera->UseCamera();
	Keyboard_Update();
}

void Game::Draw(){
	//background->Draw();
	bridge->Draw();
}