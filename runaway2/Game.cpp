#include <fstream>
#include <string>
using namespace std;

#include "Game.h"
#include "Quaternion.h"
#include "Model.h"

#define MOVE_NEXT 1
#define MOUSE_ON 2
#define CLEAR 4
#define TITLE 8

#define SHOT_INTERVAL 30

namespace{
	int clear_graph = 0;
	int title_graph = 0;
	km::Matrix3X1 next_unit2;
	int music = 0;
	
}

Game::Game(ISceneChanger* changer) : BaseScene(changer){
	background = new Character("Graph/Model/Skydome_X8/Dome_X803.x");
	city = new Object("Graph/Model/ネオUKシティ_Ver1.10/model/ネオＵＫシティ(夜景)_Ver1.10.pmx");
	camera = new Camera;
	player = new Player("Graph/Model/Skydome_X8/Dome_X803.x");
	MV1SetScale(player->GetModelHandle(), VGet(15, 15, 15));
	MovePositionLoad("move_position.txt");
	move_position[0].y = 20;
	
	
	shot = new Shot[SHOT_NUM];
	for (int i = 0; i < SHOT_NUM; i++){
		shot[i].SetModel("Graph/Model/aaaa.mqo");
		MV1SetScale(shot[i].GetModelHandle(), VGet(0.02, 0.02, 0.02));
	}

	target = new Shot[TARGET_NUM];
	for (int i = 0; i < TARGET_NUM; i++){
		target[i].SetModel("Graph/Model/aaaa.mqo");
		MV1SetScale(target[i].GetModelHandle(), VGet(0.02, 0.02, 0.02));
	}
	music = LoadSoundMem("Sound/tw060.mp3");
	PlaySoundMem(music, DX_PLAYTYPE_LOOP);
	Init();
	//SetMouseDispFlag(FALSE);
}

Game::~Game(){
	delete background;
	background = 0;
	delete city;
	city = 0;
	delete camera;
	camera = 0;
	delete[] move_position;
	move_position = 0;
	delete[] shot;
	shot = 0;
}

void Game::Init(){
	player->rotate->x = 0;
	*player->position = move_position[0];
	*player->direction = move_position[0] + km::GetVector3(0, 0, 5);
	StageColisionInfo();
	flag = MOVE_NEXT;
	//flag |= TITLE;
	position_state = 0;
	SetMousePoint(320, 240);
	//*shot[0].position = km::GetVector3(0, 0, 0);
	timer = 0;
	shot_interval = 61;
	score = 0;
	for (int i = 0; i < SHOT_NUM; i++){
		shot[i].disable_flag(0xffff);
	}
	for (int i = 0; i < TARGET_NUM; i++){
		target[i].disable_flag(0xffff);
	}
}

void Game::Update(){
	if (!(flag & CLEAR) && !(flag & TITLE))
	{
		StageColisionInfo();

		player->Update();

		PlayerUpdate();
		CameraUpdate();
		Keyboard_Update();
		GetMousePoint(&mouse_x, &mouse_y);
		for (int i = 0; i < SHOT_NUM; i++){
			shot[i].Update();
		}
		TargetUpdate();
		ShotColicion();
		timer++;
		background->position = player->position;
	}
	else if(flag & TITLE){
		
	
	}
	if (position_state == check_point_num){
		flag |= CLEAR;
	}
	
	if (Keyboard_Get(KEY_INPUT_R) == 1){
		Init();
	}
}
void Game::CameraUpdate(){
	/*static km::Vector3 v = km::GetVector3(0,0,0);
	v = player->get_unit() * -50;
	v += km::GetVector3(0, 3, 0);*/
	//camera->SetPosition(player->get_direction());

	camera->UseCamera();

}


