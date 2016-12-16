//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: effect.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/16
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"

//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/effect000.jpg"

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEffect::CEffect()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{
	
}


//=============================================================================
// �e�̏���������
//=============================================================================

HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col)
{
	CScene2D::Init(pos, size);
	SetColor(col);
	m_col = col;
	
	return S_OK;
}




//=============================================================================
// �e�̏I������
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �e�̍X�V����
//=============================================================================
void CEffect::Update(void)
{
	m_col.a -= 0.1f;
 	SetColor( m_col);

	if( m_col.a <= 0)
	{
		this->Uninit();
	}
}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���Z����
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD);	// ���� = �]����(SRC) + �]����(DEST)
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// �ʏ�u�����h 
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD);	// ���� = �]����(SRC) + �]����(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �e�̐�������
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col)
{
	CEffect *pEffect;
	pEffect = new CEffect;
	pEffect->Init(pos, size, col);

	//�e�N�X�`���̊��蓖��
	pEffect->BindTexture(m_pTexture);
	
	return pEffect;
}

//=============================================================================
//�e�N�X�`���̃��[�h
//=============================================================================
HRESULT CEffect::Load(void)
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
void CEffect::Unload(void)
{
	//�e�N�X�`���̔j��
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

