#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデル生成
	model_.reset(Model::Create());
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// デバックカメラの生成
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// 追従カメラの生成
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	// 自キャラの生成
	player_ = std::make_unique<Player>();
	// 3Dモデルの生成
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));
	modelFighterL_leg_.reset(Model::CreateFromOBJ("float_L_leg", true));
	modelFighterR_leg_.reset(Model::CreateFromOBJ("float_R_leg", true));
	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
	// Player&followCamera
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	// 自キャラモデル
	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(), modelFighterR_arm_.get(),
	                                    modelFighterL_leg_.get(), modelFighterR_leg_.get()};
	// 自キャラの初期化
	player_->Initialize(playerModels);

	// 天球の生成
	skydome_ = std::make_unique<Skydome>();
	// 3Dモデルの生成
	skydomeModel_.reset(Model::CreateFromOBJ("skydome", true));
	// 天球の初期化
	skydome_->Initialize(skydomeModel_.get());

	// 地面の生成
	ground_ = std::make_unique<Ground>();
	// 3Dモデルの生成
	groundModel_.reset(Model::CreateFromOBJ("ground", true));
	// 地面の初期化
	ground_->Initialize(groundModel_.get());

	// 爆弾の生成
	bomm_ = std::make_unique<Bomm>();
	// 3Dモデルの生成
	bommModel_.reset(Model::CreateFromOBJ("bom", true));

	// ドアモデル
	for (int i = 0; i < 10; i++) {
		door_[i] = std::make_unique<DoorOBJ>();
	}
	doorModel_[0].reset(Model::CreateFromOBJ("doorKnob1", true));
	doorModel_[1].reset(Model::CreateFromOBJ("doorKnob2", true));

	door_[0]->Initialize(doorModel_[0].get(), doorModel_[1].get(), {49.5f, 0.0f, -89.0f});

	// 家モデル
	house_ = std::make_unique<HouseStageOBJ>();
	houseModel_[0].reset(Model::CreateFromOBJ("houseGround", true));
	houseModel_[1].reset(Model::CreateFromOBJ("house1", true));
	houseModel_[2].reset(Model::CreateFromOBJ("house2", true));
	houseModel_[3].reset(Model::CreateFromOBJ("house3", true));
	houseModel_[4].reset(Model::CreateFromOBJ("house4", true));
	houseModel_[5].reset(Model::CreateFromOBJ("house5", true));
	houseModel_[6].reset(Model::CreateFromOBJ("house6", true));
	houseModel_[7].reset(Model::CreateFromOBJ("house7", true));
	houseModel_[8].reset(Model::CreateFromOBJ("house8", true));
	houseModel_[9].reset(Model::CreateFromOBJ("house9", true));
	houseModel_[10].reset(Model::CreateFromOBJ("house10", true));
	houseModel_[11].reset(Model::CreateFromOBJ("house11", true));
	houseModel_[12].reset(Model::CreateFromOBJ("house12", true));
	houseModel_[13].reset(Model::CreateFromOBJ("house13", true));
	houseModel_[14].reset(Model::CreateFromOBJ("house14", true));
	houseModel_[15].reset(Model::CreateFromOBJ("house15", true));
	houseModel_[16].reset(Model::CreateFromOBJ("house16", true));
	houseModel_[17].reset(Model::CreateFromOBJ("house17", true));
	houseModel_[18].reset(Model::CreateFromOBJ("house18", true));
	houseModel_[19].reset(Model::CreateFromOBJ("house19", true));
	houseModel_[20].reset(Model::CreateFromOBJ("house20", true));
	houseModel_[21].reset(Model::CreateFromOBJ("house21", true));
	houseModel_[22].reset(Model::CreateFromOBJ("house22", true));
	houseModel_[23].reset(Model::CreateFromOBJ("house23", true));
	houseModel_[24].reset(Model::CreateFromOBJ("house24", true));
	houseModel_[25].reset(Model::CreateFromOBJ("house25", true));
	houseModel_[26].reset(Model::CreateFromOBJ("house26", true));
	houseModel_[27].reset(Model::CreateFromOBJ("house27", true));
	houseModel_[28].reset(Model::CreateFromOBJ("house28", true));
	houseModel_[29].reset(Model::CreateFromOBJ("house29", true));
	houseModel_[30].reset(Model::CreateFromOBJ("house30", true));
	houseModel_[31].reset(Model::CreateFromOBJ("house31", true));
	houseModel_[32].reset(Model::CreateFromOBJ("house32", true));
	houseModel_[33].reset(Model::CreateFromOBJ("house33", true));
	houseModel_[34].reset(Model::CreateFromOBJ("house34", true));
	houseModel_[35].reset(Model::CreateFromOBJ("house35", true));
	houseModel_[36].reset(Model::CreateFromOBJ("house36", true));
	houseModel_[37].reset(Model::CreateFromOBJ("house37", true));
	houseModel_[38].reset(Model::CreateFromOBJ("house38", true));
	houseModel_[39].reset(Model::CreateFromOBJ("house39", true));
	houseModel_[40].reset(Model::CreateFromOBJ("house40", true));
	houseModel_[41].reset(Model::CreateFromOBJ("house41", true));
	houseModel_[42].reset(Model::CreateFromOBJ("house42", true));
	houseModel_[43].reset(Model::CreateFromOBJ("house43", true));
	houseModel_[44].reset(Model::CreateFromOBJ("house44", true));
	houseModel_[45].reset(Model::CreateFromOBJ("house45", true));
	houseModel_[46].reset(Model::CreateFromOBJ("house46", true));
	houseModel_[47].reset(Model::CreateFromOBJ("house47", true));
	houseModel_[48].reset(Model::CreateFromOBJ("house48", true));
	houseModel_[49].reset(Model::CreateFromOBJ("house49", true));
	houseModel_[50].reset(Model::CreateFromOBJ("house50", true));
	houseModel_[51].reset(Model::CreateFromOBJ("house51", true));
	houseModel_[52].reset(Model::CreateFromOBJ("house52", true));
	houseModel_[53].reset(Model::CreateFromOBJ("house53", true));
	houseModel_[54].reset(Model::CreateFromOBJ("house54", true));
	houseModel_[55].reset(Model::CreateFromOBJ("house55", true));
	houseModel_[56].reset(Model::CreateFromOBJ("house56", true));
	houseModel_[57].reset(Model::CreateFromOBJ("house57", true));
	houseModel_[58].reset(Model::CreateFromOBJ("house58", true));
	houseModel_[59].reset(Model::CreateFromOBJ("house59", true));
	houseModel_[60].reset(Model::CreateFromOBJ("house60", true));
	houseModel_[61].reset(Model::CreateFromOBJ("house61", true));
	houseModel_[62].reset(Model::CreateFromOBJ("house62", true));
	houseModel_[63].reset(Model::CreateFromOBJ("house63", true));
	houseModel_[64].reset(Model::CreateFromOBJ("house64", true));
	houseModel_[65].reset(Model::CreateFromOBJ("house65", true));
	houseModel_[66].reset(Model::CreateFromOBJ("house66", true));
	houseModel_[67].reset(Model::CreateFromOBJ("house67", true));
	houseModel_[68].reset(Model::CreateFromOBJ("house68", true));
	houseModel_[69].reset(Model::CreateFromOBJ("house69", true));
	houseModel_[70].reset(Model::CreateFromOBJ("house70", true));
	houseModel_[71].reset(Model::CreateFromOBJ("house71", true));
	houseModel_[72].reset(Model::CreateFromOBJ("house72", true));
	houseModel_[73].reset(Model::CreateFromOBJ("house73", true));
	houseModel_[74].reset(Model::CreateFromOBJ("house74", true));
	houseModel_[75].reset(Model::CreateFromOBJ("house75", true));
	houseModel_[76].reset(Model::CreateFromOBJ("house76", true));
	houseModel_[77].reset(Model::CreateFromOBJ("house77", true));
	houseModel_[78].reset(Model::CreateFromOBJ("house78", true));

	house_->Initialize(
	    houseModel_[0].get(), houseModel_[1].get(), houseModel_[2].get(), houseModel_[3].get(),
	    houseModel_[4].get(), houseModel_[5].get(), houseModel_[6].get(), houseModel_[7].get(),
	    houseModel_[8].get(), houseModel_[9].get(), houseModel_[10].get(), houseModel_[11].get(),
	    houseModel_[12].get(), houseModel_[13].get(), houseModel_[14].get(), houseModel_[15].get(),
	    houseModel_[16].get(), houseModel_[17].get(), houseModel_[18].get(), houseModel_[19].get(),
	    houseModel_[20].get(), houseModel_[21].get(), houseModel_[22].get(), houseModel_[23].get(),
	    houseModel_[24].get(), houseModel_[25].get(), houseModel_[26].get(), houseModel_[27].get(),
	    houseModel_[28].get(), houseModel_[29].get(), houseModel_[30].get(), houseModel_[31].get(),
	    houseModel_[32].get(), houseModel_[33].get(), houseModel_[34].get(), houseModel_[35].get(),
	    houseModel_[36].get(), houseModel_[37].get(), houseModel_[38].get(), houseModel_[39].get(),
	    houseModel_[40].get(), houseModel_[41].get(), houseModel_[42].get(), houseModel_[43].get(),
	    houseModel_[44].get(), houseModel_[45].get(), houseModel_[46].get(), houseModel_[47].get(),
	    houseModel_[48].get(), houseModel_[49].get(), houseModel_[50].get(), houseModel_[51].get(),
	    houseModel_[52].get(), houseModel_[53].get(), houseModel_[54].get(), houseModel_[55].get(),
	    houseModel_[56].get(), houseModel_[57].get(), houseModel_[58].get(), houseModel_[59].get(),
	    houseModel_[60].get(), houseModel_[61].get(), houseModel_[62].get(), houseModel_[63].get(),
	    houseModel_[64].get(), houseModel_[65].get(), houseModel_[66].get(), houseModel_[67].get(),
	    houseModel_[68].get(), houseModel_[69].get(), houseModel_[70].get(), houseModel_[71].get(),
	    houseModel_[72].get(), houseModel_[73].get(), houseModel_[74].get(), houseModel_[75].get(),
	    houseModel_[76].get(), houseModel_[77].get(), houseModel_[78].get());
	
	// 爆弾モデル
	std::vector<Model*> bommModels = {bommModel_.get()};
	// 爆弾の初期化
	bomm_->Initialize(bommModels);
	// 衝突マネージャの生成
	collisionManager_ = std::make_unique<CollisionManager>();
	////コライダー可視化
	//collisionManager_->Initialize();
	// テクスチャ
	uint32_t textureBommActionButton = TextureManager::Load("ActionButton.png");
	// スプライト生成
	spriteBommActionButton_ = Sprite::Create(
	    textureBommActionButton, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
}

