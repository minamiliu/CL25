//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: enemy.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/18
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "enemy2D.h"
#include "bullet2D.h"
#include "explosion2D.h"

//============================================
// �}�N����`
//============================================
#define TEXTURE_ENEMY000 "data/TEXTURE/enemy000.png"
#define TEXTURE_ENEMY001 "data/TEXTURE/enemy001.png"
#define TEXTURE_ENEMY002 "data/TEXTURE/enemy002.png"
#define TEXTURE_ENEMY003 "data/TEXTURE/enemy003.png"
#define TEXTURE_ENEMY004 "data/TEXTURE/enemy004.png"

#define	TEX_PATTERN_DIVIDE_X		(2)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�w����)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�x����)
#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)		// �P�p�^�[���̃e�N�X�`���T�C�Y(�w����)(1.0f/X����������)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)		// �P�p�^�[���̃e�N�X�`���T�C�Y(�x����)(1.0f/Y����������)
#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X*TEX_PATTERN_DIVIDE_Y)	// �A�j���[�V�����̃p�^�[����(X�����������~Y����������)
#define	TIME_CHANGE_PATTERN			(30)								// �A�j���[�V�����̐؂�ւ��^�C�~���O(�t���[����)

#define ENEMY_SPEED_X	(3.0f)
#define ENEMY_START_POSX	(100.0f)
#define MAX_LINE_ENEMY	(10)
#define FRAME_DAMAGE	(20)

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9 CEnemy2D::m_pTexture[CEnemy2D::TYPE_MAX] = {};
D3DXVECTOR3 CEnemy2D::m_move = D3DXVECTOR3( ENEMY_SPEED_X, 0.0f, 0.0f);

float CEnemy2D::m_fPosXRef =  0.0f;
bool CEnemy2D::bHitWall = false;


//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEnemy2D::CEnemy2D()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEnemy2D::~CEnemy2D()
{
	
}


//=============================================================================
// �G�̏���������
//=============================================================================

HRESULT CEnemy2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, int nLife)
{
	CScene2D::Init(pos, size, D3DXVECTOR2(TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
	SetObjType( CScene::OBJTYPE_ENEMY);

	
	m_fPosXDiff = pos.x - m_fPosXRef; //���W����L�^

	m_type = type;
	m_nLife = nLife;				//���C�t
	m_state = STATE_NORMAL;		//���
	
	m_nCntState = 0;	//��Ԃ̃J�E���^�[
	m_nCounterAnim = 0;	// �G�̃A�j���[�V�����J�E���^�[
	m_nPatternAnim = 0;	// �G�̃A�j���[�V�����p�^�[��No.
	m_fCntShake = 0;

	return S_OK;
}




//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemy2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemy2D::Update(void)
{
	D3DXVECTOR3 size = CScene2D::GetSize();
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	//�h��鏈��
	pos.y += sinf(m_fCntShake) * 1.0f;
	m_fCntShake += 0.1f;
	m_fCntShake = ( m_fCntShake >= D3DX_PI * 2) ? 0.0f : m_fCntShake; 

	//�ړ�����
	pos.x = m_fPosXRef + m_fPosXDiff;

	//���E���E���X�V
	if( bHitWall == false)
	{
		if(pos.x < 0.0f + size.x/2 || pos.x > SCREEN_WIDTH - size.x/2)
		{
			bHitWall = true;
		}
	}

	//�A�j���[�V����
	m_nCounterAnim++;
	if( m_nCounterAnim >= TIME_CHANGE_PATTERN )
	{

		// �p�^�[���̐؂�ւ�
		m_nPatternAnim++;
		if( m_nPatternAnim >= NUM_ANIM_PATTERN){

			m_nPatternAnim = 0;
		}
		
		{// �e�N�X�`�����W��ݒ�
			ChangeTextureAnime( 
				m_nPatternAnim, 
				D3DXVECTOR2(TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y), 
				D3DXVECTOR2(TEX_PATTERN_DIVIDE_X, TEX_PATTERN_DIVIDE_Y));

			//m_nCounterAnim�̃��Z�b�g
			m_nCounterAnim = 0;
		}
	}

	//�e���o��
	int nRand = rand() % 1000;
	if( nRand < 1)
	{
		CBullet2D::Create( pos, D3DXVECTOR3( 10.0f, 10.0f, 0.0f), D3DXVECTOR3( 0.0f, 5.0f, 0.0f), MASENTA(1.0f), CScene::OBJTYPE_BULLET_E);
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
	}

	//�e�̈ړ��X�V
	CScene2D::SetPosition(pos);
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemy2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �G�̐�������
//=============================================================================
CEnemy2D *CEnemy2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, int nLife)
{
	CEnemy2D *pEnemy;
	pEnemy = new CEnemy2D;
	pEnemy->Init(pos, size, type, nLife);

	//�e�N�X�`���̊��蓖��
	pEnemy->BindTexture(m_pTexture[type]);
	
	return pEnemy;
}

//=============================================================================
//�e�N�X�`���̃��[�h
//=============================================================================
HRESULT CEnemy2D::Load(void)
{
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
		case TYPE_000:
			strFileName = TEXTURE_ENEMY000;
			break;

		case TYPE_001:
			strFileName = TEXTURE_ENEMY001;
			break;

		case TYPE_002:
			strFileName = TEXTURE_ENEMY002;
			break;

		case TYPE_003:
			strFileName = TEXTURE_ENEMY003;
			break;

		case TYPE_004:
			strFileName = TEXTURE_ENEMY004;
			break;

		}

		if( m_pTexture[cntType] == NULL)
		{
			LPDIRECT3DDEVICE9 pDevice;
			pDevice = CManager::GetRenderer()->GetDevice();

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile( pDevice, strFileName, &m_pTexture[cntType]);
		}	
	}


	return S_OK;
}