void Game::PlayerUpdate(){
	if (Keyboard_Get(KEY_INPUT_A)){
		player->rotate->set_x(player->rotate->get_x() + 1);
	}
	if (Keyboard_Get(KEY_INPUT_S)){
		player->rotate->set_x(player->rotate->get_x() - 1);
	}
	/*if (Keyboard_Get(KEY_INPUT_UP)){
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
*/
	static int move_timer = 0;

	if (Keyboard_Get(KEY_INPUT_SPACE) == 1){
		player->vector->y = 30;
		player->disable_gravity();
	}
	else{
		player->enable_gravity();
	}
	if (Keyboard_Get(KEY_INPUT_Q) == 1){
		
	}

	if (flag & MOVE_NEXT){
		
		*player->vector = (move_position[position_state + 1] - move_position[position_state]) * 3;
		*player->unit = player->vector->Normalize();
		*player->vector *= 1;
		flag &= ~MOVE_NEXT;
		position_state++;
		camera_target = *player->vector + move_position[position_state];
	}

	if (km::Horizontal_Colision(*player->position, move_position[position_state], 10) ){
		flag |= MOVE_NEXT;
		move_timer++;
	}
	if (move_timer > 60){
		move_timer = 0;
	}
	

	//// マウスポインタがある画面上の座標に該当する３Ｄ空間上の Near 面の座標を取得
	//StartPos = ConvScreenPosToWorldPos(VGet(Mx, My, 0.0f));

	//// マウスポインタがある画面上の座標に該当する３Ｄ空間上の Far 面の座標を取得
	//EndPos = ConvScreenPosToWorldPos(VGet(Mx, My, 1.0f));
	


	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !(flag & MOUSE_ON) ){
		flag |= MOUSE_ON;
		
	}
	else if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0 && (flag & MOUSE_ON)){
		if (flag & MOUSE_ON)
		{
			for (int i = 0; i < SHOT_NUM; i++){
				if ((shot[i].get_flag() >> 1) == 0){
					*shot[i].position = *player->position + km::GetVector3(0, 20, 0);
					*shot[i].vector =
						km::DxLibVECTORToVector3(ConvScreenPosToWorldPos(VGet(mouse_x, mouse_y, 0.0f)))
						- km::DxLibVECTORToVector3(ConvScreenPosToWorldPos(VGet(mouse_x, mouse_y, 1.0f)));

					*shot[i].vector *= -0.001;
					*shot[i].vector += *player->vector;
					//shot[0].vector->y *= -1;
					shot[i].enable_flag(2);
					break;
				}
			}
			flag &= ~MOUSE_ON;
		}
	}

	for (int i = 0; i < SHOT_NUM; i++){
		if (shot[i].get_flag() >> 1){
			if (100 < km::GetTwoVectorLength(*player->position, *shot[i].position)){
				shot[i].disable_flag(2);
			}
		}
	}

	
	km::Vector3 a = km::AnyAxis(*player->direction, *player->position, player->rotate->get_x(), 0, 1, 0);
	//*player->direction = a;
	*player->unit = a - *player->position;
	player->unit->Normalize();
	//camera_target.y = player->position->y + km::GetVector3(0, 5, 0);
	camera->SetPosition(*player->position + km::GetVector3(0, 20, 0));
	camera->SetTarget(*player->position + *player->unit + km::GetVector3(0, 20, 0));
	/*camera->SetPosition(*shot[0].position + km::GetVector3(0, 20, 0));
	camera->SetTarget(*shot[0].position );*/
}

void Game::TargetUpdate(){
	if (timer % 60 ==  0){
		for (int i = 0; i < TARGET_NUM; i++){
			if ((target[i].get_flag() >> 1) == 0){
				km::Vector3 temp = move_position[position_state] - *player->position;
				
				*target[i].position = *player->position + *player->vector * 160;
				temp = temp.Cross(*player->vector);
				double a = (double)rand() / ((double)RAND_MAX + 1);
				*target[i].position += (temp * 2) + temp * -a * 4;
				//*target[i].position = target[i].position->Cross(*player->vector);
				//target[i].position->Normalize();
				//*target[i].position *= 3;
				//*target[i].position += *player->position;
				target[i].position->y = player->position->y + rand() % 20 + 5;
				target[i].enable_flag(2);
				break;
			}
		}
	}

	for (int i = 0; i < TARGET_NUM; i++){
		target[i].Update();
		if (target[i].get_flag() >> 1){
			if (200 < km::GetTwoVectorLength(*player->position, *target[i].position)){
				target[i].disable_flag(2);
			}
		}
	}

}

void Game::StageColisionInfo(){
	
	
	MV1SetupCollInfo(city->GetModelHandle(), -1);
	
	fall = MV1CollCheck_Line(city->model, -1, km::Vector3ToDxVector(*player->position - km::GetVector3(0, 0.1, 0)), km::Vector3ToDxVector(*player->position - km::GetVector3(0, -5, 0)));
	side = MV1CollCheck_Line(city->model, -1, km::Vector3ToDxVector(*player->position + km::GetVector3(-5, 0, 5)), km::Vector3ToDxVector(*player->position + km::GetVector3(5, 0, 5)));
	if (fall.HitFlag == 1){
		player->disable_gravity();
	}
	if (fall.HitFlag == 1){
		if (fall.HitPosition.y >= player->position->y){
			player->position->y = fall.HitPosition.y;
			player->direction->y = player->position->y;
		}
	}
}

