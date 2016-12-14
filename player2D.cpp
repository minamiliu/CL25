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
#define PLAYER_LIFE	(4)
#define FRAME_DAMAGE	(20)

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
// �v���C���[�̏���������
//=============================================================================

HRESULT CPlayer2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	SetObjType( CScene::OBJTYPE_PLAYER);

	m_state = STATE_START;		//���
	m_nCntState = 60;	//��Ԃ̃J�E���^�[
	m_bUse = true;

	return S_OK;
}




//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CPlayer2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �v���C���[�̍X�V����
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
	if( m_state == STATE_NORMAL)
	{
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
					//���W
					D3DXVECTOR3 posPlayer, posBullet;
					posBullet = pScene->GetPosition();
					posPlayer = this->GetPosition();

					//�T�C�Y
					D3DXVECTOR3 sizePlayer, sizeBullet;
					sizeBullet = pScene->GetSize();
					sizePlayer = this->GetSize();

					//�����蔻��
					if(	   posBullet.x > posPlayer.x - sizePlayer.x/2.0f 
						&& posBullet.x < posPlayer.x + sizePlayer.x/2.0f 
						&& posBullet.y > posPlayer.y - sizePlayer.y/2.0f  
						&& posBullet.y < posPlayer.y + sizePlayer.y/2.0f 
						)
					{
						//�e�̔j��
						((CBullet2D*)pScene)->Uninit();

						//�_���[�W����
						this->Hit();

						//return;
					}
				}
			}
		}	
	}


	//��Ԃ̍X�V
	switch( m_state)
	{
	case STATE_DAMAGE:
		m_nCntState--;
		if( m_nCntState <= 0)
		{
			m_state = STATE_NORMAL;
			//�F�����ɖ߂�
			this->SetColor( WHITE(1.0f));
		}
		break;
	case STATE_START:
		m_nCntState--;
		if( m_nCntState <= 0)
		{
			m_state = STATE_NORMAL;
			m_bUse = true;
		}
		else if( m_nCntState % 3 == 0)
		{
			m_bUse = !m_bUse;
		}
		break;
	}
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CPlayer2D::Draw(void)
{
	if( m_bUse)
	{
		CScene2D::Draw();
	}
}

//=============================================================================
// �v���C���[�̐�������
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
//=============================================================================
// �_���[�W����
//=============================================================================
bool CPlayer2D::Hit(void)
{
	D3DXVECTOR3 pos = this->GetPosition();

	//����
	CExplosion2D::Create( pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f), YELLOW(1.0f));

	//���C�t
	CManager::GetLife()->MinusLife();

	if( CManager::GetLife()->GetLife() <= 0)
	{
		//����
		Init( D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CManager::GetLife()->Init( D3DXVECTOR3( 100.0f, 35.0f, 0.0f), D3DXVECTOR3( 200.0f, 50.0f, 0.0f), PLAYER_LIFE, D3DXCOLOR( 1.0, 1.0f, 1.0f, 1.0f));	
		return false;
	}
	else
	{
		//�_���[�W��Ԃɐݒ�
		m_state = STATE_DAMAGE;
		m_nCntState = FRAME_DAMAGE;
		this->SetColor(RED(1.0f));
	}
				
	return true;
}

