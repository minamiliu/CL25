//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: scene2D.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/19
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//============================================
// マクロ定義
//============================================
#define NUM_VERTEX (4)
#define NUM_POLYGON (2)

//=============================================================================
// 構造体定義
//=============================================================================


//=============================================================================
//コンストラクタ
//=============================================================================
CScene2D::CScene2D()
{
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);			// ポリゴンの位置
	m_bLoadTexture = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{
	
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScene2D::Init(void)
{
	return S_OK;
}

HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ポリゴンの情報を設置
	m_pos = pos;
	m_size = size;
	m_bLoadTexture = false;

	// 頂点バッファの生成
	if(FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	//頂点データのバッファサイズ 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D,			//頂点フォーマット
		D3DPOOL_MANAGED, 
		&m_pVtxBuff,		//頂点バッファインターフェースのポインタ
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	// ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x/2), m_pos.y - (m_size.y/2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x/2), m_pos.y - (m_size.y/2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x/2), m_pos.y + (m_size.y/2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x/2), m_pos.y + (m_size.y/2), 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//color
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	//テクスチャ座標指定
	pVtx[0].tex = D3DXVECTOR2(0.0F, 0.0F);
	pVtx[1].tex = D3DXVECTOR2(1.0F, 0.0F);
	pVtx[2].tex = D3DXVECTOR2(0.0F, 1.0F);
	pVtx[3].tex = D3DXVECTOR2(1.0F, 1.0F);

	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 ptnSize)
{
	Init(pos, size);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	//テクスチャ座標指定
	pVtx[0].tex = D3DXVECTOR2( ptnSize.x * 0.0f, ptnSize.y * 0.0f);
	pVtx[1].tex = D3DXVECTOR2( ptnSize.x * 1.0f, ptnSize.y * 0.0f);
	pVtx[2].tex = D3DXVECTOR2( ptnSize.x * 0.0f, ptnSize.y * 1.0f);
	pVtx[3].tex = D3DXVECTOR2( ptnSize.x * 1.0f, ptnSize.y * 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;
}


//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if(m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// テクスチャの破棄
	if(m_pTexture != NULL && m_bLoadTexture == true)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//オブジェクトの破棄
	Release();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,						//ロードする最初の頂点インデックス
		NUM_POLYGON				//ポリゴンの数
	);
}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPCSTR strFileName)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;
	pScene2D->Init(pos, size);

	//テクスチャの読み込み
	pScene2D->Load( strFileName);

	return pScene2D;
}

//=============================================================================
// ポリゴンの座標設置
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	// ポリゴンの位置を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x/2), m_pos.y - (m_size.y/2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x/2), m_pos.y - (m_size.y/2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x/2), m_pos.y + (m_size.y/2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x/2), m_pos.y + (m_size.y/2), 0.0f);

	m_pVtxBuff->Unlock();
}

//=============================================================================
// ポリゴンの座標取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// ポリゴンのテクスチャを読み込む
//=============================================================================
HRESULT CScene2D::Load(LPCSTR strFileName)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice, strFileName, &m_pTexture);

		// テクスチャの読み込みフラグ
		m_bLoadTexture = true;
	}

	return S_OK;
}

//=============================================================================
// ポリゴンのテクスチャを割り当てる
//=============================================================================
void CScene2D::BindTexture( LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//アニメのパターンを変える
//=============================================================================
void CScene2D::ChangeTextureAnime( int nPatternAnim, D3DXVECTOR2 ptnSize, D3DXVECTOR2 ptnDivide)
{
	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;
	float fPosXLeft, fPosXRight;
	float fPosYUp, fPosYDown;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	fPosXLeft	= ptnSize.x * (nPatternAnim % (int)ptnDivide.x);
	fPosXRight	= ptnSize.x * (nPatternAnim % (int)ptnDivide.x + 1);
	fPosYUp		= ptnSize.y * (nPatternAnim / (int)ptnDivide.x);
	fPosYDown	= ptnSize.y * (nPatternAnim / (int)ptnDivide.x + 1);


	pVtx[0].tex = D3DXVECTOR2( fPosXLeft, fPosYUp );
	pVtx[1].tex = D3DXVECTOR2( fPosXRight, fPosYUp );
	pVtx[2].tex = D3DXVECTOR2( fPosXLeft, fPosYDown );
	pVtx[3].tex = D3DXVECTOR2( fPosXRight, fPosYDown );

	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//ポリゴンのサイズを取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetSize(void)
{
	return m_size;
}

//=============================================================================
//色を変更
//=============================================================================
void CScene2D::SetColor(const D3DXCOLOR &col)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	//color
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();
}