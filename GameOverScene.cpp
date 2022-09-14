#include "GameOverScene.h"
#include "Input.h"
#include "SceneManager.h"

GameOverScene::~GameOverScene()
{
	Finalize();
}

void GameOverScene::Initialize()
{

	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(7, L"Resources/gameover.png");
	// �w�i�X�v���C�g����
	Gameoverimg = Sprite::Create(7, { 0.0f,0.0f });

	// �e�N�X�`���ǂݍ���
	//Sprite::LoadTexture(100, L"Resources/black.png");
	//�X�v���C�g����
	black = Sprite::Create(100, { 0.0f,0.0f });
	nowTime = 0;
	endTime = 1;
	timeRate = 0;
}

void GameOverScene::Finalize()
{
}

void GameOverScene::Update()
{
	nowTime += 0.03;
	timeRate = min(nowTime / endTime, 1);
	ease();
	Input* input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE))
	{
		nowTime = 0;
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void GameOverScene::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCmdList();
#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��

	Gameoverimg->Draw();

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion �w�i�X�v���C�g�`��




#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	black->Draw();
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
}

void GameOverScene::ease()
{

	float start=800;
	float end = 0;
	
	float pos;

	pos = (end - start) * ((timeRate * timeRate * timeRate) + 1) + start;
	XMFLOAT2 result;
	result.x = 0;
	result.y = pos;

	black->SetPosition(result);
}
