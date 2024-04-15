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
	modelAxe_.reset(Model::CreateFromOBJ("axe", true));
	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
	// Player&followCamera
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	// 自キャラモデル
	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(), modelFighterR_arm_.get(),
	                                    modelFighterL_leg_.get(), modelFighterR_leg_.get(),
	                                    modelAxe_.get()};
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
	for (int i = 0; i < 6; i++) {
		door_[i] = std::make_unique<DoorOBJ>();
	}
	doorModel_[0].reset(Model::CreateFromOBJ("doorKnob1", true));
	doorModel_[1].reset(Model::CreateFromOBJ("doorKnob2", true));

	door_[0]->Initialize(doorModel_[0].get(), doorModel_[1].get(), {49.5f, 0.0f, -89.0f,},0.0f);
	door_[1]->Initialize(doorModel_[0].get(), doorModel_[1].get(), {-88.0f, 0.0f, -135.2f},0.0f);
	door_[2]->Initialize(doorModel_[0].get(), doorModel_[1].get(), {-129.0f, 0.0f, -48.8f},0.0f);
	door_[3]->Initialize(doorModel_[0].get(), doorModel_[1].get(), {-130.0f, 17.0f, -84.5f},0.0f);
	door_[4]->Initialize(doorModel_[0].get(), doorModel_[1].get(), {107.0f, 0.0f, -34.3f}, 1.57f*3.0f);
	door_[5]->Initialize(doorModel_[0].get(), doorModel_[1].get(), {106.6f, 0.0f, 56.3f}, 1.57f * 3.0f);

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
	
	//uiの生成
	ui_ = std::make_unique<UI>();
	// ui
	ui_->Initialize();
	isWindow_ = false;
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
	switch (stageNo) {
	case Stage::kIsland:

		ground_->Update();
		skydome_->Update();
		door_[0]->Update();
		door_[1]->Update();
		door_[2]->Update();
		door_[3]->Update();
		door_[4]->Update2();
		door_[5]->Update2();
		break;

	case Stage::kDesert:

		break;

	case Stage::kVolcano:

		ground_->Update();

		break;
	}
	
	///更新
	if (isWindow_==false) {
		player_->Update();
	}
	debugCamera_->Update();
	bomm_->Update();
	
	/*collisionManager_->UpdateWorldtransform();*/
	ChackAllCollisions();
	
	
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

	HouseCollision();

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
		door_[1]->Draw(viewProjection_);
		door_[2]->Draw(viewProjection_);
		door_[3]->Draw(viewProjection_);
		door_[4]->Draw(viewProjection_);
		door_[5]->Draw(viewProjection_);

		break;

	case Stage::kDesert:

		break;

	case Stage::kVolcano:

		ground_->Draw(viewProjection_);

		break;
	}

	//////////////////////////
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
	player_->ActionbuttonDraw();
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// window
		if (player_->SetActionbutton() == 1 && joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A) {
			isWindow_ = true;
			player_->SetMotion();
		}
		if (player_->SetActionbutton() == 1 && joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {
			isWindow_ = false;
		}
	}
	// 爆弾の強化ウィンドウ
	if (player_->SetActionbutton() ==1 && isWindow_ == true) {
		ui_->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::SceneReset() {}

void GameScene::HouseCollision() {
	Vector3 posA = player_->GetWorldPosition();
	
	Vector3 posB = door_[0]->GetWorldPosition();
	Vector3 posC = door_[1]->GetWorldPosition();
	Vector3 posD = door_[2]->GetWorldPosition();
	Vector3 posF = door_[4]->GetWorldPosition();
	Vector3 posG = door_[5]->GetWorldPosition();

	// ドアの判定
	if (posB.x + 7.0f >= posA.x && posB.x <= posA.x && posB.z <= posA.z - 1.5f &&
	    posB.z + 4.0f >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[0]->SetKeyFlag(true);
		}
	}
	if (door_[0]->GetKeyFlag() == true) {
		door_[0]->Collision();
	}

	// ドアの判定
	if (posC.x + 7.0f >= posA.x && posC.x <= posA.x && posC.z <= posA.z - 1.5f &&
	    posC.z + 4.0f >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[1]->SetKeyFlag(true);
		}
	}
	if (door_[1]->GetKeyFlag() == true) {
		door_[1]->Collision();
	}

	// ドアの判定
	if (posD.x + 7.0f >= posA.x && posD.x <= posA.x && posD.z <= posA.z - 1.5f &&
	    posD.z + 4.0f >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[2]->SetKeyFlag(true);
		}
	}
	if (door_[2]->GetKeyFlag() == true) {
		door_[2]->Collision();
	}

	// ドアの判定
	if (posF.x+3.0f >= posA.x && posF.x-5.0f <= posA.x && posF.z <= posA.z &&
	    posF.z+8.0f >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[4]->SetKeyFlag(true);
		}
	}
	if (door_[4]->GetKeyFlag() == true) {
		door_[4]->Collision();
	}

	// ドアの判定
	if (posG.x + 3.0f >= posA.x && posG.x - 5.0f <= posA.x && posG.z <= posA.z &&
	    posG.z+7.0f  >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[5]->SetKeyFlag(true);
		}
	}
	if (door_[5]->GetKeyFlag() == true) {
		door_[5]->Collision();
	}

	// 家の当たり判定
	if (posA.x >= 20.5f && posA.x <= 23.0f && posA.z <= -88.0f && posA.z >= -139.5f) {
		player_->SetTranslationX(20.5f);
	}
	if (posA.x >= 82.0f && posA.x <= 83.5f && posA.z <= -88.0f && posA.z >= -139.5f) {
		player_->SetTranslationX(83.5f);
	}
	if (posA.x >= 22.0f && posA.x <= 82.0f && posA.z <= -86.5f && posA.z >= -88.0f) {
		player_->SetTranslationZ(-86.5f);
	}
	if (posA.x >= 22.0f && posA.x <= 82.0f && posA.z <= -137.5f && posA.z >= -140.5f) {
		player_->SetTranslationZ(-140.5f);
	}

	if (posA.x >= 104.5f && posA.x <= 108.0f && posA.z <= -14.5f && posA.z >= -77.0f) {
		player_->SetTranslationX(104.5f);
	}
	if (posA.x >= 164.0f && posA.x <= 165.5f && posA.z <= -14.5f && posA.z >= -77.0f) {
		player_->SetTranslationX(165.5f);
	}
	if (posA.x >= 105.0f && posA.x <= 165.0f && posA.z <= -14.0f && posA.z >= -15.5f) {
		player_->SetTranslationZ(-14.0f);
	}
	if (posA.x >= 105.0f && posA.x <= 165.0f && posA.z <= -77.5f && posA.z >= -79.0f) {
		player_->SetTranslationZ(-79.0f);
	}

	if (posA.x >= 104.0f && posA.x <= 106.0f && posA.z <= 87.0f && posA.z >= 29.0f) {
		player_->SetTranslationX(104.0f);
	}
	if (posA.x >= 155.5f && posA.x <= 157.0f && posA.z <= 87.0f && posA.z >= 29.0f) {
		player_->SetTranslationX(157.0f);
	}
	if (posA.x >= 104.5f && posA.x <= 156.0f && posA.z <= 87.5f && posA.z >= 86.0f) {
		player_->SetTranslationZ(87.5f);
	}
	if (posA.x >= 104.5f && posA.x <= 156.5f && posA.z <= 30.0f && posA.z >= 28.5f) {
		player_->SetTranslationZ(28.5f);
	}

	if (posA.x >= 83.5f && posA.x <= 85.0f && posA.z <= 249.5f && posA.z >= 145.5f) {
		player_->SetTranslationX(83.5f);
	}
	if (posA.x >= 158.5f && posA.x <= 160.0f && posA.z <= 249.5f && posA.z >= 145.5f) {
		player_->SetTranslationX(160.0f);
	}
	if (posA.x >= 84.0f && posA.x <= 159.5f && posA.z <= 250.0f && posA.z >= 248.5f) {
		player_->SetTranslationZ(250.0f);
	}
	if (posA.x >= 84.0f && posA.x <= 159.5f && posA.z <= 146.5f && posA.z >= 145.0f) {
		player_->SetTranslationZ(145.0f);
	}

	if (posA.x >= -58.0f && posA.x <= -56.5f && posA.z <= -42.5f && posA.z >= -62.5f) {
		player_->SetTranslationX(-58.0f);
	}
	if (posA.x >= -37.0f && posA.x <= -35.5f && posA.z <= -42.5f && posA.z >= -62.5f) {
		player_->SetTranslationX(-35.5f);
	}
	if (posA.x >= -57.3f && posA.x <= -36.2f && posA.z <= -42.0f && posA.z >= -43.5f) {
		player_->SetTranslationZ(-42.0f);
	}
	if (posA.x >= -57.3f && posA.x <= -36.2f && posA.z <= -61.5f && posA.z >= -63.0f) {
		player_->SetTranslationZ(-63.0f);
	}

	// 下壁          //下                //上                 //左                //右
	if (posA.x >= -94.5f && posA.x <= -93.0f && posA.z <= -133.0f && posA.z >= -190.5f) {
		player_->SetTranslationX(-94.5f);
	}
	// 上壁          //下                //上                 //左                //右
	if (posA.x >= -52.0f && posA.x <= -50.5f && posA.z <= -133.0f && posA.z >= -190.5f) {
		player_->SetTranslationX(-50.5f);
	}
	// 左壁          //下                //上                 //左                //右
	if (posA.x >= -94.0f && posA.x <= -50.0f && posA.z <= -132.5f && posA.z >= -134.0f) {
		player_->SetTranslationZ(-132.5f);
	}
	// 右壁          //下                //上                 //左                //右
	if (posA.x >= -94.0f && posA.x <= -50.0f && posA.z <= -189.5f && posA.z >= -191.0f) {
		player_->SetTranslationZ(-191.0f);
	}
	// 上壁          //下                //上                 //左                //右
	if (posA.x >= -25.5f && posA.x <= -24.0f && posA.z <= -162.5f && posA.z >= -190.5f) {
		player_->SetTranslationX(-24.0f);
	}
	// 左壁          //下                //上                 //左                //右
	if (posA.x >= -55.0f && posA.x <= -24.5f && posA.z <= -163.5f && posA.z >= -165.0f) {
		player_->SetTranslationZ(-163.5f);
	}
	// 右壁          //下                //上                 //左                //右
	if (posA.x >= -55.0f && posA.x <= -24.5f && posA.z <= -189.5f && posA.z >= -191.0f) {
		player_->SetTranslationZ(-191.0f);
	}

	// 下壁          //下                //上                 //左                //右
	if (posA.x >= -161.0f && posA.x <= -159.5f && posA.z <= -47.5f && posA.z >= -107.5f) {
		player_->SetTranslationX(-161.0f);
	}
	// 上壁          //下                //上                 //左                //右
	if (posA.x >= -100.0f && posA.x <= -98.5f && posA.z <= -47.5f && posA.z >= -107.5f) {
		player_->SetTranslationX(-98.5f);
	}
	// 左壁          //下                //上                 //左                //右
	if (posA.x >= -160.5f && posA.x <= -99.0f && posA.z <= -47.0f && posA.z >= -49.0f) {
		player_->SetTranslationZ(-47.0f);
	}
	// 右壁          //下                //上                 //左                //右
	if (posA.x >= -160.5f && posA.x <= -99.0f && posA.z <= -106.5f && posA.z >= -108.0f) {
		player_->SetTranslationZ(-108.0f);
	}

	// 下壁          //下                //上                 //左                //右
	if (posA.x >= -185.5f && posA.x <= -184.0f && posA.z <= 25.5f && posA.z >= -15.5f) {
		player_->SetTranslationX(-185.5f);
	}
	// 上壁          //下                //上                 //左                //右
	if (posA.x >= -121.5f && posA.x <= -120.0f && posA.z <= 25.5f && posA.z >= -15.5f) {
		player_->SetTranslationX(-120.0f);
	}
	// 左壁          //下                //上                 //左                //右
	if (posA.x >= -185.0f && posA.x <= -119.5f && posA.z <= 26.0f && posA.z >= 24.5f) {
		player_->SetTranslationZ(26.0f);
	}
	// 右壁          //下                //上                 //左                //右
	if (posA.x >= -185.0f && posA.x <= -119.5f && posA.z <= -14.5f && posA.z >= -16.0f) {
		player_->SetTranslationZ(-16.0f);
	}

	// 下壁          //下                //上                 //左                //右
	if (posA.x >= -92.0f && posA.x <= -90.5f && posA.z <= 114.5f && posA.z >= 63.5f) {
		player_->SetTranslationX(-92.0f);
	}
	// 上壁          //下                //上                 //左                //右
	if (posA.x >= -55.5f && posA.x <= -54.0f && posA.z <= 114.5f && posA.z >= 63.5f) {
		player_->SetTranslationX(-54.0f);
	}
	// 左壁          //下                //上                 //左                //右
	if (posA.x >= -91.5f && posA.x <= -54.0f && posA.z <= 115.5f && posA.z >= 114.0f) {
		player_->SetTranslationZ(115.5f);
	}
	// 右壁          //下                //上                 //左                //右
	if (posA.x >= -91.5f && posA.x <= -54.0f && posA.z <= 64.5f && posA.z >= 63.0f) {
		player_->SetTranslationZ(63.0f);
	}

	// 下壁          //下                //上                 //左                //右
	if (posA.x >= -63.5f && posA.x <= -62.0f && posA.z <= 180.5f && posA.z >= 136.0f) {
		player_->SetTranslationX(-63.5f);
	}
	// 上壁          //下                //上                 //左                //右
	if (posA.x >= -13.0f && posA.x <= -11.5f && posA.z <= 180.5f && posA.z >= 136.0f) {
		player_->SetTranslationX(-11.5f);
	}
	// 左壁          //下                //上                 //左                //右
	if (posA.x >= -63.0f && posA.x <= -12.0f && posA.z <= 181.0f && posA.z >= 179.5f) {
		player_->SetTranslationZ(181.0f);
	}
	// 右壁          //下                //上                 //左                //右
	if (posA.x >= -63.0f && posA.x <= -12.0f && posA.z <= 137.0f && posA.z >= 135.5f) {
		player_->SetTranslationZ(135.5f);
	}

	// 下壁          //下                //上                 //左                //右
	if (posA.x >= 229.5f && posA.x <= 231.0f && posA.z <= -238.5f && posA.z >= -272.0f) {
		player_->SetTranslationX(229.5f);
	}
	// 上壁          //下                //上                 //左                //右
	if (posA.x >= 262.0f && posA.x <= 263.5f && posA.z <= -238.5f && posA.z >= -272.0f) {
		player_->SetTranslationX(263.5f);
	}
	// 左壁          //下                //上                 //左                //右
	if (posA.x >= 230.0f && posA.x <= 263.0f && posA.z <= -238.0f && posA.z >= -239.5f) {
		player_->SetTranslationZ(-238.0f);
	}
	// 右壁          //下                //上                 //左                //右
	if (posA.x >= 230.0f && posA.x <= 263.0f && posA.z <= -271.0f && posA.z >= -272.5f) {
		player_->SetTranslationZ(-272.5f);
	}

	// 下壁          //下                //上                 //左                //右
	if (posA.x >= -262.0f && posA.x <= -260.5f && posA.z <= 256.3f && posA.z >= 180.0f) {
		player_->SetTranslationX(-262.0f);
	}
	// 上壁          //下                //上                 //左                //右
	if (posA.x >= -240.0f && posA.x <= -238.5f && posA.z <= 230.0f && posA.z >= 180.0f) {
		player_->SetTranslationX(-238.5f);
	}
	// 左壁          //下                //上                 //左                //右
	if (posA.x >= -261.3f && posA.x <= -161.7f && posA.z <= 257.0f && posA.z >= 255.5f) {
		player_->SetTranslationZ(257.0f);
	}
	// 右壁          //下                //上                 //左                //右
	if (posA.x >= -261.3f && posA.x <= -239.0f && posA.z <= 181.0f && posA.z >= 179.3f) {
		player_->SetTranslationZ(179.3f);
	}
	// 右壁          //下                //上                 //左                //右
	if (posA.x >= -245.0f && posA.x <= -195.0f && posA.z <= 229.5f && posA.z >= 228.0f) {
		player_->SetTranslationZ(228.0f);
	}
	// 下壁          //下                //上                 //左                //右
	if (posA.x >= -209.5f && posA.x <= -208.0f && posA.z <= 229.0f && posA.z >= 180.5f) {
		player_->SetTranslationX(-209.5f);
	}
	// 右壁          //下                //上                 //左                //右
	if (posA.x >= -208.7f && posA.x <= -161.7f && posA.z <= 180.5f && posA.z >= 179.0f) {
		player_->SetTranslationZ(179.0f);
	}
	// 上壁          //下                //上                 //左                //右
	if (posA.x >= -162.5f && posA.x <= -161.0f && posA.z <= 256.3f && posA.z >= 179.7f) {
		player_->SetTranslationX(-161.0f);
	}
}
