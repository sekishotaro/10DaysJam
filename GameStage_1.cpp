#include "GameStage_1.h"
#include "SceneManager.h"
#include "Audio.h"
#include "DebugText.h"
#include "Fornt.h"
#include "DirectXCommon.h"
#include "PLayer.h"
#include "ResultScene.h"

void GameStage_1::Initialize()
{
	// �J��������
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// �J�����Z�b�g
	Object3d::SetCamera(camera);

	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(1, L"Resources/BG.png");
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(6, L"Resources/item_ui.png");
	//�X�v���C�g����
	itemui = Sprite::Create(6, { 0.0f,0.0f });

	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(7, L"Resources/timer.png");
	//�X�v���C�g����
	timerui = Sprite::Create(7, {980.0f,5.0f });
	//�I�u�W�F�N�g����
	BarrelModel = Model::LoadFromOBJ("Cannon");
	barrelObject1 = Object3d::Create();

	//�I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	barrelObject1->SetModel(BarrelModel);
	barrelObject1->SetScale({ 0.5f, 0.5f, 0.5f });

	// �I�u�W�F�N�g����
	item = Model::LoadFromOBJ("block");

	//�}�b�v�`�b�v�p��CSV�ǂݍ���
	//(map, "Resource/scv/�Ȃ񂽂�.csv")�Œǉ��\
	Mapchip::CsvToVector(map, "Resources/csv/stage1.csv");//mapNum=0

	//�}�b�v�`�b�v�p�̃I�u�W�F�N�g�̏�����
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objItem[y][x] = Object3d::Create();
			objItem[y][x]->SetModel(item);
			objItem[y][x]->SetScale({ 1.0f,1.0f,1.0f });
			objItem[y][x]->SetPosition({ 1000.0f,1000.0f,0.0f });
		}
	}
	// �}�b�v�`�b�v����
	MapCreate(0);

	// �v���C���[�������W
	p_pos = { map_max_x / 2 * LAND_SCALE, -map_max_y / 2 * LAND_SCALE - 25.0f, 0 };
	// �v���C���[������
	Player::Initialize(p_pos);

	// �o�����̒��Ԉʒu
	float b_posX = map_max_x / 2 * LAND_SCALE;
	float b_posY = -map_max_y / 2 * LAND_SCALE;

	// �o�����ړ��͈�
	XMFLOAT3 pos_range1 = { b_posX - 25.0f, -65.0f, 0.0f };
	XMFLOAT3 pos_range2 = { b_posX + 25.0f, -65.0f, 0.0f };

	// �o�����̌���
	XMFLOAT3 rot = { 0.0f ,180.0f ,0.0f };

	// �o����������
	barrel1 = Barrel::Initialize(XMFLOAT3(b_posX, -65.0f, 0.0f), pos_range1, pos_range2, rot, 70.0f);

	barrelObject1->SetPosition(barrel1->GetPos());
	barrelObject1->SetScale(XMFLOAT3(4.0f, 4.0f, 4.0f));
	barrelObject1->SetRotation(rot);
}

void GameStage_1::Finalize()
{
	delete BarrelModel;
	Player::Finalize();
}

void GameStage_1::Update()
{
	// �Q�[���V�[���̖��t���[������
	Input* input = Input::GetInstance();

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

	// ���W�X�V
	p_pos = Player::GetPos();
	old_p_pos = p_pos;
	// ���a�擾
	p_radius_x = 0.5f * Player::GetScale().x;
	p_radius_y = 0.5f * Player::GetScale().y;

	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objItem[y][x]->Update();
		}
	}

	// �}�b�v�`�b�v�����蔻��
	if (MapCollide(p_pos, p_radius_x, p_radius_y, 0, old_p_pos))
	{
		Mapchip::ChangeChipNum(width, height, map[0]);
		itemCount--;
	}

	if (itemCount <= 0)
	{
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("RESULT");
	}

	// ���W�̕ύX�𔽉f
	camera->SetEye({ map_max_x / 2 * LAND_SCALE, -map_max_y / 2 * LAND_SCALE + 3.0f, -100.0f });
	camera->SetTarget({ map_max_x / 2 * LAND_SCALE, -map_max_y / 2 * LAND_SCALE, 0 });

	barrel1->CollisionPlayer();

	//�A�b�v�f�[�g
	camera->Update();
	barrel1->Update(input);
	Player::Update(input);

	barrelObject1->SetPosition(barrel1->GetPos());
	barrelObject1->Update();
	//�^�C�}�[
	timer++;
	if (timer>=60)
	{
		time -= 1;
		timer = 0;
	}
	//�Q�[���I�[�o�[����
	if (time<=0)
	{
		bool gameover = true;
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("GAMEOVER");

	}
	//DebugText::GetInstance()->Print(50, 30 * 1, 2, "Stage1");
	DebugText::GetInstance()->Print(60, 50, 2, "%d", itemCount);
	Fornt::GetInstance()->Print(1068.0f, 50.0f, 2, "%d", time);
	sceneChange.Update();
}

