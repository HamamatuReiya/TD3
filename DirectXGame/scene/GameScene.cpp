#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>
#include <ImGuiManager.h>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	for (Stone* stone : stones_) {
		delete stone;
	}

	for (Gold* gold : golds_) {
		delete gold;
	}

	for (Jushi* jushi : jushis_) {
		delete jushi;
	}

	for (Shell* shell : shells_) {
		delete shell;
	}
}

void GameScene::Initialize() {
	
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	isSceneEnd_ = false;

	for (int i = 0; i < 11; i++) {
		houseCollisionSwitchFlag[i] = true;
	}

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

	//固定カメラ
	fixedCamera_ = std::make_unique<FixedCamera>();
	fixedCamera_->Initialize();

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

	/*森エリア*/

	// 森の地面生成
	forestGround_ = std::make_unique<ForestGround>();
	// 3Dモデルの生成
	forestGroundModel_.reset(Model::CreateFromOBJ("forestGround", true));
	// 木の葉の初期化
	forestGround_->Initialize(forestGroundModel_.get());

	// 木の葉の生成
	forestTreeLeaf_ = std::make_unique<ForestTreeLeaf>();
	// 3Dモデルの生成
	forestTreeLeafModel_.reset(Model::CreateFromOBJ("forestTreeLeaf", true));
	// 木の葉の初期化
	forestTreeLeaf_->Initialize(
	    forestTreeLeafModel_.get(), forestTreeLeafModel_.get(), forestTreeLeafModel_.get(),
	    forestTreeLeafModel_.get(), forestTreeLeafModel_.get(), forestTreeLeafModel_.get(),
	    forestTreeLeafModel_.get(), forestTreeLeafModel_.get(), forestTreeLeafModel_.get(),
	    forestTreeLeafModel_.get());

	// 木の生成
	forestTreeWood_ = std::make_unique<ForestTreeWood>();
	// 3Dモデルの生成
	forestTreeWoodModel_.reset(Model::CreateFromOBJ("forestTreeWood", true));
	// 木の初期化
	forestTreeWood_->Initialize(
	    forestTreeWoodModel_.get(), forestTreeWoodModel_.get(), forestTreeWoodModel_.get(),
	    forestTreeWoodModel_.get(), forestTreeWoodModel_.get(), forestTreeWoodModel_.get(),
	    forestTreeWoodModel_.get(), forestTreeWoodModel_.get(), forestTreeWoodModel_.get(),
	    forestTreeWoodModel_.get());

	// 丸太の生成
	forestWood_ = std::make_unique<ForestWood>();
	// 3Dモデルの生成
	forestWoodModel_.reset(Model::CreateFromOBJ("forestWood", true));
	// 木の初期化
	forestWood_->Initialize(forestWoodModel_.get());

	// チュートリアルの生成
	tutorial_ = std::make_unique<Tutorial>();
	//チュートリアル
	tutorial_->TutorialInitialize();
	

	/*森エリア終わり*/

	//家ステージの読み込み
	HouseStage();
	
	//uiの生成
	ui_ = std::make_unique<UI>();
	// ui
	ui_->Initialize();
	isWindow_ = false;
	for (int i = 0; i < 17; i++) {
		isExclamation_[i] = false;
	}
	
	//所持数UIの生成
	itemCounter_ = std::make_unique<ItemCounter>();
	itemCounter_->Initialize();

	//時間
	timer_ = std::make_unique<Timer>();
	timer_->Initialize();

	// 爆弾強化
	bommEnhance_ = std::make_unique<BommEnhance>();
	bommEnhance_->Initialize();

	//素材のモデル
	modelStone_.reset(Model::CreateFromOBJ("stone", true));
	modelGold_.reset(Model::CreateFromOBJ("gold", true));
	modelJushi_.reset(Model::CreateFromOBJ("jushi", true));
	modelShell_.reset(Model::CreateFromOBJ("shell", true));

	LoadMaterialPopData(
	    "Resources/stonePop.csv", "Resources/goldPop.csv",
	    "Resources/jushiPop.csv", "Resources/shellPop.csv");
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

	//フェード
	//初期化処理
	uint32_t fadeTexHandle = TextureManager::Load("white.png");
	fadeSprite_ = Sprite::Create(fadeTexHandle, {0, 0});

	fadeColor_.w = 0.0f;

	// 爆発の生成
	explosion_ = std::make_unique<Explosion>();
	// 3Dモデルの生成
	explosionModel_.reset(Model::CreateFromOBJ("explosion", true));
	// 爆発の初期化
	explosion_->Initialize(explosionModel_.get());

}

