#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"

class Game : public BaseScene{
public:
	Game::Game(ISceneChanger *changer);
	void Init() override;
	
	void Update() override;
	void Draw() override;
};