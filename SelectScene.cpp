#include "SelectScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
#include "DirectXCommon.h"
SelectScene::~SelectScene()
{
	Finalize();
}

void SelectScene::Initialize()
{
	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(5, L"Resources/selectScene.png");
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(5, { 0.0f,0.0f });
}

void SelectScene::Finalize()
{
}

void SelectScene::Update()
{
	// �Q�[���V�[���̖��t���[������

	Input* input = Input::GetInstance();
	
	if (input->TriggerKey(DIK_1)&& sceneChange.inendflag)
	{
		//�V�[���؂�ւ�
		//SceneManager::GetInstance()->ChangeScene("STAGE_1");
		sceneChange.SceneChangeStart("STAGE_1");
	}
	if (input->TriggerKey(DIK_2))
	{
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("STAGE_2");
	}
	if (input->TriggerKey(DIK_3))
	{
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("STAGE_3");
	}
	if (input->TriggerKey(DIK_4))
	{
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("STAGE_4");
	}
	if (input->TriggerKey(DIK_5))
	{
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("STAGE_5");
	}
	if (input->TriggerKey(DIK_6))
	{
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("STAGE_6");
	}
	if (input->TriggerKey(DIK_7))
	{
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("STAGE_7");
	}
	if (input->TriggerKey(DIK_8))
	{
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("STAGE_8");
	}
	DebugText::GetInstance()->Print(50, 20, 3, "select");
	sceneChange.Update();
}

void SelectScene::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCmdList();
#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��

	spriteBG->Draw();

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion �w�i�X�v���C�g�`��




#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);

	// �f�o�b�O�e�L�X�g�̕`��
	DebugText::GetInstance()->DrawAll(cmdList);
	sceneChange.Draw();
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
}
