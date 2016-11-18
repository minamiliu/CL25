//============================================
//
// タイトル:	 CL25課題
// プログラム名: scene.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/19
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "scene.h"

//============================================
//静的メンバ変数の初期化
//============================================
CScene *CScene::m_apScene[MAX_SCENE] = {};
int CScene::m_nNumScene = 0;

//============================================
// マクロ定義
//============================================


//============================================
// 構造体定義
//============================================


//============================================
//コンストラクタ
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
//デストラクタ
//============================================
CScene::~CScene()
{
	
}

//============================================
//全部のシーン更新
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
//全部のシーン描画
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
//全部のシーン開放
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
//自我開放
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
//オブジェクトを設定
//============================================
void CScene::SetObjType(OBJTYPE type)
{
	m_objType = type;
}

//============================================
//オブジェクトを取得
//============================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//============================================
//オブジェクトのIDを取得
//============================================
CScene *CScene::GetScene(int nIdxScene)
{
	return m_apScene[nIdxScene];
}