void Game::ShotColicion(){
	for (int i = 0; i < SHOT_NUM; i++){
		if (shot[i].get_flag() >> 1){
			for (int j = 0; j < TARGET_NUM; j++){
				if (target[j].get_flag() >> 1){
					if ( 15 > km::GetTwoVectorLength(*shot[i].position, *target[j].position))
					{
						shot[i].disable_flag(2);
						target[j].disable_flag(2);
						score++;
					}
				}
			}
		}
	}
}

void Game::Draw(){
	
	/*DrawCone3D(km::Vector3ToDxVector(move_position[position_state] - km::GetVector3(0, 500, 0)), km::Vector3ToDxVector(move_position[position_state] + km::GetVector3(0, 500, 0)), 10, 160, GetColor(0, 0, 255), GetColor(0, 0, 255), TRUE);
	DrawCone3D(km::Vector3ToDxVector(move_position[position_state] + km::GetVector3(0, 500, 0)), km::Vector3ToDxVector(move_position[position_state] - km::GetVector3(0, 500, 0)), 10, 160, GetColor(0, 0, 255), GetColor(0, 0, 255), TRUE);*/
	if (!(flag & CLEAR) && !(flag & TITLE))
	{
		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		player->Draw();
		city->Draw();
		DrawCone3D(km::Vector3ToDxVector(move_position[position_state] + km::GetVector3(0, 500, 0)), km::Vector3ToDxVector(move_position[position_state] - km::GetVector3(0, 500, 0)), 7, 160, GetColor(0, 0, 255), GetColor(0, 0, 255), TRUE);
		for (int i = 0; i < SHOT_NUM; i++){
			shot[i].Draw();
		}
		for (int i = 0; i < SHOT_NUM; i++){
			target[i].Draw();
		}
		DrawFormatString(10, 10, GetColor(200, 200, 200), "SCORE %d", score);
	}
	else if (flag & CLEAR){
		if (clear_graph == 0)
		{
			clear_graph = LoadGraph("Graph/clear.png");
		}
		DrawGraph(0, 0, clear_graph, TRUE);
	}
	else if (flag & TITLE){
		if (title_graph == 0)
		{
			title_graph = LoadGraph("Graph/title.png");
		}
		DrawGraph(0, 0, title_graph, TRUE);

	}
	//player->Draw();
	if (fall.HitFlag == 1){
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", fall.HitFlag);
	}
	/*DrawLine(320, 240, next_unit2.index[0], next_unit2.index[1], GetColor(255, 0, 0));
	float a = km::Scalar(move_position[position_state], move_position[position_state + 1]);
	next_unit2 = km::RotateAnyPoints(next_unit, -1 * RAD_TO_DEG(a), 320, 240);*/
	
	
}

namespace file{
	int line_count = 0;
}

void Game::MovePositionLoad(const char* text){
	check_point_num = 0;
	FILE *fp;
	int a;
	int cnt = 0;
	fopen_s(&fp, text , "r");
	if (fp) {
		while ((a = getc(fp)) != EOF) {
			if (a == '\n') {
				cnt++;
				check_point_num++;
			}
		}
	}
	fclose(fp);

	move_position = new km::Vector3[cnt];

	//テキストファイルから敵の情報を得る
	FILE *f;
	double c = 0;
	char buf[100];
	memset(buf, 0, sizeof(buf));
	string s;
	fopen_s(&f, text, "r");
	int col = 1;
	int row = 0;

	

	while (fgetc(f) != '\n');//一行進める
	while (1){
		while (1){
			c = fgetc(f);
			if (c == EOF){
				goto out;
			}
			if (c != '\t' && c != '\n'){
				s += c;
			}
			else { break; }

		}

		switch (col){
		case 1: move_position[row].x = atof(s.c_str()); break;
		case 2: move_position[row].z = atof(s.c_str()); break;
		
		default:break;
		}

		s.clear();
		++col;

		if (c == '\n'){
			col = 1;
			move_position[row].y = 0;
			row++;
		}
	}
out:
	fclose(f);
}