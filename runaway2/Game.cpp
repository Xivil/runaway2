#include "Game.h"
#include "Quaternion.h"
#include "Model.h"
Game::Game(ISceneChanger* changer) : BaseScene(changer){
	background = new Object("Graph/Model/Skydome_X8/Dome_X803.x");
	city = new Object("Graph/Model/ネオUKシティ_Ver1.10/model/ネオＵＫシティ(夜景)_Ver1.10.pmx");
	camera = new Camera;
	player = new Player("Graph/Model/にがミクV205/にがミク[ゴシック]V205.pmd");
	Init();
}

Game::~Game(){
	delete background;
	background = 0;
	delete city;
	city = 0;
	delete camera;
	camera = 0;
}

void Game::Init(){
	*player->position = km::GetVector3(0, 0, 0);
	*player->direction = km::GetVector3(0, 0, 5);
	StageColisionInfo();
}

void Game::Update(){
	StageColisionInfo();
	player->Update();
	PlayerUpdate();
	CameraUpdate();
	Keyboard_Update();
	
}
void Game::CameraUpdate(){
	static km::Vector3 v = km::GetVector3(0,0,0);
	v = player->get_unit() * -50;
	v += km::GetVector3(0, 3, 0);
	//camera->SetPosition(player->get_direction());

	
	camera->UseCamera();

}


void Game::PlayerUpdate(){
	if (Keyboard_Get(KEY_INPUT_LEFT)){
		player->rotate->set_x(player->rotate->get_x() + 1);
	}
	if (Keyboard_Get(KEY_INPUT_RIGHT)){
		player->rotate->set_x(player->rotate->get_x() - 1);
	}
	if (Keyboard_Get(KEY_INPUT_UP)){
		*player->vector = *player->unit;
	}
	else if (Keyboard_Get(KEY_INPUT_DOWN)){
		*player->vector = *player->unit;
		*player->vector *= -1;
	}

	else{
		player->vector->set_x(0);
		player->vector->set_z(0);
	}
	if (Keyboard_Get(KEY_INPUT_SPACE) == 1){
		player->vector->y = 30;
		player->disable_gravity();
	}
	else{
		player->enable_gravity();
	}

	
	km::Vector3 a = km::AnyAxis(*player->direction, *player->position, player->rotate->get_x(), 0, 1, 0);
	//*player->direction = a;
	*player->unit = a - *player->position;
	player->unit->Normalize();
	
	camera->SetPosition(a + *player->unit * -15); 
	camera->SetTarget(*player->position);
}

void Game::StageColisionInfo(){
	
	
	MV1SetupCollInfo(city->GetModelHandle(), -1);
	
	fall = MV1CollCheck_Line(*city->model, -1, km::Vector3ToDxVector(*player->position - km::GetVector3(0, -1, 0)), km::Vector3ToDxVector(*player->position - km::GetVector3(0, 5, 0)));
	side = MV1CollCheck_Line(*city->model, -1, km::Vector3ToDxVector(*player->position + km::GetVector3(-5, 0, 5)), km::Vector3ToDxVector(*player->position + km::GetVector3(5, 0, 5)));
	if (fall.HitFlag == 1){
		player->disable_gravity();
	}
	if (fall.HitFlag == 1){
		if (fall.HitPosition.y >= player->position->y){
			player->position->y += fall.HitPosition.y;
			player->direction->y += fall.HitPosition.y;
		}
	}
}

void Game::Draw(){
	//background->Draw();
	city->Draw();
	player->Draw();
	if (fall.HitFlag == 1){
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", fall.HitFlag);
	}
	km::PrintVector3DxLib(*player->position, 0, 0);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "%f %f %f", fall.HitPosition.x, fall.HitPosition.y, fall.HitPosition.z);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "%f %f %f", fall.Normal.x, fall.Normal.y, fall.Normal.z);
}