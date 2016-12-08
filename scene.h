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
#define MAX_SCENE	(100)

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

	void SetObjType(OBJTYPE type);
	OBJTYPE GetObjType(void);
	
	static CScene *GetScene(int nIdxScene);

protected:
	
	void Release(void);

private:

	static CScene *m_apScene[MAX_SCENE];
	static int m_nNumScene;
	int m_nID;
	OBJTYPE m_objType;
};

#endif