#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"
//#include "BackGround.h"
#include "Object.h"
#include "Camera.h"
#include "Func.h"
#include "MATRIX.h"

#define SHOT_NUM 20
#define TARGET_NUM 128
class Game : public BaseScene{
private:
	Character *background;
	Object *city;
	Camera *camera;
	Character *player;
	km::Vector3 *move_position;
	km::Vector3 camera_target;
	Character *shot;
	Character *target;
	int shot_interval;
	int position_state;
	unsigned int flag;
	tagMV1_COLL_RESULT_POLY fall;
	tagMV1_COLL_RESULT_POLY side;
	int mouse_x, mouse_y;
	int timer;
	int score;
	int check_point_num;
	km::Vector3 next_unit;
public:
	Game(ISceneChanger *changer);
	virtual ~Game();
	void Init() override;
	void Update() override;
	void CameraUpdate();
	void PlayerUpdate();
	void TargetUpdate();
	void StageColisionInfo();
	void ShotColicion();

	void Draw() override;
	void MovePositionLoad(const char* text);
};