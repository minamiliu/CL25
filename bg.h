//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: bg.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/07
//
//============================================

#ifndef _BG_H_
#define _BG_H_

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
class CBg : public CScene2D
{
public:

	CBg();
	virtual ~CBg();

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPCSTR strFileName, float speed);
protected:
	void SetScroll(D3DXVECTOR2 scroll);

private:
	D3DXVECTOR2 m_scroll;
	float m_fSpeed;
};

#endif
