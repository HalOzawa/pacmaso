#pragma once
#include "Engine/GameObject.h"
class GOverScene :
	public GameObject
{
	int gPict_;
public:
	
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GOverScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