void GameScene::Update() {
	if (input_->TriggerKey(DIK_SPACE)) {
		clearFlag = true;
		isFade = true;
	}
	if (isFade == true) {
		
		fadeColor_.w += 0.01f;
		fadeSprite_->SetColor(fadeColor_);
	}
	if (fadeColor_.w >= 1.0f) {
		fadeColor_.w = 0.0f;
		isFade = false;
		clearFlag = false;
		isSceneEnd_ = true;
	}
	//player_->Update();
	debugCamera_->Update();
	ground_->Update();
	bomm_->Update();
	skydome_->Update();
	/*森エリア*/
	// 森の地面
	forestGround_->Update();
	// 木の葉
	forestTreeLeaf_->Update();
	// 木
	forestTreeWood_->Update();
	// 丸太
	forestWood_->Update();
	/*森エリア終わり*/
	/*collisionManager_->UpdateWorldtransform();*/
	ChackAllCollisions();

	switch (stageNo) {
	case Stage::kTutorial:
		ground_->Update();
		skydome_->Update();
		door_[0]->Update();
		door_[1]->Update();
		door_[2]->Update();
		door_[3]->Update();
		door_[4]->Update2();
		door_[5]->Update2();
		door_[6]->Update3();
		door_[7]->Update4();
		door_[8]->Update4();
		door_[9]->Update2();
		door2_[0]->Update5();
		door_[10]->Update4();
		door2_[1]->Update6();
		//チュートリアル
		tutorial_->TutorialUpdate();
		if (tutorial_->GetIsTutorialEnd_()==false) {
			player_->SetIsController(false);
			followCamera_->SetIsController(false);
		} else {
			player_->SetIsController(true);
			followCamera_->SetIsController(true);
			
		}
		
		if (tutorial_->GetIsView_() == true) {
			followCamera_->UpView();
		} else {
			followCamera_->LowView();
		}

		break;

	case Stage::kTown:
		ground_->Update();
		skydome_->Update();
		door_[0]->Update();
		door_[1]->Update();
		door_[2]->Update();
		door_[3]->Update();
		door_[4]->Update2();
		door_[5]->Update2();
		door_[6]->Update3();
		door_[7]->Update4();
		door_[8]->Update4();
		door_[9]->Update2();
		door2_[0]->Update5();
		door_[10]->Update4();
		door2_[1]->Update6();
		break;
	}
	
	///更新
	if (isWindow_==false) {
		if (clearFlag == false)
		player_->Update();
	} else {
		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
				bommEnhance_->Update(stoneCount_, goldCount_, jushiCount_, shellCount_);
				stoneCount_ = 0;
				goldCount_ = 0;
				jushiCount_ = 0;
				shellCount_ = 0;
			}
		}
	}

	//player_->SetIsController(false);
	debugCamera_->Update();
	bomm_->Update();
		
	UpdateStonePopCommands();
	UpdateGoldPopCommands();
	UpdateJushiPopCommands();
	UpdateShellPopCommands();

	for (Stone* stone : stones_) {
		stone->Update();
	}

	for (Gold* gold : golds_) {
		gold->Update();
	}

	for (Jushi* jushi : jushis_) {
		jushi->Update();
	}

	for (Shell* shell : shells_) {
		shell->Update();
	}

	MaterialCheckCollisions();

	// 所持数UIの更新
	itemCounter_->Update(stoneCount_, goldCount_, jushiCount_, shellCount_);

	time--;
	//時間更新
	timer_->Update(time);

	if (time <= 0) {
		clearFlag = true;
	}

	stones_.remove_if([](Stone* stone) {
		if (stone->IsDead()) {
			delete stone;
			return true;
		}
		return false;
	});

	golds_.remove_if([](Gold* gold) {
		if (gold->IsDead()) {
			delete gold;
			return true;
		}
		return false;
	});

	jushis_.remove_if([](Jushi* jushi) {
		if (jushi->IsDead()) {
			delete jushi;
			return true;
		}
		return false;
	});

	shells_.remove_if([](Shell* shell) {
		if (shell->IsDead()) {
			delete shell;
			return true;
		}
		return false;
	});



	// 追従カメラの更新
	if (clearFlag == false) {
		followCamera_->Update();
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
		viewProjection_.matView = followCamera_->GetViewProjection().matView;

	} else {
		fixedCamera_->Update();
		isFade = true;
		explosion_->Update();
		viewProjection_.matView = fixedCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = fixedCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	}
	

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
	case Stage::kTutorial:
		
		house_->Draw(viewProjection_);
		door_[0]->Draw(viewProjection_);
		door_[1]->Draw(viewProjection_);
		door_[2]->Draw(viewProjection_);
		door_[3]->Draw(viewProjection_);
		door_[4]->Draw(viewProjection_);
		door_[5]->Draw(viewProjection_);
		door_[6]->Draw(viewProjection_);
		door_[7]->Draw(viewProjection_);
		door_[8]->Draw(viewProjection_);
		door_[9]->Draw(viewProjection_);
		door2_[0]->Draw(viewProjection_);
		door_[10]->Draw(viewProjection_);
		door2_[1]->Draw(viewProjection_);
		break;
	case Stage::kTown:
		
		house_->Draw(viewProjection_);
		door_[0]->Draw(viewProjection_);
		door_[1]->Draw(viewProjection_);
		door_[2]->Draw(viewProjection_);
		door_[3]->Draw(viewProjection_);
		door_[4]->Draw(viewProjection_);
		door_[5]->Draw(viewProjection_);
		door_[6]->Draw(viewProjection_);
		door_[7]->Draw(viewProjection_);
		door_[8]->Draw(viewProjection_);
		door_[9]->Draw(viewProjection_);
		door2_[0]->Draw(viewProjection_);
		door_[10]->Draw(viewProjection_);
		door2_[1]->Draw(viewProjection_);

		break;

	
	}

	for (Stone* stone : stones_) {
		stone->Draw(viewProjection_);
	}

	for (Gold* gold : golds_) {
		gold->Draw(viewProjection_);
	}

	for (Jushi* jushi : jushis_) {
		jushi->Draw(viewProjection_);
	}

	for (Shell* shell : shells_) {
		shell->Draw(viewProjection_);
	}

	player_->Draw(viewProjection_);
	bomm_->Draw(viewProjection_);
	if (isFade == true) {
		explosion_->Draw(viewProjection_);
	}
	

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
	if (player_->GetActionbutton() == 1) {
		player_->ActionbuttonDraw();
	} else {
		ui_->ButtonHintDraw();
	}
	switch (stageNo) {
	case Stage::kTutorial:
		// チュートリアル
		if (tutorial_->GetIsTutorialEnd_() == false) {
			tutorial_->TutorialDraw();
		}
		break;
	case Stage::kTown:
		


		break;
	}
	itemCounter_->Draw();
	// 時間更新
	timer_->Draw();
	if (isFade == true) {
		fadeSprite_->Draw();
	}

	// ゲームパッドの状態を得る変数
	//XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// window
		if (player_->GetActionbutton() == 1 && joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A) {
			isWindow_ = true;
			player_->SetMotion();
		}
		if (player_->GetActionbutton() == 1 && joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {
			isWindow_ = false;
		}
	}
	// 爆弾の強化ウィンドウ
	if (player_->GetActionbutton() ==1 && isWindow_ == true) {
		ui_->Draw();
		bommEnhance_->Draw();
		
	}
	///!
	for (int i = 0; i < 18; i++) {
		if (isExclamation_[i] == true) {
			ui_->ExclamationMarkDraw();
		}
	}
	for (Stone* stone : stones_) {
		if (stone->GetIsExclamation() == true) {
			ui_->ExclamationMarkDraw();
		}
	}
	for (Gold* gold : golds_) {
		if (gold->GetIsExclamation() == true) {
			ui_->ExclamationMarkDraw();
		}
	}
	for (Jushi* jushi : jushis_) {
		if (jushi->GetIsExclamation() == true) {
			ui_->ExclamationMarkDraw();
		}
	}
	for (Shell* shell : shells_) {
		if (shell->GetIsExclamation() == true) {
			ui_->ExclamationMarkDraw();
		}
	}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::SceneReset() {
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	followCamera_->Initialize();

	player_->RoopInitialize();

	bomm_->RoopInitialize();

	tutorial_->RoopInitilize();

	time = kTime;

	explosion_->Initialize(explosionModel_.get());

	houseCollisionFlag = true;
	for (int i = 0; i < 11; i++) {
		houseCollisionSwitchFlag[i] = true;
	}

	isWindow_ = false;
	for (int i = 0; i < 18; i++) {
		isExclamation_[i] = false;
	}

	for (Stone* stone : stones_) {
		stone->SetIsExclamation(false);
	}
	for (Gold* gold : golds_) {
		gold->SetIsExclamation(false);
	}
	for (Jushi* jushi : jushis_) {
		jushi->SetIsExclamation(false);
	}
	for (Shell* shell : shells_) {
		shell->SetIsExclamation(false);
	}

	door_[0]->RoopInitialize({49.5f,0.0f, -89.0f,},0.0f);
	door_[1]->RoopInitialize({-88.0f, 0.0f, -135.2f}, 0.0f);
	door_[2]->RoopInitialize({-129.0f, 0.0f, -48.8f}, 0.0f);
	door_[3]->RoopInitialize({-130.0f, 17.0f, -84.5f}, 0.0f);
	door_[4]->RoopInitialize({107.0f, 0.0f, -34.3f}, 1.57f * 3.0f);
	door_[5]->RoopInitialize({106.6f, 0.0f, 56.3f}, 1.57f * 3.0f);
	door_[6]->RoopInitialize({-69.2f, 0.0f, 65.7f}, 1.57f * 2.0f);
	door_[7]->RoopInitialize({-123.4f, 0.0f, 8.2f}, 1.57f * 1.0f);
	door_[8]->RoopInitialize({-14.6f, 0.0f, 162.2f}, 1.57f * 1.0f);
	door_[9]->RoopInitialize({86.7f, 0.0f, 191.2f}, 1.57f * 3.0f);
	door_[10]->RoopInitialize({-163.3f, 0.0f, 247.6f}, 1.57f * 1.0f);
		
	door2_[0]->RoopInitialize({86.7f, 0.0f, 204.02f}, 1.57f * 3.0f);
	door2_[1]->RoopInitialize({-163.3f, 0.0f, 234.8f}, 1.57f * 1.0f);

	for (int i = 0; i < 18; i++) {
		isExclamation_[i] = false;
	}

	isSceneEnd_ = false;

	LoadMaterialPopData(
	    "Resources/stonePop.csv", "Resources/goldPop.csv", "Resources/jushiPop.csv",
	    "Resources/shellPop.csv");
}

