#include "DxLib.h"
#include "Game.h"
#include "Menu.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr() :
mNextScene(IScene::eScene::None) //���̃V�[���Ǘ��ϐ�
{
	mScene = (BaseScene*) new Game(this);
}

//������
void SceneMgr::Init(){
	mScene->Init();
}

//�I������
void SceneMgr::Final(){
	mScene->Final();
}

//�X�V
void SceneMgr::Update(){
	if (mNextScene != IScene::eScene::None){    //���̃V�[�����Z�b�g����Ă�����
		mScene->Final();//���݂̃V�[���̏I�����������s
		delete mScene;
		switch (mNextScene){       //�V�[���ɂ���ď����𕪊�
		case IScene::eScene::Menu:        //���̉�ʂ����j���[�Ȃ�
			mScene = (BaseScene*) new Menu(this);   //���j���[��ʂ̃C���X�^���X�𐶐�����
			break;//�ȉ���
		case IScene::eScene::Game:
			mScene = (BaseScene*) new Game(this);
			break;
		
		}
		mNextScene = IScene::eScene::None;    //���̃V�[�������N���A
		mScene->Init();    //�V�[����������
	}

	mScene->Update(); //�V�[���̍X�V
}

//�`��
void SceneMgr::Draw(){
	mScene->Draw(); //�V�[���̕`��
}

// ���� nextScene �ɃV�[����ύX����
void SceneMgr::ChangeScene(IScene::eScene NextScene){
	mNextScene = NextScene;    //���̃V�[�����Z�b�g����
}