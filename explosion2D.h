//============================================
//
// タイトル:	 CL25課題
// プログラム名: explosion2D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/16
//
//============================================

#ifndef _EXPLOSION2D_H_
#define _EXPLOSION2D_H_

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

class CExplosion2D : public CScene2D
{
public:

	CExplosion2D();
	virtual ~CExplosion2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col);
	static HRESULT Load(void);
	static void Unload(void);

private:
	//関数


	//変数
	static LPDIRECT3DTEXTURE9 m_pTexture;

	//アニメーション
	int m_nCounterAnim;	// ポリゴンのアニメーションカウンター
	int	m_nPatternAnim;	// ポリゴンのアニメーションパターンNo.
};

#endif
