//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: scene2D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/21
//
//============================================

#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//============================================
//インクルードファイル
//============================================
#include "scene.h"

//============================================
//マクロ定義
//============================================
// 頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define NUM_VERTEX (4)
#define NUM_POLYGON (2)


//============================================
//構造体定義
//============================================
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

class CScene2D : public CScene
{
public:

	CScene2D();
	virtual ~CScene2D();

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 ptnSize);//パターンのあるテクスチャ専用
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//テクスチャ関連
	HRESULT Load(LPCSTR strFileName);
	void BindTexture( LPDIRECT3DTEXTURE9 pTexture);
	void ChangeTextureAnime( int nPatternAnim, D3DXVECTOR2 ptnSize, D3DXVECTOR2 ptnDivide); //アニメーション

	//頂点データ関連
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetColor(const D3DXCOLOR &col); //色を変更

	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPCSTR strFileName);


private:

	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	bool m_bLoadTexture;					// テクスチャを読み込んだかどうか

	D3DXVECTOR3			m_pos;				// ポリゴンの位置
	D3DXVECTOR3			m_size;				// ポリゴンのサイズ
};

#endif
