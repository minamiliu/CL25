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
#include "bullet2D.h"
#include "explosion2D.h"

//============================================
// マクロ定義
//============================================
#define TEXTURE_ENEMY000 "data/TEXTURE/enemy000.png"
#define TEXTURE_ENEMY001 "data/TEXTURE/enemy001.png"
#define TEXTURE_ENEMY002 "data/TEXTURE/enemy002.png"
#define TEXTURE_ENEMY003 "data/TEXTURE/enemy003.png"
#define TEXTURE_ENEMY004 "data/TEXTURE/enemy004.png"

#define	TEX_PATTERN_DIVIDE_X		(2)								// アニメーションパターンのテクスチャ内での分割数(Ｘ方向)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// アニメーションパターンのテクスチャ内での分割数(Ｙ方向)
#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)		// １パターンのテクスチャサイズ(Ｘ方向)(1.0f/X方向分割数)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)		// １パターンのテクスチャサイズ(Ｙ方向)(1.0f/Y方向分割数)
#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X*TEX_PATTERN_DIVIDE_Y)	// アニメーションのパターン数(X方向分割数×Y方向分割数)
#define	TIME_CHANGE_PATTERN			(30)								// アニメーションの切り替わるタイミング(フレーム数)

#define ENEMY_SPEED_X	(3.0f)
#define ENEMY_START_POSX	(100.0f)
#define MAX_LINE_ENEMY	(10)
#define FRAME_DAMAGE	(20)

//============================================
// 静的メンバー変数の初期化
//============================================
LPDIRECT3DTEXTURE9 CEnemy2D::m_pTexture[CEnemy2D::TYPE_MAX] = {};
D3DXVECTOR3 CEnemy2D::m_move = D3DXVECTOR3( ENEMY_SPEED_X, 0.0f, 0.0f);

float CEnemy2D::m_fPosXRef =  0.0f;
bool CEnemy2D::bHitWall = false;


//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CEnemy2D::CEnemy2D()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CEnemy2D::~CEnemy2D()
{
	
}


//=============================================================================
// 敵の初期化処理
//=============================================================================

HRESULT CEnemy2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, int nLife)
{
	CScene2D::Init(pos, size, D3DXVECTOR2(TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
	SetObjType( CScene::OBJTYPE_ENEMY);

	
	m_fPosXDiff = pos.x - m_fPosXRef; //座標ずれ記録

	m_type = type;
	m_nLife = nLife;				//ライフ
	m_state = STATE_NORMAL;		//状態
	
	m_nCntState = 0;	//状態のカウンター
	m_nCounterAnim = 0;	// 敵のアニメーションカウンター
	m_nPatternAnim = 0;	// 敵のアニメーションパターンNo.
	m_fCntShake = 0;

	return S_OK;
}




//=============================================================================
// 敵の終了処理
//=============================================================================
void CEnemy2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// 敵の更新処理
//=============================================================================
void CEnemy2D::Update(void)
{
	D3DXVECTOR3 size = CScene2D::GetSize();
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	//揺れる処理
	pos.y += sinf(m_fCntShake) * 1.0f;
	m_fCntShake += 0.1f;
	m_fCntShake = ( m_fCntShake >= D3DX_PI * 2) ? 0.0f : m_fCntShake; 

	//移動処理
	pos.x = m_fPosXRef + m_fPosXDiff;

	//左右限界を更新
	if( bHitWall == false)
	{
		if(pos.x < 0.0f + size.x/2 || pos.x > SCREEN_WIDTH - size.x/2)
		{
			bHitWall = true;
		}
	}

	//アニメーション
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

	//弾を出す
	int nRand = rand() % 1000;
	if( nRand < 1)
	{
		CBullet2D::Create( pos, D3DXVECTOR3( 10.0f, 10.0f, 0.0f), D3DXVECTOR3( 0.0f, 5.0f, 0.0f), MASENTA(1.0f), CScene::OBJTYPE_BULLET_E);
	}

	//状態の更新
	switch( m_state)
	{
	case STATE_DAMAGE:
		m_nCntState--;
		if( m_nCntState <= 0)
		{
			m_state = STATE_NORMAL;
			//色を元に戻す
			this->SetColor( WHITE(1.0f));
		}
		break;
	}

	//弾の移動更新
	CScene2D::SetPosition(pos);
}

//=============================================================================
// 敵の描画処理
//=============================================================================
void CEnemy2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 敵の生成処理
//=============================================================================
CEnemy2D *CEnemy2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, int nLife)
{
	CEnemy2D *pEnemy;
	pEnemy = new CEnemy2D;
	pEnemy->Init(pos, size, type, nLife);

	//テクスチャの割り当て
	pEnemy->BindTexture(m_pTexture[type]);
	
	return pEnemy;
}

//=============================================================================
//テクスチャのロード
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

		case TYPE_004:
			strFileName = TEXTURE_ENEMY004;
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
//テクスチャのアンロード
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
//敵の種類を取得
//=============================================================================
CEnemy2D::TYPE CEnemy2D::GetType(void)
{
	return m_type;
}
//=============================================================================
//敵全体の生成(ステージ0)
//=============================================================================
void CEnemy2D::CreateAllEnemy(void)
{
	m_fPosXRef = ENEMY_START_POSX;

	for(int cntEnemy = 0; cntEnemy < MAX_LINE_ENEMY; cntEnemy++)
	{
		CEnemy2D::Create(D3DXVECTOR3( ENEMY_START_POSX + cntEnemy * 100.0f, 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), TYPE_000, 5);
		CEnemy2D::Create(D3DXVECTOR3( ENEMY_START_POSX + cntEnemy * 100.0f, 150.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), TYPE_001, 4);
		CEnemy2D::Create(D3DXVECTOR3( ENEMY_START_POSX + cntEnemy * 100.0f, 200.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), TYPE_002, 3);
		CEnemy2D::Create(D3DXVECTOR3( ENEMY_START_POSX + cntEnemy * 100.0f, 250.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), TYPE_003, 2);
		CEnemy2D::Create(D3DXVECTOR3( ENEMY_START_POSX + cntEnemy * 100.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), TYPE_004, 1);
	}
}
//=============================================================================
//敵全体の基準座標の更新処理
//=============================================================================
void CEnemy2D::UpdateRefPos(void)
{
	//壁に跳ね返す
	if( bHitWall == true)
	{
		m_move *= -1;
		bHitWall = false;
	}

	//座標基準更新
	m_fPosXRef += m_move.x;
}
//=============================================================================
//敵のダメージ処理
//=============================================================================
bool CEnemy2D::Hit(int nDamage)
{
	m_nLife -= nDamage;
	if( m_nLife <= 0)
	{
		D3DXVECTOR3 posEnemy = GetPosition();

		//色付けの爆風の生成
		switch( m_type)
		{
		case TYPE_000:
			CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), RED(1.0f));
			break;

		case TYPE_001:
			CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), WHITE(1.0f));
			break;

		case TYPE_002:
			CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), GRAY(1.0f));
			break;

		case TYPE_003:
			CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), BLUE(1.0f));
			break;

		case TYPE_004:
			CExplosion2D::Create( posEnemy, D3DXVECTOR3(100.0f, 100.0f, 0.0f), GREEN(1.0f));
			break;
		}

		//敵の破棄
		//this->Uninit();
		this->SetDelFlg();

		return true;
	}
	else
	{
		m_state = STATE_DAMAGE;
		m_nCntState = FRAME_DAMAGE;

		//色をダメージ色に変更
		this->SetColor( RED(1.0f));
	}
	return false;
}