void GameStage_1::Draw()
{
	// �Q�[���V�[���̕`��

// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCmdList();

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
	//�}�b�v�`�b�v�̕`��
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			if (Mapchip::GetChipNum(x, y, map[0]) == Item)
			{
				objItem[y][x]->Draw();
			}
		}
	}
	Player::Draw();

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	itemui->Draw();
	timerui->Draw();
	// �f�o�b�O�e�L�X�g�̕`��
	DebugText::GetInstance()->DrawAll(cmdList);
	Fornt::GetInstance()->DrawAll(cmdList);
	sceneChange.Draw();
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
}

void GameStage_1::MapCreate(int mapNumber)
{
	for (int y = 0; y < map_max_y; y++) {//(y��12)
		for (int x = 0; x < map_max_x; x++) {//(x��52)

			if (Mapchip::GetChipNum(x, y, map[mapNumber]) == Item)
			{
				//�ʒu�Ƒ傫���̕ύX(���͑傫���͕ύX���Ȃ���)
				//objItem[y][x]->SetScale({ LAND_SCALE, LAND_SCALE, LAND_SCALE });
				objItem[y][x]->SetPosition({ x * LAND_SCALE,  -y * LAND_SCALE, 0 });
				itemCount++;
			}
			else
			{
				objItem[y][x]->SetPosition({ 1000, 1000, 0 });
			}
		}
	}
}

bool GameStage_1::MapCollide(XMFLOAT3& pos, float radiusX, float radiusY, int mapNumber, const XMFLOAT3 oldPos)
{
	//�}�b�v�`�b�v
	//X, Y
	float mapX = 0;
	float mapY = 0;
	//Radius
	float mapRadiusX = 0;
	float mapRadiusY = 0;

	//�t���O
	bool hitFlag = false;

	//����
	int mapMaxX = static_cast<int>((pos.x + radiusX + LAND_SCALE / 2) / LAND_SCALE);
	int mapMinX = static_cast<int>((pos.x - radiusX + LAND_SCALE / 2) / LAND_SCALE);
	int mapMaxY = -static_cast<int>((pos.y - radiusY + LAND_SCALE / 2) / LAND_SCALE - 1);
	int mapMinY = -static_cast<int>((pos.y + radiusY + LAND_SCALE / 2) / LAND_SCALE - 1);

	for (int h = mapMinY; h <= mapMaxY; h++)
	{
		if (h < 0)
		{
			continue;
		}
		for (int w = mapMinX; w <= mapMaxX; w++)
		{
			if (w < 0)
			{
				continue;
			}
			if (Mapchip::GetChipNum(w, h, map[mapNumber]) == Item)
			{
				mapX = objItem[h][w]->GetPosition().x;
				mapY = objItem[h][w]->GetPosition().y;
				mapRadiusX = 2.0f * objItem[h][w]->GetScale().x;
				mapRadiusY = 2.0f * objItem[h][w]->GetScale().y;

				if (pos.x <= mapX + mapRadiusX && mapX - mapRadiusX <= pos.x)
				{
					if (mapY + mapRadiusY + radiusY > pos.y && mapY < oldPos.y)
					{
						pos.y = mapY + mapRadiusY + radiusY;
						hitFlag = true;
						height = h;
						width = w;
					}
					else if (mapY - mapRadiusY - radiusY < pos.y && mapY > oldPos.y)
					{
						pos.y = mapY - mapRadiusY - radiusY;
						hitFlag = true;
						height = h;
						width = w;
					}
				}
				if (pos.y <= mapY + mapRadiusY && mapY - mapRadiusY <= pos.y)
				{
					if (mapX + mapRadiusX + radiusX > pos.x && mapX < oldPos.x)
					{
						pos.x = mapX + mapRadiusX + radiusX;
						hitFlag = true;
						height = h;
						width = w;
					}
					else if (mapX - mapRadiusX - radiusX < pos.x && mapX > oldPos.x)
					{
						pos.x = mapX - mapRadiusX - radiusX;
						hitFlag = true;
						height = h;
						width = w;
					}
				}
			}
		}
	}

	return hitFlag;
}