void GameScene::Update() {
	player_->Update();
	debugCamera_->Update();
	ground_->Update();
	bomm_->Update();
	skydome_->Update();
	door_[0]->Update();
	/*collisionManager_->UpdateWorldtransform();*/
	ChackAllCollisions();

	


	switch (stageNo) {
	case Stage::kIsland:

		ground_->Update();
		skydome_->Update();

		break;

	case Stage::kDesert:

		break;

	case Stage::kVolcano:

		ground_->Update();

		break;
	}

	player_->Update();

	bomm_->Update();

	
	// 追従カメラの更新
	followCamera_->Update();

	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.matView = followCamera_->GetViewProjection().matView;

	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_C)) {
		isDebugCameraActive_ = true;
	} else if (input_->TriggerKey(DIK_B)) {
		isDebugCameraActive_ = false;
	}
#endif
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.TransferMatrix();
	}

}
void GameScene::ChackAllCollisions() {
	// 衝突マネージャのリセット
	collisionManager_->Reset();
	// コライダーをリストに登録
	collisionManager_->AddCollider(player_.get());

	collisionManager_->AddCollider(bomm_.get());

	// 衝突判定と応答
	collisionManager_->ChackAllCollisions();

	Vector3 posA = player_->GetWorldPosition();
	;
	Vector3 posB = door_[0]->GetWorldPosition();

	if (posB.x + 3.5f >= posA.x && posB.x <= posA.x && posB.z <= posA.z - 1.5f &&
	    posB.z+13.0f >= posA.z ) {
		if (player_->GetIsPushX() == true) {
			door_[0]->SetKeyFlag(true);
		}
	}
	if (door_[0]->GetKeyFlag() == true) {
		door_[0]->Collision();
	}

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	switch (stageNo) {
	case Stage::kIsland:

		//ground_->Draw(viewProjection_);
		//skydome_->Draw(viewProjection_);
		house_->Draw(viewProjection_);
		door_[0]->Draw(viewProjection_);

		break;

	case Stage::kDesert:

		break;

	case Stage::kVolcano:

		ground_->Draw(viewProjection_);

		break;
	}


	player_->Draw(viewProjection_);
	bomm_->Draw(viewProjection_);
	/*collisionManager_->Draw(viewProjection_);*/
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	// 爆弾接触時のボタン
	if (player_->SetBommCollider_() == 1) {
		spriteBommActionButton_->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::SceneReset() {}
