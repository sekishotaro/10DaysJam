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
}

void SelectScene::Finalize()
{
}

void SelectScene::Update()
{
	// �Q�[���V�[���̖��t���[������

	Input* input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE))
	{
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("STAGE_1");
	}
	DebugText::GetInstance()->Print(50, 20, 3, "select");
}

void SelectScene::Draw()
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

	// �f�o�b�O�e�L�X�g�̕`��
	DebugText::GetInstance()->DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion �O�i�X�v���C�g�`��
}
