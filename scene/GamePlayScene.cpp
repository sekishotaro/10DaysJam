#include "GamePlayScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
#include "DirectXCommon.h"

#include "PLayer.h"
#include "Barrel.h"

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
	block = Model::LoadFromOBJ("block");

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

	Player::Initialize();
	Barrel::Initialize();

	// ���a�擾
	//p_radius_x = 0.5f * Player::GetScale().x;
	//p_radius_y = 0.5f * Player::GetScale().y;
}

void GamePlayScene::Finalize()
{
	//delete model;
	Player::Finalize();
	Barrel::Finalize();
}

void GamePlayScene::Update()
{
	// �Q�[���V�[���̖��t���[������
	
	Input* input = Input::GetInstance();

	// ���W�X�V
	p_pos = Player::GetPos();
	old_p_pos = p_pos;

	// �}�b�v�`�b�v����
	MapCreate(0);
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objBlock[y][x]->Update();
		}
	}

	// �}�b�v�`�b�v�����蔻��
	//if (MapCollide(player->GetPos(), p_radius_x, p_radius_y, 0, old_p_pos))
	//{

	//}


	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		// ���݂̍��W���擾
		XMFLOAT3 position = camera->GetEye();

		DebugText::GetInstance()->Print(50, 30 * 1, 2, "%f", camera->GetEye().x);
		DebugText::GetInstance()->Print(50, 30 * 2, 2, "%f", camera->GetEye().y);
	}

	//if (input->TriggerKey(DIK_SPACE))
	//{
	//	p_pos = { map_max_x / 2 * LAND_SCALE,  -map_max_y / 2 * LAND_SCALE, 0 };
	//}

	// ���W�̕ύX�𔽉f
	camera->SetEye({ p_pos.x, p_pos.y + 3.0f, p_pos.z - 100.0f });
	camera->SetTarget(p_pos);
	Barrel::CollisionPlayer();
	//�A�b�v�f�[�g
	camera->Update();
	Barrel::Update(input);
	Player::Update(input);
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
	//objectX->Draw();

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
	
	Player::Draw();
	Barrel::Draw();

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

bool GamePlayScene::MapCollide(XMFLOAT3& pos, float radiusX, float radiusY, int mapNumber, const XMFLOAT3 old_pos)
{
	//�}�b�v�`�b�v
	//X, Y
	float x = 0;
	float y = 0;
	//Radius
	float r_x = 0;
	float r_y = 0;

	//�t���O
	bool is_hit = false;

	//����
	int max_x = static_cast<int>((pos.x + radiusX + LAND_SCALE / 2) / LAND_SCALE);
	int min_x = static_cast<int>((pos.x - radiusX + LAND_SCALE / 2) / LAND_SCALE);
	int max_y = -static_cast<int>((pos.y - radiusY + LAND_SCALE / 2) / LAND_SCALE - 1);
	int min_y = -static_cast<int>((pos.y + radiusY + LAND_SCALE / 2) / LAND_SCALE - 1);

	for (int h = min_y; h <= max_y; h++)
	{
		if (h < 0)
		{
			continue;
		}
		for (int w = min_x; w <= max_x; w++)
		{
			if (w < 0)
			{
				continue;
			}
			if (Mapchip::GetChipNum(w, h, map[mapNumber]) == Coin)
			{
				x = objBlock[h][w]->GetPosition().x;
				y = objBlock[h][w]->GetPosition().y;
				r_x = 2.5f * objBlock[h][w]->GetScale().x;
				r_y = 2.5f * objBlock[h][w]->GetScale().y;

				if (pos.x <= x + r_x && x - r_x <= pos.x)
				{
					if (y + r_y + radiusY > pos.y && y < old_pos.y)
					{
						pos.y = y + r_y + radiusY;
						is_hit = true;
					}
					else if (y - r_y - radiusY < pos.y && y > old_pos.y)
					{
						pos.y = y - r_y - radiusY;
						is_hit = true;
					}
				}
				if (pos.y <= y + r_y && y - r_y <= pos.y)
				{
					if (x + r_x + radiusX > pos.x && x < old_pos.x)
					{
						pos.x = x + r_x + radiusX;
						is_hit = true;
					}
					else if (x - r_x - radiusX < pos.x && x > old_pos.x)
					{
						pos.x = x - r_x - radiusX;
						is_hit = true;
					}
				}
			}
		}
	}

	return is_hit;
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
