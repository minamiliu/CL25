//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: number.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/21
//
//============================================

#ifndef _NUMBER_H_
#define _NUMBER_H_

//============================================
//インクルードファイル
//============================================
#include "scene2D.h"

//============================================
//マクロ定義
//============================================

class CNumber
{
public:

	CNumber();
	virtual ~CNumber();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 ptnSize);//パターンのあるテクスチャ専用
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//テクスチャ関連
	void BindTexture( LPDIRECT3DTEXTURE9 pTexture);
	void ChangeTextureAnime( int nPatternAnim, D3DXVECTOR2 ptnSize, D3DXVECTOR2 ptnDivide); //アニメーション

	//頂点データ関連
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetColor(const D3DXCOLOR &col); //色を変更

	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 ptnSize);

private:

	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	bool m_bLoadTexture;					// テクスチャを読み込んだかどうか

	D3DXVECTOR3			m_pos;				// ポリゴンの位置
	D3DXVECTOR3			m_size;				// ポリゴンのサイズ
};

#endif
