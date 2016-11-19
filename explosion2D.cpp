//============================================
//
// タイトル:	 CL25課題
// プログラム名: explosion2D.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/11
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "explosion2D.h"

//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/explosion000.png"

#define	TEX_PATTERN_DIVIDE_X		(8)								// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// アニメーションパターンのテクスチャ内での分割数(Ｙ方向)
#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)		// １パターンのテクスチャサイズ(Ｘ方向)(1.0f/X方向分割数)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)		// １パターンのテクスチャサイズ(Ｙ方向)(1.0f/Y方向分割数)

#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X*TEX_PATTERN_DIVIDE_Y)	// アニメーションのパターン数(X方向分割数×Y方向分割数)
#define	TIME_CHANGE_PATTERN			(5)								// アニメーションの切り替わるタイミング(フレーム数)

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CExplosion2D::m_pTexture = NULL;

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CExplosion2D::CExplosion2D()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CExplosion2D::~CExplosion2D()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CExplosion2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size, D3DXVECTOR2(TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
	SetObjType( CScene::OBJTYPE_EXPLOSION);

	//アニメーション
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CExplosion2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CExplosion2D::Update(void)
{
	CScene2D::Update();
	
	m_nCounterAnim++;
	if( m_nCounterAnim >= TIME_CHANGE_PATTERN )
	{

		// パターンの切り替え
		m_nPatternAnim++;
		if( m_nPatternAnim >= NUM_ANIM_PATTERN){
			this->Uninit();
		}
		else
		{
			// テクスチャ座標を設定
			ChangeTextureAnime( 
				m_nPatternAnim, 
				D3DXVECTOR2(TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y), 
				D3DXVECTOR2(TEX_PATTERN_DIVIDE_X, TEX_PATTERN_DIVIDE_Y));

			//m_nCounterAnimのリセット
			m_nCounterAnim = 0;
		}
	}

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CExplosion2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CExplosion2D *CExplosion2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion2D *pExplosion;
	pExplosion = new CExplosion2D;
	pExplosion->Init(pos, size);

	//テクスチャの読み込み
	pExplosion->Load();

	//テクスチャの割り当て
	pExplosion->BindTexture(m_pTexture);
	
	return pExplosion;
}

//=============================================================================
//
//=============================================================================
HRESULT CExplosion2D::Load(void)
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
//
//=============================================================================
void CExplosion2D::Unload(void)
{
	//テクスチャの破棄
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


