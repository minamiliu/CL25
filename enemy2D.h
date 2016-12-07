//============================================
//
// タイトル:	 CL25課題
// プログラム名: enemy.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/18
//
//============================================

#ifndef _ENEMY2D_H_
#define _ENEMY2D_H_

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

class CEnemy2D : public CScene2D
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_000,
		TYPE_001,
		TYPE_002,
		TYPE_003,
		TYPE_MAX,
	}TYPE;

	CEnemy2D();
	virtual ~CEnemy2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	TYPE GetType(void);

	static CEnemy2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
	D3DXVECTOR3 m_move;
	float m_fCntAngle;
	TYPE m_type;

	//アニメーション
	int m_nCounterAnim;	// ポリゴンのアニメーションカウンター
	int	m_nPatternAnim;	// ポリゴンのアニメーションパターンNo.
};

#endif
