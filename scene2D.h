//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: scene2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================
//�G�N���X
class CScene2D : public CScene
{
public:

	CScene2D();
	virtual ~CScene2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScene2D *Create(void);

private:

	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
};

#endif