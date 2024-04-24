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
#include "Tutorial.h"

#include "ItemCounter.h"
#include "Stone.h"
#include "Gold.h"
#include "Jushi.h"
#include "Shell.h"

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
	/// <summary>
	/// 石の発生
	/// </summary>
	void StoneSpawn(Vector3 position);
	/// <summary>
	/// 金の発生
	/// </summary>
	void GoldSpawn(Vector3 position);
	/// <summary>
	/// 樹脂の発生
	/// </summary>
	void JushiSpawn(Vector3 position);
	/// <summary>
	/// 貝の発生
	/// </summary>
	void ShellSpawn(Vector3 position);

    /// <summary>
    /// 素材発生データの読み込み  
    /// </summary>
	void LoadMaterialPopData();
private:
	void HouseCollision();

	//素材の当たり
	void MaterialCheckCollisions();

	/// <summary>
	/// 素材発生コマンドの更新
	/// </summary>
	void UpdateStonePopCommands();
	void UpdateGoldPopCommands();
	void UpdateJushiPopCommands();
	void UpdateShellPopCommands();
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

	std::unique_ptr<Model> rockModel_[10] = {nullptr};

	// ドア
	std::unique_ptr<DoorOBJ> door2_[2];
	std::unique_ptr<Model> doorModel2_[2] = {nullptr};
	// ドア
	std::unique_ptr<DoorOBJ> door_[11];
	std::unique_ptr<Model> doorModel_[2] = {nullptr};

	//梯子
	std::unique_ptr<Model> ladderModel_[8] = {nullptr};

	//素材
	//std::list<BommParts*> bommParts_;
	std::list<Stone*> stones_;
	std::list<Gold*> golds_;
	std::list<Jushi*> jushis_;
	std::list<Shell*> shells_;

	//  3Dモデル
	std::unique_ptr<Model> modelStone_;
	std::unique_ptr<Model> modelGold_;
	std::unique_ptr<Model> modelJushi_;
	std::unique_ptr<Model> modelShell_;

	// 素材発生コマンド
	std::stringstream stonePopCommands;
	std::stringstream goldPopCommands;
	std::stringstream jushiPopCommands;
	std::stringstream shellPopCommands;

	//素材の待機中のフラグ
	bool stonePopWaitFlag = true;
	bool goldPopWaitFlag = true;
	bool jushiPopWaitFlag = true;
	bool shellPopWaitFlag = true;

	// 待機タイマー
	int32_t stonePopWaitTimer = 0;
	int32_t goldPopWaitTimer = 0;
	int32_t jushiPopWaitTimer = 0;
	int32_t shellPopWaitTimer = 0;

	// 素材の所持数表示
	std::unique_ptr<ItemCounter> itemCounter_;

	//素材の所持数
	int stoneCount_ = 0;
	int goldCount_ = 0;
	int jushiCount_ = 0;
	int shellCount_ = 0;

	/*森エリア*/
	// 3Dモデル
	std::unique_ptr<Model> forestGroundModel_ = nullptr;
	// 森の地面
	std::unique_ptr<ForestGround> forestGround_;

	// 3Dモデル
	std::unique_ptr<Model> forestTreeLeafModel_ = nullptr;
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

	

	//UI
	std::unique_ptr<UI> ui_;
	bool isWindow_;
	bool isExclamation_[16];
	// チュートリアル
	std::unique_ptr<Tutorial> tutorial_;
	

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
