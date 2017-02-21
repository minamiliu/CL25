//============================================
//
// タイトル:	 CL25課題
// プログラム名: scene.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/21
//
//============================================

#ifndef _SCENE_H_
#define _SCENE_H_

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET_P,
		OBJTYPE_BULLET_E,
		OBJTYPE_EXPLOSION,
		OBJTYPE_MAX,
	}OBJTYPE;

	CScene();
	virtual ~CScene();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);

	virtual D3DXVECTOR3 GetPosition(void) = 0;
	virtual D3DXVECTOR3 GetSize(void) = 0;

	void SetObjType(OBJTYPE type);
	OBJTYPE GetObjType(void);
	
	static CScene *GetTop(void);
	static CScene *GetCur(void);

	void LinkList(void);
	void UnlinkList(void);
	CScene *GetNext(void);
	CScene *GetPrev(void);
	
	void SetDelFlg(void);
	static void DeleteAllFlg(void);

protected:
	
	void Release(void);

private:

	static CScene *m_pTop; //自分の前のオブジェクトのポインター
	static CScene *m_pCur; //自分の後のオブジェクトのポインター

	CScene *m_pPrev; //リストの先頭のオブジェクトのポインター
	CScene *m_pNext; //リストの最後尾のオブジェクトのポインター(現在位置)

	OBJTYPE m_objType;
	bool m_bDelFlg;
};

#endif