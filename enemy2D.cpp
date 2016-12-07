//============================================
//
// タイトル:	 CL25課題
// プログラム名: enemy.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/18
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "enemy2D.h"

//============================================
// マクロ定義
//============================================
#define TEXTURE_ENEMY000 "data/TEXTURE/enemy000.png"
#define TEXTURE_ENEMY001 "data/TEXTURE/enemy001.png"
#define TEXTURE_ENEMY002 "data/TEXTURE/enemy002.png"
#define TEXTURE_ENEMY003 "data/TEXTURE/enemy003.png"

#define	TEX_PATTERN_DIVIDE_X		(2)								// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// アニメーションパターンのテクスチャ内での分割数(Ｙ方向)
#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)		// １パターンのテクスチャサイズ(Ｘ方向)(1.0f/X方向分割数)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)		// １パターンのテクスチャサイズ(Ｙ方向)(1.0f/Y方向分割数)

#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X*TEX_PATTERN_DIVIDE_Y)	// アニメーションのパターン数(X方向分割数×Y方向分割数)
#define	TIME_CHANGE_PATTERN			(30)								// アニメーションの切り替わるタイミング(フレーム数)

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CEnemy2D::m_pTexture[CEnemy2D::TYPE_MAX] = {};

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CEnemy2D::CEnemy2D()
{
	m_move = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_fCntAngle = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CEnemy2D::~CEnemy2D()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CEnemy2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	CScene2D::Init(pos, size, D3DXVECTOR2(TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
	SetObjType( CScene::OBJTYPE_ENEMY);

	m_type = type;
	m_move = D3DXVECTOR3( 5.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;	// ポリゴンのアニメーションカウンター
	m_nPatternAnim = 0;	// ポリゴンのアニメーションパターンNo.

	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CEnemy2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CEnemy2D::Update(void)
{
	CScene2D::Update();

	D3DXVECTOR3 size = CScene2D::GetSize();
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	//揺れる処理
	pos.y += sinf(m_fCntAngle) * 1.0f;
	m_fCntAngle += 0.1f;
	m_fCntAngle = ( m_fCntAngle >= D3DX_PI * 2) ? 0.0f : m_fCntAngle; 

	//壁に跳ね返す
	//if( pos.x < size.x/2 || pos.x > SCREEN_WIDTH - size.x/2)
	//{
	//	m_move *= -1;
	//}

	//pos += m_move;

	m_nCounterAnim++;
	if( m_nCounterAnim >= TIME_CHANGE_PATTERN )
	{

		// パターンの切り替え
		m_nPatternAnim++;
		if( m_nPatternAnim >= NUM_ANIM_PATTERN){

			m_nPatternAnim = 0;
		}
		
		{// テクスチャ座標を設定
			ChangeTextureAnime( 
				m_nPatternAnim, 
				D3DXVECTOR2(TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y), 
				D3DXVECTOR2(TEX_PATTERN_DIVIDE_X, TEX_PATTERN_DIVIDE_Y));

			//m_nCounterAnimのリセット
			m_nCounterAnim = 0;
		}
	}

	//弾の移動更新
	CScene2D::SetPosition(pos);
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CEnemy2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CEnemy2D *CEnemy2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	CEnemy2D *pBullet2D;
	pBullet2D = new CEnemy2D;
	pBullet2D->Init(pos, size, type);

	//テクスチャの割り当て
	pBullet2D->BindTexture(m_pTexture[type]);
	
	return pBullet2D;
}

//=============================================================================
//
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
		}

		if( m_pTexture[cntType] == NULL)
		{
			LPDIRECT3DDEVICE9 pDevice;
			pDevice = CManager::GetRenderer()->GetDevice();

			// テクスチャの読み込み
			D3DXCreateTextureFromFile( pDevice, strFileName, &m_pTexture[cntType]);
		}	
	}


	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CEnemy2D::Unload(void)
{
	//テクスチャの破棄
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
//
//=============================================================================
CEnemy2D::TYPE CEnemy2D::GetType(void)
{
	return m_type;
}

