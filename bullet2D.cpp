//============================================
//
// タイトル:	 CL25課題
// プログラム名: bullet2D.cpp
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
#include "bullet2D.h"
#include "explosion2D.h"
#include "score.h"
#include "enemy2D.h"

//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/bullet000.png"

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CBullet2D::m_pTexture = NULL;

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CBullet2D::CBullet2D()
{
	m_move = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
}

//=============================================================================
//デストラクタ
//=============================================================================
CBullet2D::~CBullet2D()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================

HRESULT CBullet2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, const D3DXCOLOR &col, CScene::OBJTYPE obj)
{
	CScene2D::Init(pos, size);
	SetObjType( obj);
	SetColor(col);

	m_move = move;
	m_nCntFrame = 0;
	
	return S_OK;
}




//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CBullet2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CBullet2D::Update(void)
{

	//弾の移動更新
	D3DXVECTOR3 pos = CScene2D::GetPosition();
	pos += m_move;
	CScene2D::SetPosition(pos);

	//弾が消える処理
	m_nCntFrame++;
	if( m_nCntFrame > 120)
	{
		CExplosion2D::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f), WHITE(1.0f));
		this->Uninit();
		return;
	}

	//敵との当たり判定
	if(this->GetObjType() == CScene::OBJTYPE_BULLET_P)
	{
		for( int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene *pScene;
			pScene = CScene::GetScene( nCntScene);
		
			if( pScene != NULL)
			{
				CScene::OBJTYPE type;
				type = pScene->GetObjType();

				if( type == CScene::OBJTYPE_ENEMY)
				{
					D3DXVECTOR3 posEnemy, posBullet;
					posEnemy = pScene->GetPosition();
					posBullet = this->GetPosition();

					if( sqrt( (posEnemy.x - posBullet.x)*(posEnemy.x - posBullet.x) + (posEnemy.y - posBullet.y)*(posEnemy.y - posBullet.y)  ) < 50.0f)
					{
						//爆風の色付け
						switch( ((CEnemy2D*)pScene)->GetType())
						{
						case CEnemy2D::TYPE_000:
							CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), RED(1.0f));
							break;

						case CEnemy2D::TYPE_001:
							CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), WHITE(1.0f));
							break;

						case CEnemy2D::TYPE_002:
							CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), GRAY(1.0f));
							break;

						case CEnemy2D::TYPE_003:
							CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), BLUE(1.0f));
							break;

						case CEnemy2D::TYPE_004:
							CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), GREEN(1.0f));
							break;
						}

						//敵の破棄
 						pScene->Uninit();

						//弾(自分)の破棄
						this->Uninit();

						//スコア
						CManager::GetScore()->AddScore( 100);
					
						return;
					}
				}
			}
		}	
	}

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CBullet2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CBullet2D *CBullet2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, const D3DXCOLOR &col, CScene::OBJTYPE obj)
{
	CBullet2D *pBullet2D;
	pBullet2D = new CBullet2D;
	pBullet2D->Init(pos, size, move, col, obj);

	//テクスチャの読み込み
	pBullet2D->Load();

	//テクスチャの割り当て
	pBullet2D->BindTexture(m_pTexture);
	
	return pBullet2D;
}

//=============================================================================
//
//=============================================================================
HRESULT CBullet2D::Load(void)
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
void CBullet2D::Unload(void)
{
	//テクスチャの破棄
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