void GameScene::HouseCollision() {
	Vector3 posA = player_->GetWorldPosition();
	Vector3 posB = door_[0]->GetWorldPosition();
	Vector3 posC = door_[1]->GetWorldPosition();
	Vector3 posD = door_[2]->GetWorldPosition();
	Vector3 posF = door_[4]->GetWorldPosition();
	Vector3 posG = door_[5]->GetWorldPosition();
	Vector3 posH = door_[6]->GetWorldPosition();
	Vector3 posI = door_[7]->GetWorldPosition();
	Vector3 posJ = door_[8]->GetWorldPosition();
	Vector3 posK = door_[9]->GetWorldPosition();
	Vector3 posL = door2_[0]->GetWorldPosition();
	Vector3 posM = door_[10]->GetWorldPosition();
	Vector3 posN = door2_[1]->GetWorldPosition();

	// ドアの判定
	if (posB.x + 7.0f >= posA.x && posB.x <= posA.x && posB.z <= posA.z - 1.5f &&
	    posB.z + 4.0f >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[0]->SetKeyFlag(true);
		}
	} 
	if (door_[0]->GetKeyFlag() == true) {
		door_[0]->Collision();
		player_->InHouseZ(0, {53.0f, 0.0f, -86.5f}, 3.2f,-107.0f);
		if (houseCollisionSwitchFlag[0] == true) {
			houseCollisionFlag = false;
		}
	}
	if (posB.x + 7.0f >= posA.x && posB.x <= posA.x && posB.z <= posA.z - 1.5f &&
	    posB.z + 4.0f >= posA.z) {
		isExclamation_[0] = true;
	} else {
		isExclamation_[0] = false;
	}
	if (player_->GetOutMoveFlag1() == false && houseCollisionSwitchFlag[0] == true) {
		houseCollisionFlag = true;
		houseCollisionSwitchFlag[0] = false;
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
		player_->InHouseZ(1, {-84.8f, 0.0f, -132.5f}, 3.2f, -150.0f);
		if (houseCollisionSwitchFlag[1] == true) {
			houseCollisionFlag = false;
		}
	}
	if (posC.x + 7.0f >= posA.x && posC.x <= posA.x && posC.z <= posA.z - 1.5f &&
	    posC.z + 4.0f >= posA.z) {
		isExclamation_[1] = true;
	} else {
		isExclamation_[1] = false;
	}
	if (player_->GetOutMoveFlag2() == false && houseCollisionSwitchFlag[1] == true) {
		houseCollisionFlag = true;
		houseCollisionSwitchFlag[1] = false;
	}


	// ドアの判定
	if (posD.x + 7.0f >= posA.x && posD.x <= posA.x && posD.z <= posA.z - 0.5f &&
	    posD.z + 4.0f >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[2]->SetKeyFlag(true);
			
		}
	} 
	if (door_[2]->GetKeyFlag() == true) {
		door_[2]->Collision();
		player_->InHouseZ(2, {-125.7f, 0.0f, -47.0f}, 3.2f, -70.0f);
		if (houseCollisionSwitchFlag[2] == true) {
			houseCollisionFlag = false;
		}
	}
	if (posD.x + 7.0f >= posA.x && posD.x <= posA.x && posD.z <= posA.z - 0.5f &&
	    posD.z + 4.0f >= posA.z) {
		isExclamation_[2] = true;
	} else {
		isExclamation_[2] = false;
	}
	if (player_->GetOutMoveFlag3() == false && houseCollisionSwitchFlag[2] == true) {
		houseCollisionFlag = true;
		houseCollisionSwitchFlag[2] = false;
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
		player_->InHouseX(3, {104.5f, 0.0f, -31.2f}, 1.6f, 130.0f);
		if (houseCollisionSwitchFlag[3] == true) {
			houseCollisionFlag = false;
		}
	}
	if (posF.x + 3.0f >= posA.x && posF.x - 5.0f <= posA.x && posF.z <= posA.z &&
	    posF.z + 8.0f >= posA.z) {
		isExclamation_[3] = true;
	} else {
		isExclamation_[3]= false;
	}
	if (player_->GetOutMoveFlag4() == false && houseCollisionSwitchFlag[3] == true) {
		houseCollisionFlag = true;
		houseCollisionSwitchFlag[3] = false;
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
		player_->InHouseX(4, {104.0f, 0.0f, 59.5f}, 1.6f, 135.0f);
		if (houseCollisionSwitchFlag[4] == true) {
			houseCollisionFlag = false;
		}
	}
	if (posG.x + 3.0f >= posA.x && posG.x - 5.0f <= posA.x && posG.z <= posA.z &&
	    posG.z + 7.0f >= posA.z) {
		isExclamation_[4] = true;
	} else {
		isExclamation_[4] = false;
	}
	if (player_->GetOutMoveFlag5() == false && houseCollisionSwitchFlag[4] == true) {
		houseCollisionFlag = true;
		houseCollisionSwitchFlag[4] = false;
	}


	// ドアの判定
	if (posH.x >= posA.x && posH.x - 7.0f <= posA.x && posH.z - 3.0f <= posA.z &&
	    posH.z+5.0f  >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[6]->SetKeyFlag(true);
		}
	}
	if (door_[6]->GetKeyFlag() == true) {
		door_[6]->Collision();
		player_->InHouseZ2(5, {-72.4f, 0.0f, 63.0f}, 0.0f, 90.0f);
		if (houseCollisionSwitchFlag[5] == true) {
			houseCollisionFlag = false;
		}
	}
	if (posH.x >= posA.x && posH.x - 7.0f <= posA.x && posH.z - 3.0f <= posA.z &&
	    posH.z + 5.0f >= posA.z) {
		isExclamation_[5] = true;
	} else {
		isExclamation_[5] = false;
	}
	if (player_->GetOutMoveFlag6() == false && houseCollisionSwitchFlag[5] == true) {
		houseCollisionFlag = true;
		houseCollisionSwitchFlag[5] = false;
	}


	// ドアの判定
	if (posI.x+5.0f >= posA.x && posI.x - 3.0f <= posA.x && posI.z-7.0f  <= posA.z &&
	    posI.z  >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[7]->SetKeyFlag(true);
		}
	}
	if (door_[7]->GetKeyFlag() == true) {
		door_[7]->Collision();
		player_->InHouseX2(6, {-120.0f, 0.0f, 4.7f}, 4.8f, -150.0f);
		if (houseCollisionSwitchFlag[6] == true) {
			houseCollisionFlag = false;
		}
	}
	if (posI.x + 5.0f >= posA.x && posI.x - 3.0f <= posA.x && posI.z - 7.0f <= posA.z &&
	    posI.z >= posA.z) {
		isExclamation_[6] = true;
	} else {
		isExclamation_[6] = false;
	}
	if (player_->GetOutMoveFlag7() == false && houseCollisionSwitchFlag[6] == true) {
		houseCollisionFlag = true;
		houseCollisionSwitchFlag[6] = false;
	}

	// ドアの判定
	if (posJ.x + 5.0f >= posA.x && posJ.x - 3.0f <= posA.x && posJ.z - 7.0f <= posA.z &&
	    posJ.z >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[8]->SetKeyFlag(true);
		}
	}
	if (door_[8]->GetKeyFlag() == true) {
		door_[8]->Collision();
		player_->InHouseX2(7, {-11.5f, 0.0f, 159.0f}, 4.8f, -40.0f);
		if (houseCollisionSwitchFlag[7] == true) {
			houseCollisionFlag = false;
		}
	}
	if (posJ.x + 5.0f >= posA.x && posJ.x - 3.0f <= posA.x && posJ.z - 7.0f <= posA.z &&
	    posJ.z >= posA.z) {
		isExclamation_[7] = true;
	} else {
		isExclamation_[7] = false;
	}
	if (player_->GetOutMoveFlag8() == false && houseCollisionSwitchFlag[7] == true) {
		houseCollisionFlag = true;
		houseCollisionSwitchFlag[7] = false;
	}


	// ドアの判定
	if (posK.x + 3.0f >= posA.x && posK.x - 5.0f <= posA.x && posK.z <= posA.z &&
	    posK.z + 14.0f >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[9]->SetKeyFlag(true);
		}
	}
	if (door_[9]->GetKeyFlag() == true) {
		door_[9]->Collision();
		player_->InHouseX(8, {83.5f, 0.0f, 197.7f}, 1.6f, 120.0f);
		if (houseCollisionSwitchFlag[8] == true) {
			houseCollisionFlag = false;
		}
	}
	if (posK.x + 3.0f >= posA.x && posK.x - 5.0f <= posA.x && posK.z <= posA.z &&
	    posK.z + 14.0f >= posA.z) {
		isExclamation_[8] = true;
	} else {
		isExclamation_[8] = false;
	}
	if (player_->GetOutMoveFlag9() == false && houseCollisionSwitchFlag[8] == true) {
		houseCollisionFlag = true;
		houseCollisionSwitchFlag[8] = false;
	}

	// ドアの判定
	if (posL.x + 3.0f >= posA.x && posL.x - 5.0f <= posA.x && posL.z - 14.0f <= posA.z &&
	    posL.z  >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door2_[0]->SetKeyFlag(true);
		}
	}
	if (door2_[0]->GetKeyFlag() == true) {
		door2_[0]->Collision();
		
	}
	if (posL.x + 3.0f >= posA.x && posL.x - 5.0f <= posA.x && posL.z - 14.0f <= posA.z &&
	    posL.z >= posA.z) {
		isExclamation_[9] = true;
	} else {
		isExclamation_[9] = false;
	}
	

	// ドアの判定
	if (posM.x + 3.0f >= posA.x && posM.x - 5.0f <= posA.x && posM.z - 14.0f <= posA.z &&
	    posM.z >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door_[10]->SetKeyFlag(true);
		}
	}
	if (door_[10]->GetKeyFlag() == true) {
		door_[10]->Collision();
		player_->InHouseX2(9, {-161.0f, 0.0f, 240.7f}, 1.6f, -200.0f);
		if (houseCollisionSwitchFlag[9] == true) {
			houseCollisionFlag = false;
		}
	}
	if (posM.x + 3.0f >= posA.x && posM.x - 5.0f <= posA.x && posM.z - 14.0f <= posA.z &&
	    posM.z >= posA.z) {
		isExclamation_[10] = true;
	} else {
		isExclamation_[10] = false;
	}
	if (player_->GetOutMoveFlag10() == false && houseCollisionSwitchFlag[9] == true) {
		houseCollisionFlag = true;
		houseCollisionSwitchFlag[9] = false;
	}

	// ドアの判定
	if (posN.x + 3.0f >= posA.x && posN.x - 5.0f <= posA.x && posN.z <= posA.z &&
	    posN.z + 14.0f >= posA.z) {
		if (player_->GetIsPushX() == true) {
			door2_[1]->SetKeyFlag(true);
		}
	}
	if (door2_[1]->GetKeyFlag() == true) {
		door2_[1]->Collision();
	}
	if (posN.x + 3.0f >= posA.x && posN.x - 5.0f <= posA.x && posN.z <= posA.z &&
	    posN.z + 14.0f >= posA.z) {
		isExclamation_[11] = true;
	} else {
		isExclamation_[11] = false;
	}

	

	//梯子の当たり判定
	if ( 165.0f >= posA.x && 155.0f <= posA.x &&2.0f>=posA.y&& 186.0f <= posA.z &&
	    196.0f >= posA.z) {
		
		if (player_->GetIsPushX() == true) {
			player_->SetIsController(false);
		}
	} 
	/*if (player_->GetIsController() == false) {
		claimCount++;
		if (claimCount >= 180) {
			claimCount=0;
			player_->SetIsController(true);
		}
	}*/
	
	if (houseCollisionFlag == true) {

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

		// 下壁          //下                //上                 //左                //右
		if (posA.x >= 275.5f && posA.x <= 290.0f && posA.z <= -230.0f && posA.z >= -315.0f) {
			player_->SetTranslationX(275.5f);
		}
		// 右壁          //下                //上                 //左                //右
		if (posA.x >= 175.0f && posA.x <= 290.0f && posA.z <= -237.5f && posA.z >= -240.0f) {
			player_->SetTranslationZ(-240.0f);
		}
		// 左壁          //下                //上                 //左                //右
		if (posA.x >= -240.0f && posA.x <= 280.0f && posA.z <= -280.0f && posA.z >= -285.5f) {
			player_->SetTranslationZ(-280.0f);
		}
		// 上壁          //下                //上                 //左                //右
		if (posA.x >= -216.5f && posA.x <= -211.0f && posA.z <= 80.0f && posA.z >= -300.0f) {
			player_->SetTranslationX(-211.0f);
		}
		// 左壁          //下                //上                 //左                //右
		if (posA.x >= -300.0f && posA.x <= -211.7f && posA.z <= 81.5f && posA.z >= 77.5f) {
			player_->SetTranslationZ(81.5f);
		}
		// 上壁          //下                //上                 //左                //右
		if (posA.x >= -290.0f && posA.x <= -283.0f && posA.z <= 300.0f && posA.z >= 70.0f) {
			player_->SetTranslationX(-283.0f);
		}
		// 右壁          //下                //上                 //左                //右
		if (posA.x >= -300.0f && posA.x <= -50.0f && posA.z <= 280.5f && posA.z >= 277.0f) {
			player_->SetTranslationZ(277.0f);
		}
		// 下壁          //下                //上                 //左                //右
		if (posA.x >= -79.0f && posA.x <= -77.0f && posA.z <= 290.0f && posA.z >= 207.5f) {
			player_->SetTranslationX(-79.0f);
		}
		// 右壁          //下                //上                 //左                //右
		if (posA.x >= -78.0f && posA.x <= 48.0f && posA.z <= 207.5f && posA.z >= 205.5f) {
			player_->SetTranslationZ(205.5f);
		}
		// 上壁          //下                //上                 //左                //右
		if (posA.x >= 48.0f && posA.x <= 50.0f && posA.z <= 300.0f && posA.z >= 205.5f) {
			player_->SetTranslationX(50.0f);
		}
		// 右壁          //下                //上                 //左                //右
		if (posA.x >= 30.0f && posA.x <= 200.0f && posA.z <= 280.0f && posA.z >= 277.0f) {
			player_->SetTranslationZ(277.0f);
		}
		// 下壁          //下                //上                 //左                //右
		if (posA.x >= 173.0f && posA.x <= 175.0f && posA.z <= 325.0f && posA.z >= -238.0f) {
			player_->SetTranslationX(173.0f);
		}

		// 上壁          //下                //上                 //左                //右
		if (posA.x >= -90.0f && posA.x <= -88.0f && posA.z <= 166.0f && posA.z >= 68.0f) {
			player_->SetTranslationX(-88.0f);
		}
		// 右壁          //下                //上                 //左                //右
		if (posA.x >= -300.0f && posA.x <= -90.0f && posA.z <= 69.0f && posA.z >= 67.0f) {
			player_->SetTranslationZ(67.0f);
		}
		// 左壁          //下                //上                 //左                //右
		if (posA.x >= -300.0f && posA.x <= -90.0f && posA.z <= 167.0f && posA.z >= 165.0f) {
			player_->SetTranslationZ(167.0f);
		}

		// 上壁          //下                //上                 //左                //右
		if (posA.x >= -56.0f && posA.x <= -54.0f && posA.z <= 208.0f && posA.z >= 179.0f) {
			player_->SetTranslationX(-54.0f);
		}
		// 右壁          //下                //上                 //左                //右
		if (posA.x >= -100.0f && posA.x <= -54.0f && posA.z <= 175.0f && posA.z >= 172.5f) {
			player_->SetTranslationZ(172.5f);
		}
		// 下壁          //下                //上                 //左                //右
		if (posA.x >= -101.5f && posA.x <= -99.5f && posA.z <= 231.0f && posA.z >= 170.5f) {
			player_->SetTranslationX(-101.5f);
		}
		// 左壁          //下                //上                 //左                //右
		if (posA.x >= -100.0f && posA.x <= -75.0f && posA.z <= 233.0f && posA.z >= 231.0f) {
			player_->SetTranslationZ(233.0f);
		}

		// 上壁          //下                //上                 //左                //右
		if (posA.x >= -127.0f && posA.x <= -125.0f && posA.z <= -166.0f && posA.z >= -300.0f) {
			player_->SetTranslationX(-125.0f);
		}
		// 左壁          //下                //上                 //左                //右
		if (posA.x >= -215.0f && posA.x <= -126.0f && posA.z <= -165.0f && posA.z >= -167.0f) {
			player_->SetTranslationZ(-165.0f);
		}

		// 上壁          //下                //上                 //左                //右
		if (posA.x >= 8.0f && posA.x <= 10.2f && posA.z <= -186.0f && posA.z >= -230.0f) {
			player_->SetTranslationX(10.2f);
		}
		// 左壁          //下                //上                 //左                //右
		if (posA.x >= -25.5f && posA.x <= 8.5f && posA.z <= -185.0f && posA.z >= -187.0f) {
			player_->SetTranslationZ(-185.0f);
		}
		// 右壁          //下                //上                 //左                //右
		if (posA.x >= -33.5f && posA.x <= 8.5f && posA.z <= -229.5f && posA.z >= -231.5f) {
			player_->SetTranslationZ(-231.5f);
		}
		// 下壁          //下                //上                 //左                //右
		if (posA.x >= -34.5f && posA.x <= -32.5f && posA.z <= -186.0f && posA.z >= -230.0f) {
			player_->SetTranslationX(-34.5f);
		}

		// 上壁          //下                //上                 //左                //右
		if (posA.x >= 26.0f && posA.x <= 28.0f && posA.z <= -200.0f && posA.z >= -218.5f) {
			player_->SetTranslationX(28.0f);
		}
		// 左壁          //下                //上                 //左                //右
		if (posA.x >= 8.0f && posA.x <= 27.0f && posA.z <= -199.0f && posA.z >= -201.0f) {
			player_->SetTranslationZ(-199.0f);
		}
		// 下壁          //下                //上                 //左                //右
		if (posA.x >= 7.0f && posA.x <= 9.0f && posA.z <= -200.0f && posA.z >= -218.5f) {
			player_->SetTranslationX(7.0f);
		}
		// 右壁          //下                //上                 //左                //右
		if (posA.x >= 8.0f && posA.x <= 27.0f && posA.z <= -217.5f && posA.z >= -219.5f) {
			player_->SetTranslationZ(-219.5f);
		}

		// 上壁          //下                //上                 //左                //右
		if (posA.x >= 183.0f && posA.x <= 185.0f && posA.z <= -164.0f && posA.z >= -241.0f) {
			player_->SetTranslationX(185.0f);
		}
		// 左壁          //下                //上                 //左                //右
		if (posA.x >= 26.5f && posA.x <= 183.0f && posA.z <= -162.0f && posA.z >= -164.0f) {
			player_->SetTranslationZ(-162.0f);
		}
		// 下壁          //下                //上                 //左                //右
		if (posA.x >= 25.0f && posA.x <= 27.0f && posA.z <= -164.0f && posA.z >= -241.0f) {
			player_->SetTranslationX(25.0f);
		}
		// 右壁          //下                //上                 //左                //右
		if (posA.x >= 26.5f && posA.x <= 183.0f && posA.z <= -241.0f && posA.z >= -243.0f) {
			player_->SetTranslationZ(-243.0f);
		}

		// 梯子の当たり判定
		//  上壁          //下                //上                 //左                //右
		if (posA.x >= 161.0f && posA.x <= 163.0f && posA.z <= 193.5f && posA.z >= 188.5f) {
			player_->SetTranslationX(163.0f);
		}
		// 左壁          //下                //上                 //左                //右
		if (posA.x >= 155.0f && posA.x <= 162.0f && posA.z <= 194.5f && posA.z >= 192.5f) {
			player_->SetTranslationZ(194.5f);
		}
		// 右壁          //下                //上                 //左                //右
		if (posA.x >= 155.0f && posA.x <= 162.0f && posA.z <= 189.5f && posA.z >= 187.5f) {
			player_->SetTranslationZ(187.5f);
		}
	}
}

