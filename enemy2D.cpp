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

HRESULT CEnemy2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	SetObjType( CScene::OBJTYPE_ENEMY);

	m_move = D3DXVECTOR3( 5.0f, 0.0f, 0.0f);


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
	if(pos.x < size.x/2 || pos.x > SCREEN_WIDTH - size.x/2)
	{
		m_move.x *= -1;
	}
	
	pos += m_move;

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
	pBullet2D->Init(pos, size);

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

