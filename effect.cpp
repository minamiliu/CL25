//============================================
//
// タイトル:	 CL25課題
// プログラム名: effect.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/16
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"

//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/effect000.jpg"

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CEffect::CEffect()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CEffect::~CEffect()
{
	
}


//=============================================================================
// 弾の初期化処理
//=============================================================================

HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col)
{
	CScene2D::Init(pos, size);
	SetColor(col);
	m_col = col;
	
	return S_OK;
}




//=============================================================================
// 弾の終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// 弾の更新処理
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
// 弾の描画処理
//=============================================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 加算合成
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD);	// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// 通常ブレンド 
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD);	// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// 弾の生成処理
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col)
{
	CEffect *pEffect;
	pEffect = new CEffect;
	pEffect->Init(pos, size, col);

	//テクスチャの割り当て
	pEffect->BindTexture(m_pTexture);
	
	return pEffect;
}

//=============================================================================
//テクスチャのロード
//=============================================================================
HRESULT CEffect::Load(void)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice, TEXTURENAME, &m_pTexture);
	}

	return S_OK;
}

//=============================================================================
//テクスチャのアンロード
//=============================================================================
void CEffect::Unload(void)
{
	//テクスチャの破棄
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