void GameScene::HouseStage() {// ドアモデル
	doorModel_[0].reset(Model::CreateFromOBJ("doorKnob1", true));
	doorModel_[1].reset(Model::CreateFromOBJ("doorKnob2", true));

	doorModel2_[0].reset(Model::CreateFromOBJ("door1", true));
	doorModel2_[1].reset(Model::CreateFromOBJ("door2", true));

	for (int i = 0; i < 11; i++) {
		door_[i] = std::make_unique<DoorOBJ>();
	}

	door_[0]->Initialize(
	    doorModel_[0].get(), doorModel_[1].get(),{49.5f,0.0f,-89.0f,},0.0f);
	door_[1]->Initialize(doorModel_[0].get(), doorModel_[1].get(), {-88.0f, 0.0f, -135.2f}, 0.0f);
	door_[2]->Initialize(doorModel_[0].get(), doorModel_[1].get(), {-129.0f, 0.0f, -48.8f}, 0.0f);
	door_[3]->Initialize(doorModel_[0].get(), doorModel_[1].get(), {-130.0f, 17.0f, -84.5f}, 0.0f);
	door_[4]->Initialize(
	    doorModel_[0].get(), doorModel_[1].get(), {107.0f, 0.0f, -34.3f}, 1.57f * 3.0f);
	door_[5]->Initialize(
	    doorModel_[0].get(), doorModel_[1].get(), {106.6f, 0.0f, 56.3f}, 1.57f * 3.0f);
	door_[6]->Initialize(
	    doorModel_[0].get(), doorModel_[1].get(), {-69.2f, 0.0f, 65.7f}, 1.57f * 2.0f);
	door_[7]->Initialize(
	    doorModel_[0].get(), doorModel_[1].get(), {-123.4f, 0.0f, 8.2f}, 1.57f * 1.0f);
	door_[8]->Initialize(
	    doorModel_[0].get(), doorModel_[1].get(), {-14.6f, 0.0f, 162.2f}, 1.57f * 1.0f);
	door_[9]->Initialize(
	    doorModel_[0].get(), doorModel_[1].get(), {86.7f, 0.0f, 191.2f}, 1.57f * 3.0f);
	door_[10]->Initialize(
	    doorModel_[0].get(), doorModel_[1].get(), {-163.3f, 0.0f, 247.6f}, 1.57f * 1.0f);

	for (int i = 0; i < 2; i++) {
		door2_[i] = std::make_unique<DoorOBJ>();
	}
	door2_[0]->Initialize(
	    doorModel2_[0].get(), doorModel2_[1].get(), {86.7f, 0.0f, 204.02f}, 1.57f * 3.0f);
	door2_[1]->Initialize(
	    doorModel2_[0].get(), doorModel2_[1].get(), {-163.3f, 0.0f, 234.8f}, 1.57f * 1.0f);


	rockModel_[0].reset(Model::CreateFromOBJ("rock1", true));
	rockModel_[1].reset(Model::CreateFromOBJ("rock2", true));
	rockModel_[2].reset(Model::CreateFromOBJ("rock3", true));
	rockModel_[3].reset(Model::CreateFromOBJ("rock4", true));
	rockModel_[4].reset(Model::CreateFromOBJ("rock5", true));
	rockModel_[5].reset(Model::CreateFromOBJ("rock6", true));
	rockModel_[6].reset(Model::CreateFromOBJ("rock7", true));
	rockModel_[7].reset(Model::CreateFromOBJ("rock8", true));
	rockModel_[8].reset(Model::CreateFromOBJ("rock9", true));
	rockModel_[9].reset(Model::CreateFromOBJ("rock10", true));

	ladderModel_[0].reset(Model::CreateFromOBJ("ladder1", true));
	ladderModel_[1].reset(Model::CreateFromOBJ("ladder2", true));
	ladderModel_[2].reset(Model::CreateFromOBJ("ladder3", true));
	ladderModel_[3].reset(Model::CreateFromOBJ("ladder4", true));
	ladderModel_[4].reset(Model::CreateFromOBJ("ladder5", true));
	ladderModel_[5].reset(Model::CreateFromOBJ("ladder6", true));
	ladderModel_[6].reset(Model::CreateFromOBJ("ladder7", true));
	ladderModel_[7].reset(Model::CreateFromOBJ("ladder8", true));

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
	    houseModel_[76].get(), houseModel_[77].get(), houseModel_[78].get(), rockModel_[0].get(),
	    rockModel_[1].get(), rockModel_[2].get(), rockModel_[3].get(), rockModel_[4].get(),
	    rockModel_[5].get(), rockModel_[6].get(), rockModel_[7].get(), rockModel_[8].get(),
	    rockModel_[9].get(), ladderModel_[0].get(),ladderModel_[1].get(), ladderModel_[2].get(),
	    ladderModel_[3].get(), ladderModel_[4].get(), ladderModel_[5].get(), ladderModel_[6].get(),
	    ladderModel_[7].get());
}

