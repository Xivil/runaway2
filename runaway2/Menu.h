#pragma once
#include "BaseScene.h"

class Menu : public BaseScene {

public:
	Menu(ISceneChanger* changer);
	void Init() override;			
	//void Finalize() override ;    
	void Update() override;        
	void Draw() override;           

};