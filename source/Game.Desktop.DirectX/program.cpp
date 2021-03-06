// Game.Desktop.DirectX.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include "SList.h"
#include "World.h"
#include "ScopeParseHelper.h"
#include "Furniture.h"
#include "ActionList.h"
#include "DebugAction.h"
#include "ActionListIf.h"
#include "Rendering.h"
#include "WICTextureLoader.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "AudioManager.h"
#include "Input.h"
#include "InputAction.h"
#include "InputReaction.h"
#include "LevelManager.h"
#include "ResetActionIf.h"
#include "ResetActionElse.h"
#include "RuleCheckEntity.h"

using namespace FieaGameEngine;


LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

void InitD3D(HWND hWnd);     // sets up and initializes Direct3D
void RenderFrame(Sector& s);
void CleanD3D(void);         // closes Direct3D and releases memory

// global declarations
IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
ID3D11Device *dev;                     // the pointer to our Direct3D device interface
ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context

ID3D11RenderTargetView *backbuffer;

Rendering * mRendering;					//noah's renderererer



void InitD3D(HWND hWnd)
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = hWnd;                                // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode

															// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);

	///////////////// Alpha
	ID3D11BlendState* g_pBlendState = NULL;

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	dev->CreateBlendState(&blendDesc, &g_pBlendState);

	devcon->OMSetBlendState(g_pBlendState, 0, 0xffffffff);
	///////////////

	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// use the back buffer address to create the render target
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);

	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 720;
	viewport.Height = 720;

	devcon->RSSetViewports(1, &viewport);
	
	//initialize Rendering
	mRendering = new Rendering(devcon, dev);
}

// this is the function used to render a single frame
void RenderFrame(Sector& s)
{
	// clear the back buffer to a deep blue
	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	devcon->ClearRenderTargetView(backbuffer, color);

	// do 3D rendering on the back buffer here
	mRendering->Update(s);
	// switch the back buffer and the front buffer
	swapchain->Present(0, 0);
}


void CleanD3D()
{
	// close and release all existing COM objects
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
	delete mRendering;
}




void Initialize()
{
	RegisterType(World);
	RegisterType(Entity);
	RegisterType(Sector);
	RegisterType(Furniture);
	RegisterType(Action);
	RegisterType(ActionList);
	RegisterType(ActionListIf);
	RegisterType(DebugAction);
	RegisterType(GameObject);
	RegisterType(Input);
	RegisterType(InputReaction);
	RegisterType(InputAction);
	RegisterType(RuleCheckEntity);
	RegisterType(ResetActionIf);
	RegisterType(ResetActionElse);

	AudioManager::Instance()->AddSound("BackgroundMusic", "Audio/BackgroundMusic.wav");
	AudioManager::Instance()->AddSound("Convert", "Audio/Convert.wav");
	AudioManager::Instance()->AddSound("Die", "Audio/Die.wav");
	AudioManager::Instance()->AddSound("Move", "Audio/Move.wav");
	AudioManager::Instance()->AddSound("Reset", "Audio/Reset.wav");
	AudioManager::Instance()->AddSound("Undo", "Audio/Undo.wav");
	AudioManager::Instance()->AddSound("Win", "Audio/Win.wav");

	AudioManager::Instance()->Init();
}





int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(hPrevInstance);
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;
	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";
	// register the window class
	RegisterClassEx(&wc);
	// create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
		L"WindowClass1",    // name of the window class
		L"Window with DirectX",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		360,    // x-position of the window
		360,    // y-position of the window
		735,    // width of the window
		760,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

				  // display the window on the screen
	ShowWindow(hWnd, nCmdShow);
	//Initalize d3d
	InitD3D(hWnd);
	// this struct holds Windows event messages
	MSG msg;

	ConcreteEntityFactory e;
	ConcreteFurnitureFactory ff;
	ConcreteActionListFactory al;
	ConcreteDebugActionFactory da;
	ConcreteActionListIfFactory ai;
	ConcreteGameObjectFactory cgo;
	ConcreteInputActionFactory ciaf;
	ConcreteInputReactionFactory cirf;
	ConcreteRuleCheckEntityFactory crcef;
	ConcreteResetActionIfFactory craif;
	ConcreteResetActionElseFactory craef;
	ConcreteInputFactory cif;

	Initialize();
	
	World tempWorld;

	LevelManager::InitLevelManager(tempWorld);
	LevelManager::InitializeGame();
	LevelManager::StartLevel(0);

	AudioManager::Instance()->Play("BackgroundMusic", true);

	//bool babaIsPaul = false;
	// wait for the next message in the queue, store the result in 'msg'
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// translate keystroke messages into the right format
		TranslateMessage(&msg);
		tempWorld.Update();

		//if (!babaIsPaul && LevelManager::mLevel == 1)
		//{
		//	std::string* fileNames = mRendering->GetFileNamezzz();
		//	fileNames[2] = "Sprites/PAUL_WORD.PNG";
		//	fileNames[12] = "Sprites/PAUL.PNG";

		//	babaIsPaul = true;
		//}

		GameObject::ClearAllAspects();
		LevelManager::LoadCurrentLevel();
		LevelManager::LoadNextLevel();
		LevelManager::RevertBoard();
		// send the message to the WindowProc function
		DispatchMessage(&msg);
		RenderFrame(*(tempWorld.Sectors()[1]).As<Sector>());
	}
	CleanD3D();

	AudioManager::Instance()->Shutdown();

	// return this part of the WM_QUIT message to Windows
	return (int)msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
	case WM_ACTIVATEAPP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		break;
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}
	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}