void GameScene::MaterialCheckCollisions() {
	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 自キャラと石の当たり判定
	for (Stone* stone : stones_) {
		// 石の座標
		posB = stone->GetWorldPosition();
		
		float radius1 = 1.5f;
		float radius2 = 2.0f;

		float hit = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		            (posB.z - posA.z) * (posB.z - posA.z);

		float radius = (radius1 + radius2) * (radius1 + radius2);

		// プレイヤーと石の交差判定
		if (hit <= radius) {
			stone->SetIsExclamation(true);
			if (player_->GetIsPushX() == true) {
				// 石の衝突時コールバックを呼び出す
				stone->OnCollision();
				//素材の所持数を足す
				stoneCount_++;
				switch (stageNo) {
				case Stage::kTutorial:
					// チュートリアル用
					tutorial_->SetIsTutorialEnd_(false);
					if (tutorial_->GetIsTutorialEnd_() == false) {
						player_->SetIsController(false);
					}
					break;
				}

				stone->SetIsExclamation(false);
			}
		} else {
			stone->SetIsExclamation(false);
		}
	}

	// 自キャラと金の当たり判定
	for (Gold* gold : golds_) {
		// 金の座標
		posB = gold->GetWorldPosition();

		float radius1 = 1.5f;
		float radius2 = 2.0f;

		float hit = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		            (posB.z - posA.z) * (posB.z - posA.z);

		float radius = (radius1 + radius2) * (radius1 + radius2);

		// プレイヤーと金の交差判定
		if (hit <= radius) {
			gold->SetIsExclamation(true);
			if (player_->GetIsPushX() == true) {
				// 金の衝突時コールバックを呼び出す
				gold->OnCollision();
				// 素材の所持数を足す
				goldCount_++;
				gold->SetIsExclamation(false);
			}
		} else {
			gold->SetIsExclamation(false);
		}
	}

	// 自キャラと樹脂の当たり判定
	for (Jushi* jushi : jushis_) {
		// 樹脂の座標
		posB = jushi->GetWorldPosition();

		float radius1 = 1.5f;
		float radius2 = 2.0f;

		float hit = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		            (posB.z - posA.z) * (posB.z - posA.z);

		float radius = (radius1 + radius2) * (radius1 + radius2);

		// プレイヤーと樹脂の交差判定
		if (hit <= radius) {
			jushi->SetIsExclamation(true);
			if (player_->GetIsPushX() == true) {
				// 樹脂の衝突時コールバックを呼び出す
				jushi->OnCollision();
				// 素材の所持数を足す
				jushiCount_++;
				jushi->SetIsExclamation(false);
			}
		} else {
			jushi->SetIsExclamation(false);
		}
	}

	// 自キャラと貝の当たり判定
	for (Shell* shell : shells_) {
		// 貝の座標
		posB = shell->GetWorldPosition();

		float radius1 = 1.5f;
		float radius2 = 2.0f;

		float hit = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		            (posB.z - posA.z) * (posB.z - posA.z);

		float radius = (radius1 + radius2) * (radius1 + radius2);

		// プレイヤーと貝の交差判定
		if (hit <= radius) {
			shell->SetIsExclamation(true);
			if (player_->GetIsPushX() == true) {
				// 貝の衝突時コールバックを呼び出す
				shell->OnCollision();
				// 素材の所持数を足す
				shellCount_++;
				shell->SetIsExclamation(false);
			}
		} else {
			shell->SetIsExclamation(false);
		}
	}
}

