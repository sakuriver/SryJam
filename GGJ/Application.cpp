//#include "Application.h"
//#include "KeyboardClass.h"
//#include "Title.h"
//#include "HospitalMgr.h"
//#include "MirrorMgr.h"
//#include "GocartMgr.h"
//#include "GameScene.h"
//#include "DX\DxLib.h"
//
////現在のシーンステータスをTitleへ
//Application::Application()
//	:isRun_(true)
//	,nowState_(SceneMode::Mode_TITLE)
//	,nextState_(SceneMode::Mode_TITLE)
//{
//	//最初にタイトルを入れる
////	sceneStack.push(Title::Create());
//}
//
//bool Application::Run()
//{
//	//stackの中に物があればRun
//	if(sceneStack.empty()) return isRun_;
//
//	KeyboardClass::getInstance()->update();
//
//	//scenestack　常に上のシーンを走らせる
//	sceneStack.top()->update();
//	sceneStack.top()->render();
//
//	//シーンに変更処理があった場合、処理の一番最後で切り替え処理をする
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
//	//次のシーン登録
//	nextState_ = state;
//}
//
//void Application::ChangeNextScene()
//{
//	//! 保持しているすべてのシーンを破棄。
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
//	//! シーンの状態を更新して　切り替え終了 
//	nowState_ = nextState_;
//}
//
//void Application::DestroyAll()
//{
//	//全ての保持しているシーンを開放する
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