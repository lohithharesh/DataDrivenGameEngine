#define GAME_CPP

#define IN_BATTLE 1
#include "pch.h"
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <string>

#include <vector>
#include <unordered_map>

#include "game.h"
#include "gamedefs.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "openGLStuff.h"



// Declarations
const std::string CGame::mGameTitle="Baba Is You";
CGame* CGame::sInstance=NULL;



BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;						
}

void CGame::init()
{
	//AudioManager::createInstance();
	//AudioManager::getInstance()->init();
}

void CGame::UpdateFrame(DWORD milliseconds)			
{
	//keyProcess();
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();
}


CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
}
void CGame::DestroyGame(void)
{
}