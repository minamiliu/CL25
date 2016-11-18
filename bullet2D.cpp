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

//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/bullet000.png"

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
// �|���S���̏���������
//=============================================================================

HRESULT CBullet2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	SetObjType( CScene::OBJTYPE_BULLET);

	m_move = D3DXVECTOR3( 0.0f, -5.0f, 0.0f);
	m_nCntFrame = 0;

	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CBullet2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CBullet2D::Update(void)
{
	CScene2D::Update();

	//�e�̈ړ��X�V
	D3DXVECTOR3 pos = CScene2D::GetPosition();
	pos += m_move;
	CScene2D::SetPosition(pos);

	//�e�������鏈��
	m_nCntFrame++;
	if( m_nCntFrame > 120)
	{
		CExplosion2D::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		this->Uninit();
		return;
	}

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
				D3DXVECTOR3 posEnemy, posBullet;
				posEnemy = pScene->GetPosition();
				posBullet = this->GetPosition();

				if( sqrt( (posEnemy.x - posBullet.x)*(posEnemy.x - posBullet.x) + (posEnemy.y - posBullet.y)*(posEnemy.y - posBullet.y)  ) < 50.0f)
				{
					CExplosion2D::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));

					//�G�̔j��
 					pScene->Uninit();

					//�e(����)�̔j��
					this->Uninit();

					return;
				}
			}
		}
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CBullet2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CBullet2D *CBullet2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBullet2D *pBullet2D;
	pBullet2D = new CBullet2D;
	pBullet2D->Init(pos, size);

	//�e�N�X�`���̓ǂݍ���
	pBullet2D->Load();

	//�e�N�X�`���̊��蓖��
	pBullet2D->BindTexture(m_pTexture);
	
	return pBullet2D;
}

//=============================================================================
//
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
//
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

