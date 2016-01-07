#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"
//#include "BackGround.h"
#include "Object.h"
#include "Camera.h"
#include "Func.h"
class Game : public BaseScene{
private:
	Object *background;
	Object *city;
	Camera *camera;
	Character *player; 
	unsigned int flag;
	tagMV1_COLL_RESULT_POLY fall;
	tagMV1_COLL_RESULT_POLY side;
public:
	Game(ISceneChanger *changer);
	virtual ~Game();
	void Init() override;
	void Update() override;
	void CameraUpdate();
	void PlayerUpdate();
	void StageColisionInfo();

	void Draw() override;
};