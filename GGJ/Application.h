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
//	シーン切り替え
//	void SetNextScene(SceneMode state);
//	void ChangeNextScene();
//
//	アプリ終了
//	void End();
//
//	保持しているシーンすべて破棄
//	void DestroyAll();
//
//protected:
//	正常に実行できたかどうか
//	bool isRun_;
//
//	SceneMode nowState_;
//	SceneMode nextState_;
//
//	SceneBase型のstack
//	std::stack<SceneBaseClass*>sceneStack;
//
//};