//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: number.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/25
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

//============================================
//構造体定義
//============================================

class CNumber : public CScene2D
{
public:

	CNumber();
	virtual ~CNumber();

	virtual HRESULT Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, const D3DXCOLOR &col);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int maxKeta, const D3DXCOLOR &col);
	static HRESULT Load(void);
	static void Unload(void);

	void SetNumber(int score); //数字をそのまま表示する
	void SetColor(const D3DXCOLOR &col); //全桁の色を一気に変更
	void AddNumber(int score);

protected:
	void BindAllTexture(void);

private:
	//関数
	void SetKetaTexture(const int keta, const int texNo);

	//変数
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2D **m_ppPolygon;
	int m_nMaxKeta;

	int m_nValue;

};

#endif
