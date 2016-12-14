//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: score.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/30
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "heart.h"
#include "life.h"


//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/life000.png"

#define	TEX_PATTERN_DIVIDE_X		(1)								// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// アニメーションパターンのテクスチャ内での分割数(Ｙ方向)
#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)		// １パターンのテクスチャサイズ(Ｘ方向)(1.0f/X方向分割数)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)		// １パターンのテクスチャサイズ(Ｙ方向)(1.0f/Y方向分割数)

#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X*TEX_PATTERN_DIVIDE_Y)	// アニメーションのパターン数(X方向分割数×Y方向分割数)
//#define	TIME_CHANGE_PATTERN			(5)								// アニメーションの切り替わるタイミング(フレーム数)

//============================================
// 静的メンバー変数の初期化
//============================================

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CLife::CLife()
{
	m_ppPolygon = NULL;
	m_pTexture = NULL;
}

//=============================================================================
//デストラクタ
//=============================================================================
CLife::~CLife()
{
	
}


//=============================================================================
// ライフの初期化処理
//=============================================================================
HRESULT CLife::Init(void)
{
	return S_OK;
}
HRESULT CLife::Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, const D3DXCOLOR &col)
{
	//初期値を設定
	m_nMaxKeta = maxKeta;
	m_nValue = maxKeta;
	m_pos = numberPos;
	m_size = numberSize;

	//Numberポインター配列の生成
	m_ppPolygon = new CHeart*[maxKeta];

	//スタート位置(右)と桁サイズの計算
	D3DXVECTOR3 rightPos = numberPos;
	D3DXVECTOR3 ketaSize = numberSize;
	ketaSize.x /= maxKeta;
	rightPos.x = numberPos.x + ketaSize.x * (maxKeta - 1) / 2.0f;
	
	//桁分のNumberの生成
	D3DXVECTOR3 tmpPos = rightPos;
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		m_ppPolygon[cntKeta] = CHeart::Create( tmpPos , ketaSize, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
		
		//テクスチャの割り当て
		m_ppPolygon[cntKeta]->BindTexture(m_pTexture);
		
		tmpPos.x -= ketaSize.x;
	}



	return S_OK;
}




//=============================================================================
// ライフの終了処理
//=============================================================================
void CLife::Uninit(void)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		if( m_ppPolygon[cntKeta] != NULL)
		{				
			m_ppPolygon[cntKeta]->Uninit();
			m_ppPolygon[cntKeta] = NULL;	
		}
	}

	delete[] m_ppPolygon;
	m_ppPolygon = NULL;

	//テクスチャの破棄
	this->Unload();
	
	//オブジェクトの破棄
	Release();
}


//=============================================================================
// ライフの更新処理
//=============================================================================
void CLife::Update(void)
{
	
}

//=============================================================================
// ライフの描画処理
//=============================================================================
void CLife::Draw(void)
{
	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		if( m_ppPolygon[nKeta] != NULL)
		{
			m_ppPolygon[nKeta]->Draw();
		}
	}
}

//=============================================================================
// ライフの生成処理
//=============================================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int maxKeta, const D3DXCOLOR &col)
{
	CLife *pLife;
	pLife = new CLife;

	//テクスチャの読み込み
	pLife->Load();

	pLife->Init(pos, size, maxKeta, col);
	
	return pLife;
}

//=============================================================================
//テクスチャのロード
//=============================================================================
HRESULT CLife::Load(void)
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
void CLife::Unload(void)
{
	//テクスチャの破棄
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


//=============================================================================
//ライフを減る
//=============================================================================
void CLife::MinusLife(void)
{
	m_nValue--;
	if( m_nValue < 0) m_nValue = 0;

	int keta = m_nMaxKeta - m_nValue -1;

	if( m_ppPolygon[keta] != NULL)
	{
		m_ppPolygon[keta]->Uninit();
		m_ppPolygon[keta] = NULL;	
	}

}
//=============================================================================
//座標を取得
//=============================================================================
D3DXVECTOR3 CLife::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
//サイズを取得
//=============================================================================
D3DXVECTOR3 CLife::GetSize(void)
{
	return m_size;
}

//=============================================================================
//ライフを取得
//=============================================================================
int CLife::GetLife(void)
{
	return m_nValue;
}
