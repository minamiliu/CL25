//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: score.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/30
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "heart.h"
#include "life.h"


//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/life000.png"

#define	TEX_PATTERN_DIVIDE_X		(1)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�w����)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�x����)
#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)		// �P�p�^�[���̃e�N�X�`���T�C�Y(�w����)(1.0f/X����������)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)		// �P�p�^�[���̃e�N�X�`���T�C�Y(�x����)(1.0f/Y����������)

#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X*TEX_PATTERN_DIVIDE_Y)	// �A�j���[�V�����̃p�^�[����(X�����������~Y����������)
//#define	TIME_CHANGE_PATTERN			(5)								// �A�j���[�V�����̐؂�ւ��^�C�~���O(�t���[����)

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CLife::CLife()
{
	m_ppPolygon = NULL;
	m_pTexture = NULL;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CLife::~CLife()
{
	
}


//=============================================================================
// ���C�t�̏���������
//=============================================================================
HRESULT CLife::Init(void)
{
	return S_OK;
}
HRESULT CLife::Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, const D3DXCOLOR &col)
{
	//�����l��ݒ�
	m_nMaxKeta = maxKeta;
	m_nValue = maxKeta;
	m_pos = numberPos;
	m_size = numberSize;

	//Number�|�C���^�[�z��̐���
	m_ppPolygon = new CHeart*[maxKeta];

	//�X�^�[�g�ʒu(�E)�ƌ��T�C�Y�̌v�Z
	D3DXVECTOR3 rightPos = numberPos;
	D3DXVECTOR3 ketaSize = numberSize;
	ketaSize.x /= maxKeta;
	rightPos.x = numberPos.x + ketaSize.x * (maxKeta - 1) / 2.0f;
	
	//������Number�̐���
	D3DXVECTOR3 tmpPos = rightPos;
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		m_ppPolygon[cntKeta] = CHeart::Create( tmpPos , ketaSize, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
		
		//�e�N�X�`���̊��蓖��
		m_ppPolygon[cntKeta]->BindTexture(m_pTexture);
		
		tmpPos.x -= ketaSize.x;
	}



	return S_OK;
}




//=============================================================================
// ���C�t�̏I������
//=============================================================================
void CLife::Uninit(void)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		if( m_ppPolygon[cntKeta] != NULL)
		{				
			m_ppPolygon[cntKeta]->Uninit();
			m_ppPolygon[cntKeta] = NULL;	
		}
	}

	delete[] m_ppPolygon;
	m_ppPolygon = NULL;

	//�e�N�X�`���̔j��
	this->Unload();
	
	//�I�u�W�F�N�g�̔j��
	Release();
}


//=============================================================================
// ���C�t�̍X�V����
//=============================================================================
void CLife::Update(void)
{
	
}

//=============================================================================
// ���C�t�̕`�揈��
//=============================================================================
void CLife::Draw(void)
{
	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		if( m_ppPolygon[nKeta] != NULL)
		{
			m_ppPolygon[nKeta]->Draw();
		}
	}
}

//=============================================================================
// ���C�t�̐�������
//=============================================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int maxKeta, const D3DXCOLOR &col)
{
	CLife *pLife;
	pLife = new CLife;

	//�e�N�X�`���̓ǂݍ���
	pLife->Load();

	pLife->Init(pos, size, maxKeta, col);
	
	return pLife;
}

//=============================================================================
//�e�N�X�`���̃��[�h
//=============================================================================
HRESULT CLife::Load(void)
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
void CLife::Unload(void)
{
	//�e�N�X�`���̔j��
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


//=============================================================================
//���C�t������
//=============================================================================
void CLife::MinusLife(void)
{
	m_nValue--;
	if( m_nValue < 0) m_nValue = 0;

	int keta = m_nMaxKeta - m_nValue -1;

	if( m_ppPolygon[keta] != NULL)
	{
		m_ppPolygon[keta]->Uninit();
		m_ppPolygon[keta] = NULL;	
	}

}
//=============================================================================
//���W���擾
//=============================================================================
D3DXVECTOR3 CLife::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
//�T�C�Y���擾
//=============================================================================
D3DXVECTOR3 CLife::GetSize(void)
{
	return m_size;
}

//=============================================================================
//���C�t���擾
//=============================================================================
int CLife::GetLife(void)
{
	return m_nValue;
}
