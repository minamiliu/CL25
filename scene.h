//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: scene.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _SCENE_H_
#define _SCENE_H_

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
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

	static CScene *m_pTop; //�����̑O�̃I�u�W�F�N�g�̃|�C���^�[
	static CScene *m_pCur; //�����̌�̃I�u�W�F�N�g�̃|�C���^�[

	CScene *m_pPrev; //���X�g�̐擪�̃I�u�W�F�N�g�̃|�C���^�[
	CScene *m_pNext; //���X�g�̍Ō���̃I�u�W�F�N�g�̃|�C���^�[(���݈ʒu)

	OBJTYPE m_objType;
	bool m_bDelFlg;
};

#endif