//============================================
//
// タイトル:	 CL25課題
// プログラム名: bullet.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/11
//
//============================================

#ifndef _BULLET2D_H_
#define _BULLET2D_H_

//============================================
//インクルードファイル
//============================================
#include "scene2D.h"

//============================================
//マクロ定義
//============================================

//============================================
//前方宣言
//============================================
class CEffect;

//============================================
//構造体定義
//============================================

class CBullet2D : public CScene2D
{
public:

	CBullet2D();
	virtual ~CBullet2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, const D3DXCOLOR &col, CScene::OBJTYPE obj);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, const D3DXCOLOR &col, CScene::OBJTYPE obj);
	static HRESULT Load(void);
	static void Unload(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_move;
	int m_nCntFrame;
	CEffect *m_effect;
};

#endif
