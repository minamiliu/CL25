//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: manager.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/01
//
//============================================

#ifndef _MANAGER_H_
#define _MANAGER_H_

//============================================
//�}�N����`
//============================================

//============================================
//�O���錾
//============================================
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CSound;
class CNumber;

//============================================
//�\���̒�`
//============================================

class CManager
{
public:

	CManager();
	virtual ~CManager();
	
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	//�����_���[
	static CRenderer *GetRenderer(void);

	//���͏���
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputMouse *GetInputMouse(void);

	//�T�E���h
	static CSound *GetSound(void);

	//�X�R�A
	static CNumber *GetScore(void);

private:
	//�����_���[
	static CRenderer *m_pRenderer;

	//���͏���
	static CInputKeyboard *m_pInputKeyboard;
	static CInputMouse *m_pInputMouse;

	//�T�E���h
	static CSound *m_pSound;

	//�X�R�A
	static CNumber *m_pScore;
};

#endif
