#pragma once
#include"Player.h"
#include <Sprite.h>
class UI {
public:
	// �f�X�g���N�^

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	

private:
	// ���L����
	std::unique_ptr<Player> player_;
	// �X�v���C�g
	Sprite* spriteBommActionButton_ = nullptr; // ���e�̃A�N�V�����{�^��
	
};
