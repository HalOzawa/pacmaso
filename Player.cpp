#include "Player.h"
#include "Stage.h"
#include "Gauge.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

namespace {
	const float PLAYER_MOVE_SPEED{ 0.1f };
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), 
	 hModel_(-1), speed_(PLAYER_MOVE_SPEED), pStage_(nullptr),
	 hpCrr_(100), hpMax_(100)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);
	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
	pStage_ = (Stage *)FindObject("Stage");
	rec.SetRectCenter(transform_.position_.x, transform_.position_.z, 1.0, 1.0);
}

void Player::Update()
{
	enum Dir
	{
		UP,LEFT, DOWN,RIGHT,NONE,
	};
	int moveDir = Dir::NONE;
	XMVECTOR vFront = { 0, 0, 1, 0 };
	XMVECTOR move{ 0,0,0,0 };

	if (Input::IsKey(DIK_UP))
	{
		//transform_.position_.z += 0.2;
		move = XMVECTOR{ 0,0,1,0 };
		moveDir = Dir::UP;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		//transform_.position_.x -= 0.2;
		move = XMVECTOR{ -1,0,0,0 };
		moveDir = Dir::LEFT;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		//transform_.position_.z -= 0.2;
		move = XMVECTOR{ 0,0,-1,0 };
		moveDir = Dir::DOWN;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		//transform_.position_.x += 0.2;
		move = XMVECTOR{ 1,0,0,0 };
		moveDir = Dir::RIGHT;
	}
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	XMVECTOR posTmp = XMVectorZero();
	posTmp = pos + speed_ * move;

	int tx, ty;
	PacRect trec;
	trec.SetRectCenter(XMVectorGetX(posTmp), XMVectorGetZ(posTmp), 1.0, 1.0);

	switch (moveDir)
	{
	case UP:
		tx = (int)(trec.centerx + 1);
		ty = pStage_->GetStageHeight() - (int)(trec.top) - 1;
		break;
	case DOWN:
		tx = (int)(trec.centerx + 1);
		ty = pStage_->GetStageHeight() - (int)(trec.bottom) - 1;
		break;
	case LEFT:
		tx = (int)(trec.left + 1);
		ty = pStage_->GetStageHeight() - (int)(trec.centery) - 1;
		break;
	case RIGHT:
		tx = (int)(trec.right + 1);
		ty = pStage_->GetStageHeight() - (int)(trec.centery) - 1;
		break;
	case NONE:
		tx = (int)(trec.centerx + 1);
		ty = pStage_->GetStageHeight() - (int)(trec.centery) - 1;
		break;
	default:
		break;
	}

	if (!(pStage_->IsWall(tx, ty)))
	{
		pos = posTmp;
	}
	else
	{
		hpCrr_ = hpCrr_ - 4;
		if (hpCrr_ < 0) {
			hpCrr_ = 0;
			SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
			pSM->ChangeScene(SCENE_ID_GAMEOVER);
		}
	}


	//ˆÚ“®æ‚ªƒtƒƒA(STAGE_OBJ::FLOOR => 0)
	//if (map[ty][tx] == STAGE_OBJ::FLOOR) {
		//pos = psoTemp;
	//}
	//Debug::Log("X, Z=");
	//Debug::Log(XMVectorGetX(pos));
	//Debug::Log(",");
	//Debug::Log(XMVectorGetZ(pos), true);
	//Debug::Log("iX, iZ=");
	//Debug::Log(tx);
	//Debug::Log(",");
	//Debug::Log(ty);
	//Debug::Log(" : ");
	//Debug::Log(pStage_->IsWall(tx, ty), true);

	if (!XMVector3Equal(move, XMVectorZero()))
	{
		XMStoreFloat3(&(transform_.position_), pos);

		float retAngle = 0.0;
		retAngle = atan2(XMVectorGetX(move), XMVectorGetZ(move));
		transform_.rotate_.y = XMConvertToDegrees(retAngle);
	}
	Gauge* pGauge = (Gauge*)FindObject("Gauge");
	pGauge->SetGageVal(hpCrr_, hpMax_);
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

PacRect::PacRect()
	:top(-1), bottom(-1), left(-1), right(-1), centerx(-1),
	 centery(-1), width(-1), height(-1)
{
}

void PacRect::SetRectCenter(float _cx, float _cy, float _width, float _height)
{
	centerx = _cx;
	centery = _cy;
	width = _width;
	height = _height;
	top = centery + height / 2.0;
	bottom = centery - height / 2.0;
	left = centerx - width / 2.0;
	right = centerx + width / 2.0;
}

void PacRect::SetRectTopBottom(float _left, float _top, float _width, float _height)
{
	left = _left;
	top = _top;
	width = _width;
	height = _height;
	centery = top - height / 2.0;
	bottom = top - height;
	centerx = left + width / 2.0;
	right = left + width;
}

float PacRect::GetLeft()
{
	return left;
}

float PacRect::GetRight()
{
	return right;
}

float PacRect::GetTop()
{
	return top;
}

float PacRect::GetBottom()
{
	return bottom;
}

float PacRect::GetCenterX()
{
	return centerx;
}

float PacRect::GetCenterY()
{
	return centery;
}

float PacRect::GetWidth()
{
	return width;
}

float PacRect::GetHeight()
{
	return height;
}
