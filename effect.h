//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: effect.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/16
//
//============================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene2D.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CEffect : public CScene2D
{
public:

	CEffect();
	virtual ~CEffect();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col);
	static HRESULT Load(void);
	static void Unload(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXCOLOR m_col;
};

#endif
