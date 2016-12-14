//============================================
//
// タイトル:	 CL25課題
// プログラム名: player2D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/21
//
//============================================

#ifndef _PLAYER2D_H_
#define _PLAYER2D_H_

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

class CPlayer2D : public CScene2D
{
public:

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_START,
		STATE_DAMAGE,
		STATE_MAX,
	}STATE;

	CPlayer2D();
	virtual ~CPlayer2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	bool Hit(void);


private:
	
	bool m_bUse;
	STATE m_state;		//状態
	int m_nCntState;	//状態のカウンター
};

#endif
