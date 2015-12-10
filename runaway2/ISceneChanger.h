#pragma once

namespace IScene{
	enum eScene{
		Menu,
		Game,
		None,
	};
}

class ISceneChanger{
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(IScene::eScene NextScene) = 0;
};
