#include "GameStage_7.h"
#include "SceneManager.h"

GameStage_7::~GameStage_7()
{
	Finalize();
}

void GameStage_7::Initialize()
{
	Audio::GetInstance()->LoadWave("BGM.wav");
	Audio::GetInstance()->LoadWave("injection.wav");
	Audio::GetInstance()->PlayWave("BGM.wav", 0.05, true);

}

void GameStage_7::Finalize()
{
}

void GameStage_7::Update()
{
	Input* input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE))
	{
		Audio::GetInstance()->SoundStop("BGM.wav");
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void GameStage_7::Draw()
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
