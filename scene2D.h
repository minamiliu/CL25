//============================================
//
// タイトル:	 CL25課題
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

//============================================
//構造体定義
//============================================

class CScene2D : public CScene
{
public:

	CScene2D();
	virtual ~CScene2D();

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	HRESULT Load(LPCSTR strFileName);
	void BindTexture( LPDIRECT3DTEXTURE9 pTexture);

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);

	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


private:

	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	bool m_bLoadTexture;					// テクスチャを読み込んだかどうか

	D3DXVECTOR3			m_pos;				// ポリゴンの位置
	D3DXVECTOR3			m_size;				// ポリゴンのサイズ
};

#endif
