#include "GamePlayScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
#include "DirectXCommon.h"

void GamePlayScene::Initialize()
{
	Audio::GetInstance()->LoadWave("futta-dream.wav");
	Audio::GetInstance()->LoadWave("zaza.wav");

	//Audio::GetInstance()->PlayWave("zaza.wav", true);

	// �J��������
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// �J�����Z�b�g
	Object3d::SetCamera(camera);

	// �e�N�X�`���ǂݍ���

	Sprite::LoadTexture(1, L"Resources/background.png");
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	// �I�u�W�F�N�g����
	model = Model::LoadFromOBJ("sphere");
	block = Model::LoadFromOBJ("block");

	objectX = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	objectX->SetModel(model);

	//�}�b�v�`�b�v�p��CSV�ǂݍ���
	//(map, "Resource/scv/�Ȃ񂽂�.csv")�Œǉ��\
	Mapchip::CsvToVector(map, "Resources/csv/tutorial.csv");//mapNum=0
	
	//�}�b�v�`�b�v�p�̃I�u�W�F�N�g�̏�����
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x] = Object3d::Create();
			objBlock[y][x]->SetModel(block);
			objBlock[y][x]->SetScale({ 1.0f,1.0f,1.0f });
			objBlock[y][x]->SetPosition({ 1000.0f,1000.0f,0.0f });
		}
	}
}

void GamePlayScene::Finalize()
{
	delete model;
}

void GamePlayScene::Update()
{
	// �Q�[���V�[���̖��t���[������
	
	Input *input = Input::GetInstance();

	// �}�b�v�`�b�v����
	MapCreate(0);
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x]->Update();
		}
	}

	//�I�u�W�F�N�g�ړ�
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// ���݂̍��W���擾
		p_pos = objectX->GetPosition();

		// �ړ���̍��W���v�Z
		if(input->PushKey(DIK_UP))
		{
			p_pos.y += 1.0f;
		}
		else if(input->PushKey(DIK_DOWN))
		{
			p_pos.y -= 1.0f;
		}
		if (input->PushKey(DIK_RIGHT))
		{
			p_pos.x += 1.0f;
		}
		else if (input->PushKey(DIK_LEFT))
		{
			p_pos.x -= 1.0f;
		}
	}

	//if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	//{
	//	// ���݂̍��W���擾
	//	c_pos = camera->GetEye();

	//	// �ړ���̍��W���v�Z
	//	if (input->PushKey(DIK_W))		{ c_pos.y += 1.0f; }
	//	else if (input->PushKey(DIK_S)) { c_pos.y -= 1.0f; }
	//	if (input->PushKey(DIK_D))		{ c_pos.x += 1.0f; }
	//	else if (input->PushKey(DIK_A)) { c_pos.x -= 1.0f; }

	//}

	DebugText::GetInstance()->Print(50, 30 * 1, 2, "%f", camera->GetEye().x);
	DebugText::GetInstance()->Print(50, 30 * 2, 2, "%f", camera->GetEye().y);

	if (input->TriggerKey(DIK_SPACE))
	{
		p_pos = { map_max_x / 2 * LAND_SCALE,  -map_max_y / 2 * LAND_SCALE, 0 };
	}

	// ���W�̕ύX�𔽉f
	objectX->SetPosition(p_pos);
	camera->SetEye({ p_pos.x, p_pos.y + 3.0f, p_pos.z - 100.0f });
	camera->SetTarget(p_pos);

	//�A�b�v�f�[�g
	camera->Update();
	objectX->Update();
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
	objectX->Draw();

	//�}�b�v�`�b�v�̕`��
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x]->Draw();
		}
	}

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);

	// �f�o�b�O�e�L�X�g�̕`��
	DebugText::GetInstance()->DrawAll(cmdList);

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
}

void GamePlayScene::MapCreate(int mapNumber)
{
	for (int y = 0; y < map_max_y; y++) {//(y��12)
		for (int x = 0; x < map_max_x; x++) {//(x��52)

			if (Mapchip::GetChipNum(x, y, map[mapNumber]) == Coin)
			{
				//�ʒu�Ƒ傫���̕ύX(���͑傫���͕ύX���Ȃ���)
				//objBlock[y][x]->SetScale({ LAND_SCALE, LAND_SCALE, LAND_SCALE });
				objBlock[y][x]->SetPosition({ x * LAND_SCALE,  -y * LAND_SCALE, 0 });
			}
			else
			{
				objBlock[y][x]->SetPosition({ 1000, 1000, 0 });
			}
		}
	}
}

int GamePlayScene::GetLeftMapChip(XMFLOAT3 position)
{
	int chip = Mapchip::GetChipNum(static_cast<int>((position.x + LAND_SCALE / 2) / LAND_SCALE - 1), -static_cast<int>((position.y - LAND_SCALE / 2) / LAND_SCALE), map[0]);
	return chip;
}

int GamePlayScene::GetRightMapChip(XMFLOAT3 position)
{
	int chip = Mapchip::GetChipNum(static_cast<int>((position.x + LAND_SCALE / 2) / LAND_SCALE + 1), -static_cast<int>((position.y - LAND_SCALE / 2) / LAND_SCALE), map[0]);
	return chip;
}

int GamePlayScene::GetUpMapChip(XMFLOAT3 position)
{
	int chip = Mapchip::GetChipNum(static_cast<int>((position.x + LAND_SCALE / 2) / LAND_SCALE), -static_cast<int>((position.y - LAND_SCALE / 2) / LAND_SCALE + 1), map[0]);
	return chip;
}
