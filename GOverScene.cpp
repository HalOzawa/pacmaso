#include "GOverScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

GOverScene::GOverScene(GameObject* parent)
	:GameObject(parent, "GOverScene"), gPict_(-1)
{
}

void GOverScene::Initialize()
{
	gPict_ = Image::Load("Clear.png");
	assert(gPict_ >= 0);
}

void GOverScene::Update()
{
}

void GOverScene::Draw()
{
	Image::SetTransform(gPict_, transform_);
	Image::Draw(gPict_);
}

void GOverScene::Release()
{
}
