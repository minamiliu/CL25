//============================================
//
// タイトル:	 CL25課題
// プログラム名: effect.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/16
//
//============================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

//============================================
//インクルードファイル
//============================================
#include "scene2D.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CEffect : public CScene2D
{
public:

	CEffect();
	virtual ~CEffect();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col);
	static HRESULT Load(void);
	static void Unload(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXCOLOR m_col;
};

#endif
