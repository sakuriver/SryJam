#include "DxLib.h"

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib" )

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>

#if _DEBUG
#pragma comment(lib, "Effekseer.Debug.lib" )
#pragma comment(lib, "EffekseerRendererDX9.Debug.lib" )
#else
#pragma comment(lib, "Effekseer.Release.lib" )
#pragma comment(lib, "EffekseerRendererDX9.Release.lib" )
#endif

#include "Player_K.h"
#include "MapObject.h"
#include "Animation.h"
#include "SceneManager.h"

#define now Time[1]-Time[0]

static int g_window_width = 640;
static int g_window_height = 480;
static ::Effekseer::Manager*			g_manager = NULL;
static ::EffekseerRendererDX9::Renderer*	g_renderer = NULL;
static ::Effekseer::Effect*				g_effect = NULL;
static ::Effekseer::Handle				g_handle = -1;


void DeviceLostFunction(void *Data)
{
	printf("Start LostFunction\n");
	// デバイスロストが発生した時に呼ぶ。
	g_renderer->OnLostDevice();

	// 読み込んだエフェクトのリソースは全て破棄する。
	g_effect->UnloadResources();

	// DXライブラリは内部でデバイス自体を消去しているのでNULLを設定する。
	g_renderer->ChangeDevice(NULL);

	printf("End LostFunction\n");
}

void DeviceRestoreFunction(void *Data)
{
	printf("Start RestoreFunction\n");

	// DXライブラリは回復時に内部でデバイスを再生成するので新しく設定する。
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)GetUseDirect3DDevice9();
	g_renderer->ChangeDevice(device);

	// エフェクトのリソースを再読み込みする。
	g_effect->ReloadResources();

	// デバイスが復帰するときに呼ぶ
	g_renderer->OnResetDevice();
	printf("End RestoreFunction\n");
}

//解像度の指定
namespace Window {
	//横幅[px]
	static const int WIDTH = 1280;
	//縦幅[px]
	static const int HEIGHT = 720;
	//カラービット[bit]
	static const int COLOR_BIT = 32;
}

//必要となる三つの関数
bool Process(){
	if (ScreenFlip() != 0) return false;
	if (ProcessMessage() != 0) return false;
	if (ClearDrawScreen() != 0) return false;

	return true;
}


void Setup(){
	//ウィンドウモードにする
	//◎後々フルスクとウィンドウで変えられるようにするかもしれない
	ChangeWindowMode(true),

	//ウィンドウモードのタイトルを変更
	SetWindowTextA("STAR ROAD DRAW ver 1.00"),

	

	//ログ出力を行うかのセット
	SetOutApplicationLogValidFlag(true),
	
	//ウィンドウの場合の画面モードの変更
	SetGraphMode(Window::WIDTH, Window::HEIGHT, Window::COLOR_BIT),
	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK),
	
	//マウスカーソルの表示の有無
	SetMouseDispFlag(true);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Setup();

	// 描画用インスタンスの生成
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)GetUseDirect3DDevice9();
	g_renderer = ::EffekseerRendererDX9::Renderer::Create(device, 2000);

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// エフェクト管理用インスタンスの生成
	g_manager = ::Effekseer::Manager::Create(2000);

	// 描画用インスタンスから描画機能を設定
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());
	g_manager->SetTrackRenderer(g_renderer->CreateTrackRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());
	g_manager->SetModelLoader(g_renderer->CreateModelLoader());

	// デバイスロスト時のコールバック設定(フルスクリーンウインドウ切り替えのために必要)
	SetGraphicsDeviceLostCallbackFunction(DeviceLostFunction, NULL);
	SetGraphicsDeviceRestoreCallbackFunction(DeviceRestoreFunction, NULL);



	// カメラを初期化


	// Dxlibからeffekseerに座標を転記する
	MATRIX proj = GetCameraProjectionMatrix();
	MATRIX view = GetCameraViewMatrix();
	Effekseer::Matrix44 efproj, efview;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			efproj.Values[j][i] = proj.m[j][i];
			efview.Values[j][i] = view.m[j][i];
		}
	}

	// 座標系をそろえる
	g_manager->SetCoordinateSystem(Effekseer::COORDINATE_SYSTEM_LH);


	// 投影行列を設定
	g_renderer->SetProjectionMatrix(efproj);


	// カメラ行列を設定
	g_renderer->SetCameraMatrix(efview);

	// エフェクトの読込
	g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Resources/effect/combo_0.efk");
	
	SceneManager* gameSceneManager = new SceneManager();


	gameSceneManager->setMainSoundH(LoadSoundMem("Resources/game_main.ogg"));
	gameSceneManager->initialize();

	while (Process()){

		gameSceneManager->update(g_manager);
		gameSceneManager->render(g_manager, g_renderer);

	}

	// エフェクトの破棄
	ES_SAFE_RELEASE(g_effect);

	// エフェクト管理用インスタンスを破棄
	g_manager->Destroy();

	// 描画用インスタンスを破棄
	g_renderer->Destory();


	DxLib_End();

	return 0;
}