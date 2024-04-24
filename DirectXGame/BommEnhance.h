#pragma once

class BommEnhance {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(int stone, int gold, int jushi, int shell);

	/// <summary>
	/// 描画
	/// </summary>
	//void Draw();

private:
	int exp = 0;
	int expMax[10];
	int bommLv = 1;
};
