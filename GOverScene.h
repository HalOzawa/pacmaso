#pragma once
#include "Engine/GameObject.h"
class GOverScene :
	public GameObject
{
	int gPict_;
public:
	
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GOverScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
