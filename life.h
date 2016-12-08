//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: life.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/08
//
//============================================

#ifndef _LIFE_H_
#define _LIFE_H_

//============================================
//インクルードファイル
//============================================
#include "scene.h"

//============================================
//マクロ定義
//============================================

//============================================
//前方宣言
//============================================
class CHeart;

//============================================
//構造体定義
//============================================

class CLife : public CScene
{
public:

	CLife();
	virtual ~CLife();
	virtual HRESULT Init(void);
	virtual HRESULT Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, const D3DXCOLOR &col);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int maxKeta, const D3DXCOLOR &col);
	HRESULT Load(void);
	void Unload(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	int GetLife(void);

	void MinusLife(void); //得点を上げる

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	CHeart **m_ppPolygon;	//総桁を管理するポインター
	int m_nMaxKeta;			//桁数
	int m_nValue;			//スコア
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

#endif
