#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include <Stage.h>
#include "Scene.h"

class ResultScene {
public: // �����o�֐�
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	ResultScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ResultScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

public:
	void SceneReset();

	bool isSceneEnd_ = false;

	bool IsSceneEnd() { return isSceneEnd_; }
	SceneType NextScene() { return SceneType::kTitle; }

private: // �����o�ϐ�

	DirectXCommon* dxCommon_ = nullptr;
	// ���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	// �r���[�v���W�F�N�V����
	ViewProjection viewProjection_;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
};
