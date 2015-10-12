//#pragma once
//
//#include "SingletonClass.h"
//#include "Config.h"
//#include "SceneBaseClass.h"
//#include <stack>
//
//class Application : public SingletonClass<Application>
//{
//public:	
//	Application();
//	virtual ~Application(){};
//	friend SingletonClass<Application>;
//
//	bool Run();
//
//	�V�[���؂�ւ�
//	void SetNextScene(SceneMode state);
//	void ChangeNextScene();
//
//	�A�v���I��
//	void End();
//
//	�ێ����Ă���V�[�����ׂĔj��
//	void DestroyAll();
//
//protected:
//	����Ɏ��s�ł������ǂ���
//	bool isRun_;
//
//	SceneMode nowState_;
//	SceneMode nextState_;
//
//	SceneBase�^��stack
//	std::stack<SceneBaseClass*>sceneStack;
//
//};