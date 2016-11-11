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

//============================================
// �}�N����`
//============================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;

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

	//�I�u�W�F�N�g�̐���(2D�|���S��)
	CPlayer2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));

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
