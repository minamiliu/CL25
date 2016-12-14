//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: bullet2D.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/11
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "bullet2D.h"
#include "explosion2D.h"
#include "score.h"
#include "enemy2D.h"

//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/bullet000.png"
#define BULLET_DAMAGE	(1)
//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9 CBullet2D::m_pTexture = NULL;

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBullet2D::CBullet2D()
{
	m_move = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBullet2D::~CBullet2D()
{
	
}


//=============================================================================
// �e�̏���������
//=============================================================================

HRESULT CBullet2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, const D3DXCOLOR &col, CScene::OBJTYPE obj)
{
	CScene2D::Init(pos, size);
	SetObjType( obj);
	SetColor(col);

	m_move = move;
	m_nCntFrame = 0;
	
	return S_OK;
}




//=============================================================================
// �e�̏I������
//=============================================================================
void CBullet2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �e�̍X�V����
//=============================================================================
void CBullet2D::Update(void)
{

	//�e�̈ړ��X�V
	D3DXVECTOR3 pos = CScene2D::GetPosition();
	pos += m_move;
	CScene2D::SetPosition(pos);

	//�e�������鏈��
	m_nCntFrame++;
	if( m_nCntFrame > 120)
	{
		CExplosion2D::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f), WHITE(1.0f));
		this->Uninit();
		return;
	}

	//�G�Ƃ̓����蔻��
	if(this->GetObjType() == CScene::OBJTYPE_BULLET_P)
	{
		for( int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene *pScene;
			pScene = CScene::GetScene( nCntScene);
		
			if( pScene != NULL)
			{
				CScene::OBJTYPE type;
				type = pScene->GetObjType();

				if( type == CScene::OBJTYPE_ENEMY)
				{
					//���W
					D3DXVECTOR3 posEnemy, posBullet;
					posEnemy = pScene->GetPosition();
					posBullet = this->GetPosition();

					//�T�C�Y
					D3DXVECTOR3 sizeEnemy, sizeBullet;
					sizeEnemy = pScene->GetSize();
					sizeBullet = this->GetSize();

					//�����蔻��
					if(	   posBullet.x > posEnemy.x - sizeEnemy.x/2.0f 
						&& posBullet.x < posEnemy.x + sizeEnemy.x/2.0f 
						&& posBullet.y > posEnemy.y - sizeEnemy.y/2.0f  
						&& posBullet.y < posEnemy.y + sizeEnemy.y/2.0f 
						)
					{
						((CEnemy2D*)pScene)->Hit( BULLET_DAMAGE);

						//�e(����)�̔j��
						this->Uninit();

						//�X�R�A
						CManager::GetScore()->AddScore( 100);
					
						return;
					}
				}
			}
		}	
	}

}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void CBullet2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �e�̐�������
//=============================================================================
CBullet2D *CBullet2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, const D3DXCOLOR &col, CScene::OBJTYPE obj)
{
	CBullet2D *pBullet2D;
	pBullet2D = new CBullet2D;
	pBullet2D->Init(pos, size, move, col, obj);

	//�e�N�X�`���̓ǂݍ���
	pBullet2D->Load();

	//�e�N�X�`���̊��蓖��
	pBullet2D->BindTexture(m_pTexture);
	
	return pBullet2D;
}

//=============================================================================
//�e�N�X�`���̃��[�h
//=============================================================================
HRESULT CBullet2D::Load(void)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile( pDevice, TEXTURENAME, &m_pTexture);
	}

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̃A�����[�h
//=============================================================================
void CBullet2D::Unload(void)
{
	//�e�N�X�`���̔j��
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

