#include "TitleScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"


TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent, "TitleScene"), tPict_(-1)
{
}

void TitleScene::Initialize()
{
	tPict_ = Image::Load("title.jpg");
	assert(tPict_ >= 0);
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		pSM->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	Image::SetTransform(tPict_, transform_);
	Image::Draw(tPict_);
}

void TitleScene::Release()
{
}

