//#include "Application.h"
//#include "KeyboardClass.h"
//#include "Title.h"
//#include "HospitalMgr.h"
//#include "MirrorMgr.h"
//#include "GocartMgr.h"
//#include "GameScene.h"
//#include "DX\DxLib.h"
//
////���݂̃V�[���X�e�[�^�X��Title��
//Application::Application()
//	:isRun_(true)
//	,nowState_(SceneMode::Mode_TITLE)
//	,nextState_(SceneMode::Mode_TITLE)
//{
//	//�ŏ��Ƀ^�C�g��������
////	sceneStack.push(Title::Create());
//}
//
//bool Application::Run()
//{
//	//stack�̒��ɕ��������Run
//	if(sceneStack.empty()) return isRun_;
//
//	KeyboardClass::getInstance()->update();
//
//	//scenestack�@��ɏ�̃V�[���𑖂点��
//	sceneStack.top()->update();
//	sceneStack.top()->render();
//
//	//�V�[���ɕύX�������������ꍇ�A�����̈�ԍŌ�Ő؂�ւ�����������
//	if(nowState_ != nextState_)
//	{
//		ChangeNextScene();
//	}
//
//	return isRun_;
//}
//
//void Application::SetNextScene(SceneMode state)
//{
//	ClearDrawScreen();
//	//���̃V�[���o�^
//	nextState_ = state;
//}
//
//void Application::ChangeNextScene()
//{
//	//! �ێ����Ă��邷�ׂẴV�[����j���B
//	this->DestroyAll();
//
//	switch (nextState_)
//	{
//		case Mode_TITLE:
//			//sceneStack.push(Title::Create());
//			break;
////		case Mode_Mirror:
////			sceneStack.push(MirrorMgr::Create());
//			break;
//		case Mode_Hospital:
//			sceneStack.push(HospitalMgr::Create());
//			break;
//		case Mode_Gocart:
//			sceneStack.push(GocartMgr::Create());
//			break;
//		default:
//			break;
//	}
//
//	//! �V�[���̏�Ԃ��X�V���ā@�؂�ւ��I�� 
//	nowState_ = nextState_;
//}
//
//void Application::DestroyAll()
//{
//	//�S�Ă̕ێ����Ă���V�[�����J������
//	while ( ! sceneStack.empty()) {
//		delete sceneStack.top();
//		sceneStack.pop();
//	}
//}
//
//void Application::End() 
//{
//	isRun_ = false;
//}