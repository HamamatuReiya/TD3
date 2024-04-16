#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "FollowCamera.h"
#include "Ground.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Bomm.h"
#include <Scene.h>
#include "CollisionManager.h"
#include "Collider.h"
#include "UI.h"
#include <Stage.h>
#include "HouseStageOBJ.h"
#include "DoorOBJ.h"
#include "ForestGround.h"
#include "ForestTreeLeaf.h"
#include "ForestTreeWood.h"
#include "ForestWood.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public StageSelect {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void ChackAllCollisions();

public:
	void SceneReset();

	bool isSceneEnd_ = false;

	bool IsSceneEnd() { return isSceneEnd_; }
	SceneType NextScene() { return SceneType::kTitle; }

private:
	void HouseCollision();

	void HouseStage();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	std::unique_ptr<Model> model_ = nullptr;

	// 3Dモデル
	std::unique_ptr<Model> playerModel_ = nullptr;
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;
	std::unique_ptr<Model> modelFighterL_leg_;
	std::unique_ptr<Model> modelFighterR_leg_;
	std::unique_ptr<Model> modelAxe_;

	// 自キャラ
	std::unique_ptr<Player> player_;

	// デバックカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	bool isDebugCameraActive_;

	// 3Dモデル
	std::unique_ptr<Model> groundModel_ = nullptr;
	// 地面
	std::unique_ptr<Ground> ground_;

	// 3Dモデル
	std::unique_ptr<Model> skydomeModel_ = nullptr;
	// 天球
	std::unique_ptr<Skydome> skydome_;

	// 3Dモデル
	std::unique_ptr<Model> bommModel_ = nullptr;
	// 爆弾
	std::unique_ptr<Bomm> bomm_;

	// 追従カメラ
	std::unique_ptr<FollowCamera> followCamera_;

	// 衝突マネージャ
	std::unique_ptr<CollisionManager> collisionManager_;

	// スプライト
	Sprite* spriteBommActionButton_ = nullptr; // 爆弾のアクションボタン

	std::unique_ptr<HouseStageOBJ> house_;
	// 家ステージのモデル
	std::unique_ptr<Model> houseModel_[99] = {nullptr};

	// ドア
	std::unique_ptr<DoorOBJ> door_[11];
	std::unique_ptr<Model> doorModel_[2] = {nullptr};


	/*森エリア*/
	// 3Dモデル
	std::unique_ptr<Model> forestGroundModel_ = nullptr;
	// 森の地面
	std::unique_ptr<ForestGround> forestGround_;

	// 3Dモデル
	std::unique_ptr<Model> forestTreeLeafModel_[4] = {nullptr};
	// 木の葉
	std::unique_ptr<ForestTreeLeaf> forestTreeLeaf_;

	// 3Dモデル
	std::unique_ptr<Model> forestTreeWoodModel_ = nullptr;
	// 木
	std::unique_ptr<ForestTreeWood> forestTreeWood_;

	// 3Dモデル
	std::unique_ptr<Model> forestWoodModel_ = nullptr;
	// 丸太
	std::unique_ptr<ForestWood> forestWood_;

	/*森エリア終わり*/

	// ドア
	std::unique_ptr<DoorOBJ> door2_[2];
	std::unique_ptr<Model> doorModel2_[2] = {nullptr};

	//UI
	std::unique_ptr<UI> ui_;
	bool isWindow_;
	bool isExclamation_;
	

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
