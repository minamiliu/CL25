//============================================
//
// タイトル:	 CL25課題
// プログラム名: manager.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/01
//
//============================================

//============================================
//インクルードファイル
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

//============================================
// マクロ定義
//============================================
#define TEXTURE_BG00 "data/TEXTURE/bg100.png"
#define TEXTURE_BG01 "data/TEXTURE/bg101.png"
#define TEXTURE_BG02 "data/TEXTURE/bg102.png"

#define MAX_LINE_ENEMY	(10)

//============================================
// 静的メンバー変数の初期化
//============================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CSound *CManager::m_pSound = NULL;
CScore *CManager::m_pScore = NULL;
//============================================
//コンストラクタ
//============================================
CManager::CManager()
{

}
//============================================
//デストラクタ
//============================================
CManager::~CManager()
{
	
}

//=============================================================================
//
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// レンダラーの生成
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//キーボードの生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//マウスの生成
	m_pInputMouse = new CInputMouse;
	m_pInputMouse->Init(hInstance, hWnd);

	//サウンド
	m_pSound = new CSound;
	m_pSound->Init( hWnd);
	m_pSound->Play( CSound::SOUND_LABEL_BGM001);

	//プレイヤー
	CPlayer2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//敵
	CEnemy2D::Load();
	CEnemy2D::CreateAllEnemy();


	//背景
	CBg::Create( D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG00, 0.005);
	CBg::Create( D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG01, 0.003);
	CBg::Create( D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG02, 0.001);

	//スコア
	m_pScore = CScore::Create( D3DXVECTOR3(SCREEN_WIDTH/2, 35.0f, 0.0f), D3DXVECTOR3( 300.0f, 50.0f, 0.0f), 6, D3DXCOLOR( 0.5, 0.5f, 1.0f, 1.0f));
	

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CManager::Uninit()
{
	//オブジェクトの破棄
	CScene2D::ReleaseAll();

	//キーボードの破棄
	if( m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//マウスの破棄
	if( m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//サウンドの破棄
	if( m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//レンダラーの破棄
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
	//レンダラーの更新処理
	m_pRenderer->Update();

	//キーボードの更新処理
	m_pInputKeyboard->Update();

	//マウスの更新処理
	m_pInputMouse->Update();

	//すべての敵に参照座標の更新処理
	CEnemy2D::UpdateRefPos();
}

//=============================================================================
//
//=============================================================================
void CManager::Draw()
{
	//レンダラーの描画処理
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

//=============================================================================
//
//=============================================================================
CScore *CManager::GetScore(void)
{
	return m_pScore;
}