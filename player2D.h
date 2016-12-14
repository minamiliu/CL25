//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: player2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _PLAYER2D_H_
#define _PLAYER2D_H_

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

class CPlayer2D : public CScene2D
{
public:

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_START,
		STATE_DAMAGE,
		STATE_MAX,
	}STATE;

	CPlayer2D();
	virtual ~CPlayer2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	bool Hit(void);


private:
	
	bool m_bUse;
	STATE m_state;		//���
	int m_nCntState;	//��Ԃ̃J�E���^�[
};

#endif
