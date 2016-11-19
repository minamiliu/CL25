//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: explosion2D.cpp
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
#include "explosion2D.h"

//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/explosion000.png"

#define	TEX_PATTERN_DIVIDE_X		(8)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�w����)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�x����)
#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)		// �P�p�^�[���̃e�N�X�`���T�C�Y(�w����)(1.0f/X����������)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)		// �P�p�^�[���̃e�N�X�`���T�C�Y(�x����)(1.0f/Y����������)

#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X*TEX_PATTERN_DIVIDE_Y)	// �A�j���[�V�����̃p�^�[����(X�����������~Y����������)
#define	TIME_CHANGE_PATTERN			(5)								// �A�j���[�V�����̐؂�ւ��^�C�~���O(�t���[����)

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9 CExplosion2D::m_pTexture = NULL;

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CExplosion2D::CExplosion2D()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CExplosion2D::~CExplosion2D()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CExplosion2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size, D3DXVECTOR2(TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
	SetObjType( CScene::OBJTYPE_EXPLOSION);

	//�A�j���[�V����
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CExplosion2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CExplosion2D::Update(void)
{
	CScene2D::Update();
	
	m_nCounterAnim++;
	if( m_nCounterAnim >= TIME_CHANGE_PATTERN )
	{

		// �p�^�[���̐؂�ւ�
		m_nPatternAnim++;
		if( m_nPatternAnim >= NUM_ANIM_PATTERN){
			this->Uninit();
		}
		else
		{
			// �e�N�X�`�����W��ݒ�
			ChangeTextureAnime( 
				m_nPatternAnim, 
				D3DXVECTOR2(TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y), 
				D3DXVECTOR2(TEX_PATTERN_DIVIDE_X, TEX_PATTERN_DIVIDE_Y));

			//m_nCounterAnim�̃��Z�b�g
			m_nCounterAnim = 0;
		}
	}

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CExplosion2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CExplosion2D *CExplosion2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion2D *pExplosion;
	pExplosion = new CExplosion2D;
	pExplosion->Init(pos, size);

	//�e�N�X�`���̓ǂݍ���
	pExplosion->Load();

	//�e�N�X�`���̊��蓖��
	pExplosion->BindTexture(m_pTexture);
	
	return pExplosion;
}

//=============================================================================
//
//=============================================================================
HRESULT CExplosion2D::Load(void)
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
void CExplosion2D::Unload(void)
{
	//�e�N�X�`���̔j��
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


