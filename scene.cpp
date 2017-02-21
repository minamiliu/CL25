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
CScene *CScene::m_pTop = NULL; //�����̑O�̃I�u�W�F�N�g�̃|�C���^�[
CScene *CScene::m_pCur = NULL; //�����̌�̃I�u�W�F�N�g�̃|�C���^�[

//============================================
// �}�N����`
//============================================


//=============================================================================
// CScene�R���X�g���N�^
//=============================================================================
CScene::CScene()
{
	// �I�u�W�F�N�g�����X�g�ɓo�^
	LinkList();

	//���S�t���O�̏�����
	m_bDelFlg = false;
}

//=============================================================================
// CScene�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	CScene *pScene = m_pTop;
	while(pScene != NULL)
	{
		CScene *pSceneNext = pScene->m_pNext;
		pScene->Update();
		pScene = pSceneNext;
	}
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	CScene *pScene = m_pTop;
	while(pScene != NULL)
	{
		CScene *pSceneNext = pScene->m_pNext;
		pScene->Draw();
		pScene = pSceneNext;
	}
}

//=============================================================================
// �I�u�W�F�N�g��S�Ĕj��
//=============================================================================
void CScene::ReleaseAll(void)
{
	CScene *pScene = m_pTop;
	while(pScene != NULL)
	{
		CScene *pSceneNext = pScene->m_pNext;
		pScene->Uninit();
		pScene = pSceneNext;
	}
	m_pTop = NULL;
	m_pCur = NULL;
}

//=============================================================================
// �I�u�W�F�N�g��j��
//=============================================================================
void CScene::Release(void)
{
	// �I�u�W�F�N�g�����X�g����폜
	UnlinkList();

	// ������j��
	delete this;
}

//=============================================================================
// �I�u�W�F�N�g�����X�g�ɓo�^
//=============================================================================
void CScene::LinkList(void)
{
	m_pPrev = NULL;
	m_pNext = NULL;

	if(m_pTop == NULL)
	{
		m_pTop = this;
	}

	if( m_pCur == NULL)
	{
		m_pCur = this;
	}
	else
	{
		m_pCur->m_pNext = this;
		this->m_pPrev = m_pCur;
		m_pCur = this;
	}
}

//=============================================================================
// �I�u�W�F�N�g�����X�g����폜
//=============================================================================
void CScene::UnlinkList(void)
{
	// �I�u�W�F�N�g�����X�g����폜
	if(this->m_pPrev != NULL)
	{
		CScene *pScenePrev = this->m_pPrev;
		pScenePrev->m_pNext = this->m_pNext;
	}


	if(this->m_pNext != NULL)
	{
		CScene *pSceneNext = this->m_pNext;
		pSceneNext->m_pPrev = this->m_pPrev;
	}

	if(m_pCur == this)
	{
		m_pCur = this->m_pPrev;
	}

	if(m_pTop == this)
	{
		m_pTop = NULL;
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
//���X�g�̐擪���擾
//============================================
CScene *CScene::GetTop(void)
{
	return m_pTop;
}

//============================================
//���X�g�̍Ō�����擾
//============================================
CScene *CScene::GetCur(void)
{
	return m_pCur;
}

//============================================
//���̃I�u�W�F�N�g�̃|�C���^���擾
//============================================
CScene *CScene::GetNext(void)
{
	return this->m_pNext;
}

//============================================
//�O�̃I�u�W�F�N�g�̃|�C���^���擾
//============================================
CScene *CScene::GetPrev(void)
{
	return this->m_pPrev;
}

//============================================
//���S�t���O�𗧂Ă�
//============================================
void CScene::SetDelFlg(void)
{
	m_bDelFlg = true;
}

//============================================
//���S�t���O���������I�u�W�F�N�g���폜����
//============================================
void CScene::DeleteAllFlg(void)
{
	CScene *pScene = m_pTop;
	while(pScene != NULL)
	{
		CScene *pSceneNext = pScene->m_pNext;
		if(pScene->m_bDelFlg == true)
		{
			pScene->Uninit();
		}
		pScene = pSceneNext;
	}
}