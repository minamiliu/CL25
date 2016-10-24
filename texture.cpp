//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: texture.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/19
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "texture.h"
#include "renderer.h"


//============================================
// �}�N����`
//============================================

// ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define NUM_VERTEX (4)
#define NUM_POLYGON (2)
#define POLYGON_POS_X	(SCREEN_WIDTH/2)//�|���S���̍���X
#define POLYGON_POS_Y	(SCREEN_HEIGHT/2)//�|���S���̍���Y
#define POLYGON_SIZE_X	(300)//�|���S����SIZE X
#define POLYGON_SIZE_Y	(300)//�|���S����SIZE Y
#define POLYGON_TEXTURENAME "data/TEXTURE/player000.png"

//============================================
// �\���̒�`
//============================================
// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

//============================================
//�R���X�g���N�^
//============================================
CTexture::CTexture()
{
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);			// �|���S���̈ʒu
}

CTexture::~CTexture()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;	
	pDevice = GetRenderer()->GetDevice();

	// �|���S���̈ʒu��ݒ�
	m_pos = D3DXVECTOR3( POLYGON_POS_X, POLYGON_POS_Y, 0.0f);

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile( pDevice, POLYGON_TEXTURENAME, &m_pTexture);

	// ���_�o�b�t�@�̐���
	if(FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	//���_�f�[�^�̃o�b�t�@�T�C�Y 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED, 
		&m_pVtxBuff,		//���_�o�b�t�@�C���^�[�t�F�[�X�̃|�C���^
		NULL)))
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	// �|���S���̈ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3(POLYGON_POS_X - (POLYGON_SIZE_X/2), POLYGON_POS_Y - (POLYGON_SIZE_Y/2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(POLYGON_POS_X + (POLYGON_SIZE_X/2), POLYGON_POS_Y - (POLYGON_SIZE_Y/2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(POLYGON_POS_X - (POLYGON_SIZE_X/2), POLYGON_POS_Y + (POLYGON_SIZE_Y/2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(POLYGON_POS_X + (POLYGON_SIZE_X/2), POLYGON_POS_Y + (POLYGON_SIZE_Y/2), 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//color
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	//�e�N�X�`�����W�w��
	pVtx[0].tex = D3DXVECTOR2(0.0F, 0.0F);
	pVtx[1].tex = D3DXVECTOR2(1.0F, 0.0F);
	pVtx[2].tex = D3DXVECTOR2(0.0F, 1.0F);
	pVtx[3].tex = D3DXVECTOR2(1.0F, 1.0F);

	m_pVtxBuff->Unlock();

	return S_OK;
}



//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTexture::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if(m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �e�N�X�`���̔j��
	if(m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTexture::Update(void)
{
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTexture::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,						//���[�h����ŏ��̒��_�C���f�b�N�X
		NUM_POLYGON				//�|���S���̐�
	);
}