void GameScene::StoneSpawn(Vector3 position) { 
	// 生成
	Stone* stone = new Stone;
	//初期化
	stone->Initialize(modelStone_.get(), position);
	//リストに登録
	stones_.push_back(stone);
}

void GameScene::GoldSpawn(Vector3 position) {
	// 生成
	Gold* gold = new Gold;
	// 初期化
	gold->Initialize(modelGold_.get(), position);
	// リストに登録
	golds_.push_back(gold);
}

void GameScene::JushiSpawn(Vector3 position) {
	// 生成
	Jushi* jushi = new Jushi;
	// 初期化
	jushi->Initialize(modelJushi_.get(), position);
	// リストに登録
	jushis_.push_back(jushi);
}

void GameScene::ShellSpawn(Vector3 position) { 
	// 生成
	Shell* shell = new Shell;
	// 初期化
	shell->Initialize(modelShell_.get(), position);
	// リストに登録
	shells_.push_back(shell);
}

void GameScene::LoadMaterialPopData(
    const std::string& fileStone, const std::string& fileGold, const std::string& fileJushi,
    const std::string& fileShell) { 
	stonePopCommands.clear(); 
	goldPopCommands.clear();
	jushiPopCommands.clear();
	shellPopCommands.clear();

	//ファイルを開く
	std::ifstream stoneFile;
	stoneFile.open(fileStone);
	assert(stoneFile.is_open());
	// ファイルの内容を文字列ストリームにコピー
	stonePopCommands << stoneFile.rdbuf();
	// ファイルを閉じる
	stoneFile.close();

	// ファイルを開く
	std::ifstream goldFile;
	goldFile.open(fileGold);
	assert(goldFile.is_open());
	// ファイルの内容を文字列ストリームにコピー
	goldPopCommands << goldFile.rdbuf();
	// ファイルを閉じる
	goldFile.close();

	// ファイルを開く
	std::ifstream jushiFile;
	jushiFile.open(fileJushi);
	assert(jushiFile.is_open());
	// ファイルの内容を文字列ストリームにコピー
	jushiPopCommands << jushiFile.rdbuf();
	// ファイルを閉じる
	jushiFile.close();

	// ファイルを開く
	std::ifstream shellFile;
	shellFile.open(fileShell);
	assert(shellFile.is_open());
	// ファイルの内容を文字列ストリームにコピー
	shellPopCommands << shellFile.rdbuf();
	// ファイルを閉じる
	shellFile.close();
}

