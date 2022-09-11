#include "GamePlayScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
#include "DirectXCommon.h"

#include "PLayer.h"

void GamePlayScene::Initialize()
{
	Audio::GetInstance()->LoadWave("futta-dream.wav");
	Audio::GetInstance()->LoadWave("zaza.wav");

	// �J��������
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// �J�����Z�b�g
	Object3d::SetCamera(camera);

	// �e�N�X�`���ǂݍ���

	Sprite::LoadTexture(1, L"Resources/background.png");
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	//�I�u�W�F�N�g����
	BarrelModel = Model::LoadFromOBJ("block");

	barrelObject1 = Object3d::Create();
	barrelObject2 = Object3d::Create();

	//�I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	barrelObject1->SetModel(BarrelModel);
	barrelObject1->SetScale({ 0.5f, 0.5f, 0.5f });

	barrelObject2->SetModel(BarrelModel);
	barrelObject2->SetScale({ 0.5f, 0.5f, 0.5f });

	Player::Initialize();


	XMFLOAT3 posA = { -50.0f, -15.0f, 0.0f };
	XMFLOAT3 posB = {  50.0f, -15.0f, 0.0f };

	XMFLOAT3 posC = { -50.0f, -25.0f, 0.0f };
	XMFLOAT3 posD = {  50.0f, -25.0f, 0.0f };

	barrel1 = Barrel::Initialize(XMFLOAT3(0.0f, -15.0f, 0.0f), posA, posB);
	
	barrel2 = Barrel::Initialize(XMFLOAT3(0.0f, -25.0f, 0.0f), posC, posD);

	barrelObject1->SetPosition(barrel1->GetPos());
	barrelObject2->SetPosition(barrel2->GetPos());
}

void GamePlayScene::Finalize()
{
	delete BarrelModel;
	Player::Finalize();
}

void GamePlayScene::Update()
{
	// �Q�[���V�[���̖��t���[������
	
	Input *input = Input::GetInstance();

	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		// ���݂̍��W���擾
		XMFLOAT3 position = camera->GetEye();

		// �ړ���̍��W���v�Z
		if (input->PushKey(DIK_W)) { position.y += 1.0f; }
		else if (input->PushKey(DIK_S)) { position.y -= 1.0f; }
		if (input->PushKey(DIK_D)) { position.x += 1.0f; }
		else if (input->PushKey(DIK_A)) { position.x -= 1.0f; }

		// ���W�̕ύX�𔽉f
		camera->SetEye(position);
	}

	DebugText::GetInstance()->Print(50, 30 * 1, 2, "%f", barrel1->GetPos().y);
	DebugText::GetInstance()->Print(50, 30 * 2, 2, "%f", barrel2->GetPos().y);

	barrel1->CollisionPlayer();
	barrel2->CollisionPlayer();
	//�A�b�v�f�[�g
	camera->Update();
	barrel1->Update(input);
	barrel2->Update(input);
	Player::Update(input);

	barrelObject1->SetPosition(barrel1->GetPos());
	barrelObject1->Update();

	barrelObject2->SetPosition(barrel2->GetPos());
	barrelObject2->Update();
	
}

void GamePlayScene::Draw()
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

	// 3D�I�u�N�W�F�N�g�̕`��
	barrelObject1->Draw();
	barrelObject2->Draw();

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>
	
	Player::Draw();

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);

	// �f�o�b�O�e�L�X�g�̕`��
	DebugText::GetInstance()->DrawAll(cmdList);

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
}
