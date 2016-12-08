//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: life.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/08
//
//============================================

#ifndef _LIFE_H_
#define _LIFE_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene.h"

//============================================
//�}�N����`
//============================================

//============================================
//�O���錾
//============================================
class CHeart;

//============================================
//�\���̒�`
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

	void MinusLife(void); //���_���グ��

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	CHeart **m_ppPolygon;	//�������Ǘ�����|�C���^�[
	int m_nMaxKeta;			//����
	int m_nValue;			//�X�R�A
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

#endif
