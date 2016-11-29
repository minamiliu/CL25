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
#include "scene2D.h"
#include "input.h"
#include "player2D.h"
#include "enemy2D.h"
#include "sound.h"

//============================================
// �}�N����`
//============================================
#define TEXTURE_BG "data/TEXTURE/bg100.png"

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CSound *CManager::m_pSound = NULL;

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
//
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

	//�v���C���[
	CPlayer2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	//�G
	CEnemy2D::Load();
	for(int cntEnemy = 0; cntEnemy < 5; cntEnemy++)
	{
		CEnemy2D::Create(D3DXVECTOR3( 100.0f + cntEnemy * 100.0f, 100.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemy2D::TYPE_000);
		CEnemy2D::Create(D3DXVECTOR3( 100.0f + cntEnemy * 100.0f, 200.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemy2D::TYPE_001);
		CEnemy2D::Create(D3DXVECTOR3( 100.0f + cntEnemy * 100.0f, 300.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemy2D::TYPE_002);
		CEnemy2D::Create(D3DXVECTOR3( 100.0f + cntEnemy * 100.0f, 400.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemy2D::TYPE_003);
	}

	//�w�i
	CScene2D::Create( D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG);
	

	return S_OK;
}

//=============================================================================
//
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
//
//=============================================================================
void CManager::Update()
{
	//�����_���[�̍X�V����
	m_pRenderer->Update();

	//�L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();

	//�}�E�X�̍X�V����
	m_pInputMouse->Update();
}

//=============================================================================
//
//=============================================================================
void CManager::Draw()
{
	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//=============================================================================
//
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
//
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
//
//=============================================================================
CInputMouse *CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//=============================================================================
//
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}