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
	// �f�o�C�X���X�g�������������ɌĂԁB
	g_renderer->OnLostDevice();

	// �ǂݍ��񂾃G�t�F�N�g�̃��\�[�X�͑S�Ĕj������B
	g_effect->UnloadResources();

	// DX���C�u�����͓����Ńf�o�C�X���̂��������Ă���̂�NULL��ݒ肷��B
	g_renderer->ChangeDevice(NULL);

	printf("End LostFunction\n");
}

void DeviceRestoreFunction(void *Data)
{
	printf("Start RestoreFunction\n");

	// DX���C�u�����͉񕜎��ɓ����Ńf�o�C�X���Đ�������̂ŐV�����ݒ肷��B
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)GetUseDirect3DDevice9();
	g_renderer->ChangeDevice(device);

	// �G�t�F�N�g�̃��\�[�X���ēǂݍ��݂���B
	g_effect->ReloadResources();

	// �f�o�C�X�����A����Ƃ��ɌĂ�
	g_renderer->OnResetDevice();
	printf("End RestoreFunction\n");
}

//�𑜓x�̎w��
namespace Window {
	//����[px]
	static const int WIDTH = 1280;
	//�c��[px]
	static const int HEIGHT = 720;
	//�J���[�r�b�g[bit]
	static const int COLOR_BIT = 32;
}

//�K�v�ƂȂ�O�̊֐�
bool Process(){
	if (ScreenFlip() != 0) return false;
	if (ProcessMessage() != 0) return false;
	if (ClearDrawScreen() != 0) return false;

	return true;
}


void Setup(){
	//�E�B���h�E���[�h�ɂ���
	//����X�t���X�N�ƃE�B���h�E�ŕς�����悤�ɂ��邩������Ȃ�
	ChangeWindowMode(true),

	//�E�B���h�E���[�h�̃^�C�g����ύX
	SetWindowTextA("STAR ROAD DRAW ver 1.00"),

	

	//���O�o�͂��s�����̃Z�b�g
	SetOutApplicationLogValidFlag(true),
	
	//�E�B���h�E�̏ꍇ�̉�ʃ��[�h�̕ύX
	SetGraphMode(Window::WIDTH, Window::HEIGHT, Window::COLOR_BIT),
	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK),
	
	//�}�E�X�J�[�\���̕\���̗L��
	SetMouseDispFlag(true);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Setup();

	// �`��p�C���X�^���X�̐���
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)GetUseDirect3DDevice9();
	g_renderer = ::EffekseerRendererDX9::Renderer::Create(device, 2000);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	g_manager = ::Effekseer::Manager::Create(2000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());
	g_manager->SetTrackRenderer(g_renderer->CreateTrackRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());
	g_manager->SetModelLoader(g_renderer->CreateModelLoader());

	// �f�o�C�X���X�g���̃R�[���o�b�N�ݒ�(�t���X�N���[���E�C���h�E�؂�ւ��̂��߂ɕK�v)
	SetGraphicsDeviceLostCallbackFunction(DeviceLostFunction, NULL);
	SetGraphicsDeviceRestoreCallbackFunction(DeviceRestoreFunction, NULL);



	// �J������������


	// Dxlib����effekseer�ɍ��W��]�L����
	MATRIX proj = GetCameraProjectionMatrix();
	MATRIX view = GetCameraViewMatrix();
	Effekseer::Matrix44 efproj, efview;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			efproj.Values[j][i] = proj.m[j][i];
			efview.Values[j][i] = view.m[j][i];
		}
	}

	// ���W�n�����낦��
	g_manager->SetCoordinateSystem(Effekseer::COORDINATE_SYSTEM_LH);


	// ���e�s���ݒ�
	g_renderer->SetProjectionMatrix(efproj);


	// �J�����s���ݒ�
	g_renderer->SetCameraMatrix(efview);

	// �G�t�F�N�g�̓Ǎ�
	g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Resources/effect/combo_0.efk");
	
	SceneManager* gameSceneManager = new SceneManager();


	gameSceneManager->setMainSoundH(LoadSoundMem("Resources/game_main.ogg"));
	gameSceneManager->initialize();

	while (Process()){

		gameSceneManager->update(g_manager);
		gameSceneManager->render(g_manager, g_renderer);

	}

	// �G�t�F�N�g�̔j��
	ES_SAFE_RELEASE(g_effect);

	// �G�t�F�N�g�Ǘ��p�C���X�^���X��j��
	g_manager->Destroy();

	// �`��p�C���X�^���X��j��
	g_renderer->Destory();


	DxLib_End();

	return 0;
}