//=============================================================================
//�e�N�X�`���̃A�����[�h
//=============================================================================
void CEnemy2D::Unload(void)
{
	//�e�N�X�`���̔j��
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		if( m_pTexture[cntType] != NULL)
		{
			m_pTexture[cntType]->Release();
			m_pTexture[cntType] = NULL;
		}	
	}

}

//=============================================================================
//�G�̎�ނ��擾
//=============================================================================
CEnemy2D::TYPE CEnemy2D::GetType(void)
{
	return m_type;
}
//=============================================================================
//�G�S�̂̐���(�X�e�[�W0)
//=============================================================================
void CEnemy2D::CreateAllEnemy(void)
{
	m_fPosXRef = ENEMY_START_POSX;

	for(int cntEnemy = 0; cntEnemy < MAX_LINE_ENEMY; cntEnemy++)
	{
		CEnemy2D::Create(D3DXVECTOR3( ENEMY_START_POSX + cntEnemy * 100.0f, 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), TYPE_000, 5);
		CEnemy2D::Create(D3DXVECTOR3( ENEMY_START_POSX + cntEnemy * 100.0f, 150.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), TYPE_001, 4);
		CEnemy2D::Create(D3DXVECTOR3( ENEMY_START_POSX + cntEnemy * 100.0f, 200.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), TYPE_002, 3);
		CEnemy2D::Create(D3DXVECTOR3( ENEMY_START_POSX + cntEnemy * 100.0f, 250.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), TYPE_003, 2);
		CEnemy2D::Create(D3DXVECTOR3( ENEMY_START_POSX + cntEnemy * 100.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), TYPE_004, 1);
	}
}
//=============================================================================
//�G�S�̂̊���W�̍X�V����
//=============================================================================
void CEnemy2D::UpdateRefPos(void)
{
	//�ǂɒ��˕Ԃ�
	if( bHitWall == true)
	{
		m_move *= -1;
		bHitWall = false;
	}

	//���W��X�V
	m_fPosXRef += m_move.x;
}
//=============================================================================
//�G�̃_���[�W����
//=============================================================================
bool CEnemy2D::Hit(int nDamage)
{
	m_nLife -= nDamage;
	if( m_nLife <= 0)
	{
		D3DXVECTOR3 posEnemy = GetPosition();

		//�F�t���̔����̐���
		switch( m_type)
		{
		case TYPE_000:
			CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), RED(1.0f));
			break;

		case TYPE_001:
			CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), WHITE(1.0f));
			break;

		case TYPE_002:
			CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), GRAY(1.0f));
			break;

		case TYPE_003:
			CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), BLUE(1.0f));
			break;

		case TYPE_004:
			CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), GREEN(1.0f));
			break;
		}

		//�G�̔j��
		//this->Uninit();
		this->SetDelFlg();

		return true;
	}
	else
	{
		m_state = STATE_DAMAGE;
		m_nCntState = FRAME_DAMAGE;

		//�F���_���[�W�F�ɕύX
		this->SetColor( RED(1.0f));
	}
	return false;
}
