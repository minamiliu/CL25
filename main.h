//=============================================================================
//
// メイン処理 [main.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// ヘッダファイル
//*****************************************************************************
#include "windows.h"
#include "d3dx9.h"
#include "dinput.h"
#include "xaudio2.h"		// XAudio2関連のヘッダー

//*****************************************************************************
// ライブラリファイル
// [構成プロパティ]->[リンカー]->[入力]->[追加の依存ファイル]に記述しても可能
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// ウインドウの幅
#define SCREEN_HEIGHT	(720)		// ウインドウの高さ

#define SAFE_RELEASE(ptr)		{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }


//カラー情報
#define WHITE(alpha)							D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,(alpha))
#define RED(alpha)								D3DCOLOR_COLORVALUE(1.0f,0.0f,0.0f,(alpha))
#define GREEN(alpha)							D3DCOLOR_COLORVALUE(0.0f,1.0f,0.0f,(alpha))
#define BLUE(alpha)								D3DCOLOR_COLORVALUE(0.0f,0.0f,1.0f,(alpha))
#define SYAN(alpha)								D3DCOLOR_COLORVALUE(0.0f,1.0f,1.0f,(alpha))
#define MASENTA(alpha)							D3DCOLOR_COLORVALUE(1.0f,0.0f,1.0f,(alpha))
#define YELLOW(alpha)							D3DCOLOR_COLORVALUE(1.0f,1.0f,0.0f,(alpha))
#define D3DX_PINK(alpha)						D3DCOLOR_COLORVALUE(1.0f,0.5f,0.5f,(alpha))
#define PURPLE(alpha)							D3DCOLOR_COLORVALUE(0.5f,0.5f,1.0f,(alpha))
#define LIME(alpha)								D3DCOLOR_COLORVALUE(0.5f,1.0f,0.5f,(alpha))
#define ORANGE(alpha)							D3DCOLOR_COLORVALUE(1.0f,0.5f,0.0f,(alpha))
#define SUN(alpha)								D3DCOLOR_COLORVALUE(0.0f,1.0f,0.5f,(alpha))
#define SKY(alpha)								D3DCOLOR_COLORVALUE(0.0f,0.5f,1.0f,(alpha))
#define BIAGE(alpha)							D3DCOLOR_COLORVALUE(1.0f,0.75f,0.5f,(alpha))
#define BLACK(alpha)							D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,(alpha))

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#ifdef _DEBUG
int GetFPS(void);
#endif


#endif