void GameScene::UpdateStonePopCommands() {
	// 待機処理
	if (stonePopWaitFlag) {
		stonePopWaitTimer--;
		if (stonePopWaitTimer <= 0) {
			// 待機完了
			stonePopWaitFlag = false;
		}
		return;
	}

	// 1行分の文字列を入れる変数
	std::string stoneLine;

	// コマンド実行ループ　石
	while (getline(stonePopCommands, stoneLine)) {
		// 1行文の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(stoneLine);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			StoneSpawn(Vector3(x, y, z));
		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			stonePopWaitFlag = true;
			stonePopWaitTimer = waitTime;

			// コマンドループを抜ける
			break;
		}
	}
}

void GameScene::UpdateGoldPopCommands() {
	// 待機処理
	if (goldPopWaitFlag) {
		goldPopWaitTimer--;
		if (goldPopWaitTimer <= 0) {
			// 待機完了
			goldPopWaitFlag = false;
		}
		return;
	}

	// 1行分の文字列を入れる変数
	std::string goldLine;

	// コマンド実行ループ　金
	while (getline(goldPopCommands, goldLine)) {
		// 1行文の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(goldLine);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			GoldSpawn(Vector3(x, y, z));
		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			goldPopWaitFlag = true;
			goldPopWaitTimer = waitTime;

			// コマンドループを抜ける
			break;
		}
	}
}

