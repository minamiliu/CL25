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
#include "effect.h"

//============================================
// マクロ定義
//============================================
#define TEXTURENAME "data/TEXTURE/bullet000.png"
#define BULLET_DAMAGE	(1)
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
	m_effect = NULL;
}

//=============================================================================
//デストラクタ
//=============================================================================
CBullet2D::~CBullet2D()
{
	
}


//=============================================================================
// 弾の初期化処理
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
// 弾の終了処理
//=============================================================================
void CBullet2D::Uninit(void)
{
	//弾の破棄
	CScene2D::Uninit();
}


//=============================================================================
// 弾の更新処理
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
		//リストの先頭を取得
		CScene *pScene = CScene::GetTop();

		while( pScene != NULL)
		{
			CScene::OBJTYPE type;
			type = pScene->GetObjType();

			if( type == CScene::OBJTYPE_ENEMY)
			{
				//座標
				D3DXVECTOR3 posEnemy, posBullet;
				posEnemy = pScene->GetPosition();
				posBullet = this->GetPosition();

				//サイズ
				D3DXVECTOR3 sizeEnemy, sizeBullet;
				sizeEnemy = pScene->GetSize();
				sizeBullet = this->GetSize();

				//当たり判定
				if(	   posBullet.x > posEnemy.x - sizeEnemy.x/2.0f 
					&& posBullet.x < posEnemy.x + sizeEnemy.x/2.0f 
					&& posBullet.y > posEnemy.y - sizeEnemy.y/2.0f  
					&& posBullet.y < posEnemy.y + sizeEnemy.y/2.0f 
					)
				{
					((CEnemy2D*)pScene)->Hit( BULLET_DAMAGE);

					//弾(自分)の破棄
					//this->Uninit();
					this->SetDelFlg();

					//スコア
					CManager::GetScore()->AddScore( 100);
					
					return;
				}
			}

			//次のオブジェクトに
			pScene = pScene->GetNext();
		}	
	}

	//サイズを取得
	D3DXVECTOR3 size = this->GetSize();
	
	if(this->GetObjType() == CScene::OBJTYPE_BULLET_P)
	{
		//エフェクト更新
		CEffect::Create( pos, size*1.5, LIME(1.0f));
	}
	else if(this->GetObjType() == CScene::OBJTYPE_BULLET_E)
	{
		//エフェクト更新
		CEffect::Create( pos, size*1.5, MASENTA(1.0f));	
	}
}

//=============================================================================
// 弾の描画処理
//=============================================================================
void CBullet2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 弾の生成処理
//=============================================================================
CBullet2D *CBullet2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, const D3DXCOLOR &col, CScene::OBJTYPE obj)
{
	CBullet2D *pBullet2D;
	pBullet2D = new CBullet2D;
	pBullet2D->Init(pos, size, move, col, obj);

	//テクスチャの割り当て
	pBullet2D->BindTexture(m_pTexture);
	
	return pBullet2D;
}

//=============================================================================
//テクスチャのロード
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
//テクスチャのアンロード
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

