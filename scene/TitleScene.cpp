#include "TitleScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Fornt.h"


void TitleScene::Initialize()
{
	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(20, L"Resources/title.png");
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(20, { 0.0f,0.0f });
	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(21, L"Resources/START_SPACE_UI.png");
	//�X�v���C�g����
	startui = Sprite::Create(21, { 460.0f,500.0f });
}

void TitleScene::Finalize()
{
}

void TitleScene::Update()
{
	// �Q�[���V�[���̖��t���[������

	Input *input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE))
	{
		//�V�[���؂�ւ�
		//SceneManager::GetInstance()->ChangeScene("SELECT");
		isChange = true;
	}
	if (isChange)
	{
		SceneManager::GetInstance()->ChangeScene("SELECT");
		//sceneChange.SceneChangeStart("SELECT");
		sceneChange.Update();
	}
	
	//Fornt::GetInstance()->Print(50, 20, 3, "0123456789");
}

void TitleScene::Draw()
{
	// �Q�[���V�[���̕`��

// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList *cmdList = DirectXCommon::GetInstance()->GetCmdList();

	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	spriteBG->Draw();
	
	
	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	DirectXCommon::GetInstance()->ClearDepthBuffer();

	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(cmdList);

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	startui->Draw();
	sceneChange.Draw();
	// �f�o�b�O�e�L�X�g�̕`��
	DebugText::GetInstance()->DrawAll(cmdList);
	Fornt::GetInstance()->DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
}