void GameScene::UpdateJushiPopCommands() {
	// 待機処理
	if (jushiPopWaitFlag) {
		jushiPopWaitTimer--;
		if (jushiPopWaitTimer <= 0) {
			// 待機完了
			jushiPopWaitFlag = false;
		}
		return;
	}

	// 1行分の文字列を入れる変数
	std::string jushiLine;

	// コマンド実行ループ　樹脂
	while (getline(jushiPopCommands, jushiLine)) {
		// 1行文の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(jushiLine);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			JushiSpawn(Vector3(x, y, z));
		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			jushiPopWaitFlag = true;
			jushiPopWaitTimer = waitTime;

			// コマンドループを抜ける
			break;
		}
	}
}

void GameScene::UpdateShellPopCommands() {
	// 待機処理
	if (shellPopWaitFlag) {
		shellPopWaitTimer--;
		if (shellPopWaitTimer <= 0) {
			// 待機完了
			shellPopWaitFlag = false;
		}
		return;
	}

	// 1行分の文字列を入れる変数
	std::string shellLine;

	// コマンド実行ループ　貝
	while (getline(shellPopCommands, shellLine)) {
		// 1行文の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(shellLine);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			ShellSpawn(Vector3(x, y, z));
		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			shellPopWaitFlag = true;
			shellPopWaitTimer = waitTime;

			// コマンドループを抜ける
			break;
		}
	}
}
