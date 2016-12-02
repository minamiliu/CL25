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
#include "score.h"
#include "number.h"


//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/number000.png"

#define	TEX_PATTERN_DIVIDE_X		(10)								// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
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
CScore::CScore()
{
	m_ppPolygon = NULL;
	m_pTexture = NULL;
}

//=============================================================================
//デストラクタ
//=============================================================================
CScore::~CScore()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScore::Init(void)
{
	return S_OK;
}
HRESULT CScore::Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, const D3DXCOLOR &col)
{
	//初期値を設定
	m_nMaxKeta = maxKeta;
	m_nValue = 0;
	m_pos = numberPos;
	m_size = numberSize;

	//Numberポインター配列の生成
	m_ppPolygon = new CNumber*[maxKeta];

	//スタート位置(右)と桁サイズの計算
	D3DXVECTOR3 rightPos = numberPos;
	D3DXVECTOR3 ketaSize = numberSize;
	ketaSize.x /= maxKeta;
	rightPos.x = numberPos.x + ketaSize.x * (maxKeta - 1) / 2.0f;
	
	//桁分のNumberの生成
	D3DXVECTOR3 tmpPos = rightPos;
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		m_ppPolygon[cntKeta] = CNumber::Create( tmpPos , ketaSize, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
		tmpPos.x -= ketaSize.x;
	}

	//色を設定
	SetColor( col);

	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScore::Uninit(void)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		//数字桁の破棄
		m_ppPolygon[cntKeta]->Uninit();
	}

	delete[] m_ppPolygon;
	m_ppPolygon = NULL;

	//テクスチャの破棄
	this->Unload();
	
	//オブジェクトの破棄
	Release();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScore::Update(void)
{
	
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScore::Draw(void)
{
	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		m_ppPolygon[nKeta]->Draw();
	}
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int maxKeta, const D3DXCOLOR &col)
{
	CScore *pScore;
	pScore = new CScore;
	pScore->Init(pos, size, maxKeta, col);

	//テクスチャの読み込み
	pScore->Load();

	//桁分のテクスチャの割り当て
	pScore->BindAllTexture();
	
	return pScore;
}

//=============================================================================
//
//=============================================================================
HRESULT CScore::Load(void)
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
void CScore::Unload(void)
{
	//テクスチャの破棄
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//数字をそのまま表示する
//=============================================================================
void CScore::SetScore(int score)
{
	int number;

	//範囲チェック
	int maxScore = powf( 10.0f, m_nMaxKeta) -1;
	if(score >  maxScore) score = maxScore;
	else if(score < 0) score = 0;

	//値を更新
	m_nValue = score;

	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		//一番右の数字を取る
		number = int(score % (int)powf( 10.0f, float(nKeta+1)) / powf( 10.0f, float(nKeta)));

		//テクスチャをずらす
		m_ppPolygon[nKeta]->ChangeTextureAnime( number, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y), D3DXVECTOR2( TEX_PATTERN_DIVIDE_X, TEX_PATTERN_DIVIDE_Y));
	}
}

//=============================================================================
//桁分のテクスチャの割り当て
//=============================================================================
void CScore::BindAllTexture(void)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		//テクスチャの割り当て
		m_ppPolygon[cntKeta]->BindTexture( m_pTexture);
	}
}

//=============================================================================
//全桁の色を一気に変更
//=============================================================================
void CScore::SetColor(const D3DXCOLOR &col)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		m_ppPolygon[cntKeta]->SetColor( col);
	}
}

//=============================================================================
//得点を上げる
//=============================================================================
void CScore::AddScore(int score)
{
	m_nValue += score;
	SetScore( m_nValue);
}
//=============================================================================
//座標を取得
//=============================================================================
D3DXVECTOR3 CScore::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
//サイズを取得
//=============================================================================
D3DXVECTOR3 CScore::GetSize(void)
{
	return m_size;
}
