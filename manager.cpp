//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: manager.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/01
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "bg.h"
#include "input.h"
#include "player2D.h"
#include "enemy2D.h"
#include "sound.h"
#include "score.h"
#include "life.h"
#include "bullet2D.h"
#include "effect.h"

//============================================
// �}�N����`
//============================================
#define TEXTURE_BG00 "data/TEXTURE/bg100.png"
#define TEXTURE_BG01 "data/TEXTURE/bg101.png"
#define TEXTURE_BG02 "data/TEXTURE/bg102.png"

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CSound *CManager::m_pSound = NULL;
CScore *CManager::m_pScore = NULL;
CLife *CManager::m_pLife = NULL;
//============================================
//�R���X�g���N�^
//============================================
CManager::CManager()
{

}
//============================================
//�f�X�g���N�^
//============================================
CManager::~CManager()
{
	
}

//=============================================================================
//������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �����_���[�̐���
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//�L�[�{�[�h�̐���
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//�}�E�X�̐���
	m_pInputMouse = new CInputMouse;
	m_pInputMouse->Init(hInstance, hWnd);

	//�T�E���h
	m_pSound = new CSound;
	m_pSound->Init( hWnd);
	m_pSound->Play( CSound::SOUND_LABEL_BGM001);

	//�e�N�X�`���̃��[�h
	CEnemy2D::Load();
	CBullet2D::Load();
	CEffect::Load();

	//�v���C���[
	CPlayer2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//�G
	CEnemy2D::CreateAllEnemy();

	//�w�i
	CBg::Create( D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG00, 0.005);
	CBg::Create( D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG01, 0.003);
	CBg::Create( D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG02, 0.001);

	//�X�R�A
	m_pScore = CScore::Create( D3DXVECTOR3(SCREEN_WIDTH - 150, 35.0f, 0.0f), D3DXVECTOR3( 300.0f, 50.0f, 0.0f), 6, D3DXCOLOR( 0.5, 0.5f, 1.0f, 1.0f));
	
	//���C�t
	m_pLife = CLife::Create( D3DXVECTOR3( 100.0f, 35.0f, 0.0f), D3DXVECTOR3( 200.0f, 50.0f, 0.0f), 4, D3DXCOLOR( 1.0, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
//�j��
//=============================================================================
void CManager::Uninit()
{
	//�I�u�W�F�N�g�̔j��
	CScene2D::ReleaseAll();

	//�L�[�{�[�h�̔j��
	if( m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�}�E�X�̔j��
	if( m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//�T�E���h�̔j��
	if( m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//�����_���[�̔j��
	if( m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CManager::Update()
{
	//�����_���[�̍X�V����
	m_pRenderer->Update();

	//�L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();

	//�}�E�X�̍X�V����
	m_pInputMouse->Update();

	//���ׂĂ̓G�ɎQ�ƍ��W�̍X�V����
	CEnemy2D::UpdateRefPos();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CManager::Draw()
{
	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//=============================================================================
//�����_���[���擾
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
//�L�[�{�[�h���擾
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
//�}�E�X���擾
//=============================================================================
CInputMouse *CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//=============================================================================
//�T�E���h���擾
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
//�X�R�A���擾
//=============================================================================
CScore *CManager::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
//���C�t���擾
//=============================================================================
CLife *CManager::GetLife(void)
{
	return m_pLife;
}