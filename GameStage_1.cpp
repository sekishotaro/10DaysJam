#include "GameStage_1.h"
#include "SceneManager.h"

GameStage_1::~GameStage_1()
{
	Finalize();
}

void GameStage_1::Initialize()
{
}

void GameStage_1::Finalize()
{
}

void GameStage_1::Update()
{
	Input* input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void GameStage_1::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCmdList();
#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��

	//sprite->Draw();

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion �w�i�X�v���C�g�`��




#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
}