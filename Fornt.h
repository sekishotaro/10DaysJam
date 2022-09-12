#pragma once

#include "Sprite.h"
#include <Windows.h>
#include <string>

/// <summary>
/// �f�o�b�O�p�����\��
/// </summary>
class Fornt
{
public:
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	static const int maxCharCount = 256;	// �ő啶����
	static const int fontWidth = 18;			// �t�H���g�摜��1�������̉���
	static const int fontHeight = 34;		// �t�H���g�摜��1�������̏c��
	static const int fontLineCount = 14;	// �t�H���g�摜��1�s���̕�����

	static Fornt* GetInstance();

public:

	void Initialize(UINT texnumber);

	void Finalize();

	void Print(float x, float y, float size, std::string text, ...);

	void DrawAll(ID3D12GraphicsCommandList* cmdList);

private:
	// �X�v���C�g�f�[�^�̔z��
	Sprite* spriteDatas[maxCharCount] = {};
	// �X�v���C�g�f�[�^�z��̓Y�����ԍ�
	int spriteIndex = 0;
};
