//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: scene.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/19
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "scene.h"

//============================================
//�ÓI�����o�ϐ��̏�����
//============================================
CScene *CScene::m_apScene[MAX_SCENE] = {};
int CScene::m_nNumScene = 0;

//============================================
// �}�N����`
//============================================


//============================================
// �\���̒�`
//============================================


//============================================
//�R���X�g���N�^
//============================================
CScene::CScene()
{
	for(int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if(m_apScene[nCntScene] == NULL)
		{
			m_apScene[nCntScene] = this;
			m_nID = nCntScene;
			m_nNumScene++;
			break;
		}
	}
}

//============================================
//�f�X�g���N�^
//============================================
CScene::~CScene()
{
	
}

//============================================
//�S���̃V�[���X�V
//============================================
void CScene::UpdateAll(void)
{
	for(int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->Update();
		}
	}	
}

//============================================
//�S���̃V�[���`��
//============================================
void CScene::DrawAll(void)
{
	for(int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->Draw();
		}
	}	
}

//============================================
//�S���̃V�[���J��
//============================================
void CScene::ReleaseAll(void)
{
	for(int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->Uninit();
		}
	}	
}

//============================================
//����J��
//============================================
void CScene::Release(void)
{
	if(m_apScene[m_nID] != NULL)
	{
		int nID = m_nID;
		delete m_apScene[nID];
		m_apScene[nID] = NULL;
		m_nNumScene--;
	}	
}

//============================================
//�I�u�W�F�N�g��ݒ�
//============================================
void CScene::SetObjType(OBJTYPE type)
{
	m_objType = type;
}

//============================================
//�I�u�W�F�N�g���擾
//============================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//============================================
//�I�u�W�F�N�g��ID���擾
//============================================
CScene *CScene::GetScene(int nIdxScene)
{
	return m_apScene[nIdxScene];
}