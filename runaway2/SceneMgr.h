#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"

class SceneMgr : public ISceneChanger, Task {

private:
	BaseScene* mScene;    //�V�[���Ǘ��ϐ�
	IScene::eScene mNextScene;    //���̃V�[���Ǘ��ϐ�

public:
	SceneMgr();
	void Init() override;//������
	void Final() override;//�I������
	void Update() override;//�X�V
	void Draw() override;//�`��

	// ���� nextScene �ɃV�[����ύX����
	void ChangeScene(IScene::eScene NextScene) override;

};