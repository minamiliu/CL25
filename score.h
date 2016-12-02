//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: score.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/30
//
//============================================

#ifndef _SCORE_H_
#define _SCORE_H_

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
class CNumber;

//============================================
//構造体定義
//============================================

class CScore : public CScene
{
public:

	CScore();
	virtual ~CScore();
	virtual HRESULT Init(void);
	virtual HRESULT Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, const D3DXCOLOR &col);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int maxKeta, const D3DXCOLOR &col);
	HRESULT Load(void);
	void Unload(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	void SetScore(int score); //数字をそのまま表示する
	void SetColor(const D3DXCOLOR &col); //全桁の色を一気に変更
	void AddScore(int score); //得点を上げる

protected:
	void BindAllTexture(void);

private:
	//関数
	void SetKetaTexture(const int keta, const int texNo);

	//変数
	LPDIRECT3DTEXTURE9 m_pTexture;
	CNumber **m_ppPolygon;	//総桁を管理するポインター
	int m_nMaxKeta;			//桁数
	int m_nValue;			//スコア
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

#endif
