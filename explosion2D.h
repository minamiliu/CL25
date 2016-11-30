//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: explosion2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/16
//
//============================================

#ifndef _EXPLOSION2D_H_
#define _EXPLOSION2D_H_

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

class CExplosion2D : public CScene2D
{
public:

	CExplosion2D();
	virtual ~CExplosion2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXCOLOR &col);
	static HRESULT Load(void);
	static void Unload(void);

private:
	//�֐�


	//�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;

	//�A�j���[�V����
	int m_nCounterAnim;	// �|���S���̃A�j���[�V�����J�E���^�[
	int	m_nPatternAnim;	// �|���S���̃A�j���[�V�����p�^�[��No.
};

#endif
