#include "HouseStageOBJ.h"

void HouseStageOBJ::Initialize(
    Model* model, Model* model1, Model* model2, Model* model3, Model* model4, Model* model5,
    Model* model6, Model* model7, Model* model8, Model* model9, Model* model10, Model* model11,
    Model* model12, Model* model13, Model* model14, Model* model15, Model* model16, Model* model17,
    Model* model18, Model* model19, Model* model20, Model* model21, Model* model22, Model* model23,
    Model* model24, Model* model25, Model* model26, Model* model27, Model* model28, Model* model29,
    Model* model30, Model* model31, Model* model32, Model* model33, Model* model34, Model* model35,
    Model* model36, Model* model37, Model* model38, Model* model39, Model* model40, Model* model41,
    Model* model42, Model* model43, Model* model44, Model* model45, Model* model46, Model* model47,
    Model* model48, Model* model49, Model* model50, Model* model51, Model* model52, Model* model53,
    Model* model54, Model* model55, Model* model56, Model* model57, Model* model58, Model* model59,
    Model* model60, Model* model61, Model* model62, Model* model63, Model* model64, Model* model65,
    Model* model66, Model* model67, Model* model68, Model* model69, Model* model70, Model* model71,
    Model* model72, Model* model73, Model* model74, Model* model75, Model* model76, Model* model77,
    Model* model78) {
	model_[0] = model;
	model_[1] = model1;
	model_[2] = model2;
	model_[3] = model3;
	model_[4] = model4;
	model_[5] = model5;
	model_[6] = model6;
	model_[7] = model7;
	model_[8] = model8;
	model_[9] = model9;
	model_[10] = model10;
	model_[11] = model11;
	model_[12] = model12;
	model_[13] = model13;
	model_[14] = model14;
	model_[15] = model15;
	model_[16] = model16;
	model_[17] = model17;
	model_[18] = model18;
	model_[19] = model19;
	model_[20] = model20;
	model_[21] = model21;
	model_[22] = model22;
	model_[23] = model23;
	model_[24] = model24;
	model_[25] = model25;
	model_[26] = model26;
	model_[27] = model27;
	model_[28] = model28;
	model_[29] = model29;
	model_[30] = model30;
	model_[31] = model31;
	model_[32] = model32;
	model_[33] = model33;
	model_[34] = model34;
	model_[35] = model35;
	model_[36] = model36;
	model_[37] = model37;
	model_[38] = model38;
	model_[39] = model39;
	model_[40] = model40;
	model_[41] = model41;
	model_[42] = model42;
	model_[43] = model43;
	model_[44] = model44;
	model_[45] = model45;
	model_[46] = model46;
	model_[47] = model47;
	model_[48] = model48;
	model_[49] = model49;
	model_[50] = model50;
	model_[51] = model51;
	model_[52] = model52;
	model_[53] = model53;
	model_[54] = model54;
	model_[55] = model55;
	model_[56] = model56;
	model_[57] = model57;
	model_[58] = model58;
	model_[59] = model59;
	model_[60] = model60;
	model_[61] = model61;
	model_[62] = model62;
	model_[63] = model63;
	model_[64] = model64;
	model_[65] = model65;
	model_[66] = model66;
	model_[67] = model67;
	model_[68] = model68;
	model_[69] = model69;
	model_[70] = model70;
	model_[71] = model71;
	model_[72] = model72;
	model_[73] = model73;
	model_[74] = model74;
	model_[75] = model75;
	model_[76] = model76;
	model_[77] = model77;
	model_[78] = model78;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void HouseStageOBJ::Update() {
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void HouseStageOBJ::Draw(ViewProjection& viewProjection) {
	model_[0]->Draw(worldTransform_, viewProjection);
	model_[1]->Draw(worldTransform_, viewProjection);
	model_[2]->Draw(worldTransform_, viewProjection);
	model_[3]->Draw(worldTransform_, viewProjection);
	model_[4]->Draw(worldTransform_, viewProjection);
	model_[5]->Draw(worldTransform_, viewProjection);
	model_[6]->Draw(worldTransform_, viewProjection);
	model_[7]->Draw(worldTransform_, viewProjection);
	model_[8]->Draw(worldTransform_, viewProjection);
	model_[9]->Draw(worldTransform_, viewProjection);
	model_[10]->Draw(worldTransform_, viewProjection);
	model_[11]->Draw(worldTransform_, viewProjection);
	model_[12]->Draw(worldTransform_, viewProjection);
	model_[13]->Draw(worldTransform_, viewProjection);
	model_[14]->Draw(worldTransform_, viewProjection);
	model_[15]->Draw(worldTransform_, viewProjection);
	model_[16]->Draw(worldTransform_, viewProjection);
	model_[17]->Draw(worldTransform_, viewProjection);
	model_[18]->Draw(worldTransform_, viewProjection);
	model_[19]->Draw(worldTransform_, viewProjection);
	model_[20]->Draw(worldTransform_, viewProjection);
	model_[21]->Draw(worldTransform_, viewProjection);
	model_[22]->Draw(worldTransform_, viewProjection);
	model_[23]->Draw(worldTransform_, viewProjection);
	model_[24]->Draw(worldTransform_, viewProjection);
	model_[25]->Draw(worldTransform_, viewProjection);
	model_[26]->Draw(worldTransform_, viewProjection);
	model_[27]->Draw(worldTransform_, viewProjection);
	model_[28]->Draw(worldTransform_, viewProjection);
	model_[29]->Draw(worldTransform_, viewProjection);
	model_[30]->Draw(worldTransform_, viewProjection);
	model_[31]->Draw(worldTransform_, viewProjection);
	model_[32]->Draw(worldTransform_, viewProjection);
	model_[33]->Draw(worldTransform_, viewProjection);
	model_[34]->Draw(worldTransform_, viewProjection);
	model_[35]->Draw(worldTransform_, viewProjection);
	model_[36]->Draw(worldTransform_, viewProjection);
	model_[37]->Draw(worldTransform_, viewProjection);
	model_[38]->Draw(worldTransform_, viewProjection);
	model_[39]->Draw(worldTransform_, viewProjection);
	model_[40]->Draw(worldTransform_, viewProjection);
	model_[41]->Draw(worldTransform_, viewProjection);
	model_[42]->Draw(worldTransform_, viewProjection);
	model_[43]->Draw(worldTransform_, viewProjection);
	model_[44]->Draw(worldTransform_, viewProjection);
	model_[45]->Draw(worldTransform_, viewProjection);
	model_[46]->Draw(worldTransform_, viewProjection);
	model_[47]->Draw(worldTransform_, viewProjection);
	model_[48]->Draw(worldTransform_, viewProjection);
	model_[49]->Draw(worldTransform_, viewProjection);
	model_[50]->Draw(worldTransform_, viewProjection);
	model_[51]->Draw(worldTransform_, viewProjection);
	model_[52]->Draw(worldTransform_, viewProjection);
	model_[53]->Draw(worldTransform_, viewProjection);
	model_[54]->Draw(worldTransform_, viewProjection);
	model_[55]->Draw(worldTransform_, viewProjection);
	model_[56]->Draw(worldTransform_, viewProjection);
	model_[57]->Draw(worldTransform_, viewProjection);
	model_[58]->Draw(worldTransform_, viewProjection);
	model_[59]->Draw(worldTransform_, viewProjection);
	model_[60]->Draw(worldTransform_, viewProjection);
	model_[61]->Draw(worldTransform_, viewProjection);
	model_[62]->Draw(worldTransform_, viewProjection);
	model_[63]->Draw(worldTransform_, viewProjection);
	model_[64]->Draw(worldTransform_, viewProjection);
	model_[65]->Draw(worldTransform_, viewProjection);
	model_[66]->Draw(worldTransform_, viewProjection);
	model_[67]->Draw(worldTransform_, viewProjection);
	model_[68]->Draw(worldTransform_, viewProjection);
	model_[69]->Draw(worldTransform_, viewProjection);
	model_[70]->Draw(worldTransform_, viewProjection);
	model_[71]->Draw(worldTransform_, viewProjection);
	model_[72]->Draw(worldTransform_, viewProjection);
	model_[73]->Draw(worldTransform_, viewProjection);
	model_[74]->Draw(worldTransform_, viewProjection);
	model_[75]->Draw(worldTransform_, viewProjection);
	model_[76]->Draw(worldTransform_, viewProjection);
	model_[77]->Draw(worldTransform_, viewProjection);
	model_[78]->Draw(worldTransform_, viewProjection);
}