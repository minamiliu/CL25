//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: player2D.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/19
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "input.h"
#include "player2D.h"
#include "bullet2D.h"
#include "sound.h"
#include "life.h"
#include "explosion2D.h"

//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/player000.png"

#define PLAYER_SPEED (5.0f)

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPlayer2D::CPlayer2D()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPlayer2D::~CPlayer2D()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CPlayer2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	SetObjType( CScene::OBJTYPE_PLAYER);

	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CPlayer2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CPlayer2D::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//CInputMouse *pInputMouse = CManager::GetInputMouse();
	CSound *pSound = CManager::GetSound();
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 size = GetSize();

	
	//�ړ�
	if(pInputKeyboard->GetKeyPress(DIK_W))
	{
		pos.y -= PLAYER_SPEED;
		float fTopWall = size.y/2;
		if( pos.y < fTopWall)
		{
			pos.y = fTopWall;
		}
		SetPosition(pos);
	}
	if(pInputKeyboard->GetKeyPress(DIK_S))
	{
		pos.y += PLAYER_SPEED;
		float fBottomall = SCREEN_HEIGHT - size.y/2;
		if( pos.y > fBottomall)
		{
			pos.y = fBottomall;
		}
		SetPosition(pos);
	}
	if(pInputKeyboard->GetKeyPress(DIK_A))
	{
		pos.x -= PLAYER_SPEED;
		float fLeftWall = size.x/2;
		if( pos.x < fLeftWall)
		{
			pos.x = fLeftWall;
		}
		SetPosition(pos);
	}
	if(pInputKeyboard->GetKeyPress(DIK_D))
	{
		pos.x += PLAYER_SPEED;
		float fRightWall = SCREEN_WIDTH - size.x/2;
		if( pos.x >  fRightWall)
		{
			pos.x = fRightWall;
		}
		SetPosition(pos);
	}
	

	//�U��
	if(pInputKeyboard->GetKeyTrigger(DIK_SPACE))
	{
		CBullet2D::Create( pos, D3DXVECTOR3( 10.0f, 10.0f, 0.0f), D3DXVECTOR3( 0.0f, -5.0f, 0.0f), LIME(1.0f), CScene::OBJTYPE_BULLET_P);
		pSound->Play( CSound::SOUND_LABEL_SE_SHOT000);
	}


	//�e�Ƃ̓����蔻��
	for( int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene( nCntScene);
		
		if( pScene != NULL)
		{
			CScene::OBJTYPE type;
			type = pScene->GetObjType();

			if( type == CScene::OBJTYPE_BULLET_E)
			{
				D3DXVECTOR3 posBullet, posPlayer;
				posBullet = pScene->GetPosition();
				posPlayer = this->GetPosition();

				if( sqrt( (posPlayer.x - posBullet.x)*(posPlayer.x - posBullet.x) + (posPlayer.y - posBullet.y)*(posPlayer.y - posBullet.y)  ) < 50.0f)
				{
					//����
					CExplosion2D::Create( posPlayer, D3DXVECTOR3(100.0f, 100.0f, 0.0f), YELLOW(1.0f));

					//�e�̔j��
 					pScene->Uninit();

					//���C�t
					CManager::GetLife()->MinusLife();
					
					//return;
				}
			}
		}
	}

	//����
	if( CManager::GetLife()->GetLife() <= 0)
	{
		Init( D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CManager::GetLife()->Init( D3DXVECTOR3( 100.0f, 35.0f, 0.0f), D3DXVECTOR3( 200.0f, 50.0f, 0.0f), 4, D3DXCOLOR( 1.0, 1.0f, 1.0f, 1.0f));
	}

	
	//�}�E�X����
	//int mouseMoveX = pInputMouse->GetMouseAxisX();
	//if( mouseMoveX != 0)
	//{
	//	pos.x += mouseMoveX;
	//	SetPosition(pos);
	//}

	//if(pInputMouse->GetMouseLeftTrigger())
	//{
	//	CBullet2D::Create(pos, D3DXVECTOR3( 20.0f, 20.0f, 0.0f));
	//}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CPlayer2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CPlayer2D *CPlayer2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer2D *pPlayer2D;
	pPlayer2D = new CPlayer2D;
	pPlayer2D->Init(pos, size);

	//�e�N�X�`���̊��蓖��
	pPlayer2D->Load( TEXTURENAME);
	
	return pPlayer2D;
}

