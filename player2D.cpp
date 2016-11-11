//============================================
//
// タイトル:	 CL25課題
// プログラム名: player2D.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/19
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "input.h"
#include "player2D.h"
#include "bullet2D.h"

//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/player000.png"

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CPlayer2D::CPlayer2D()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CPlayer2D::~CPlayer2D()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CPlayer2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CPlayer2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CPlayer2D::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	D3DXVECTOR3 pos = CPlayer2D::GetPosition();

	//移動
	if(pInputKeyboard->GetKeyPress(DIK_W))
	{
		pos.y -= 5.0f;
		CPlayer2D::SetPosition(pos);
	}
	if(pInputKeyboard->GetKeyPress(DIK_S))
	{
		pos.y += 5.0f;
		SetPosition(pos);
	}
	if(pInputKeyboard->GetKeyPress(DIK_A))
	{
		pos.x -= 5.0f;
		SetPosition(pos);
	}
	if(pInputKeyboard->GetKeyPress(DIK_D))
	{
		pos.x += 5.0f;
		SetPosition(pos);
	}
	
	int mouseMoveX = pInputMouse->GetMouseAxisX();
	if( mouseMoveX != 0)
	{
		pos.x += mouseMoveX;
		SetPosition(pos);
	}


	//攻撃
	if(pInputKeyboard->GetKeyTrigger(DIK_SPACE))
	{
		CBullet2D::Create(pos, D3DXVECTOR3( 20.0f, 20.0f, 0.0f));
	}
	if(pInputMouse->GetMouseLeftTrigger())
	{
		CBullet2D::Create(pos, D3DXVECTOR3( 20.0f, 20.0f, 0.0f));
	}

	CScene2D::Update();
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CPlayer2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CPlayer2D *CPlayer2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer2D *pPlayer2D;
	pPlayer2D = new CPlayer2D;
	pPlayer2D->Init(pos, size);

	//テクスチャの割り当て
	pPlayer2D->Load( TEXTURENAME);
	
	return pPlayer2D;
}

