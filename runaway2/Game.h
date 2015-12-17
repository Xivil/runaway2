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
public:
	Game(ISceneChanger *changer);
	virtual ~Game();
	void Init() override;
	void Update() override;
	void Draw() override;
};