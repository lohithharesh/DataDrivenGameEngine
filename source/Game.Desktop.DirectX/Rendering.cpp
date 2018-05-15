#include "pch.h"
#include "Rendering.h"
#include "GameTime.h"
#include "SpriteBatch.h"
#include "WICTextureLoader.h"
#include "Shlwapi.h"
#include "Sector.h"
#include "GameObject.h"
#include "LevelManager.h"

using namespace DirectX;

namespace FieaGameEngine
{
	Rendering::Rendering(ID3D11DeviceContext * context, ID3D11Device * device)
		: tileWidth(36), tileHeight(36), mAllTextures(100)
	{
		//initialize the board renderer
		mSpriteBatch = new DirectX::SpriteBatch(context);
		mDevice = device;
		mDeviceContext = context;

		//initialize textures
		WCHAR PathBuffer[MAX_PATH];
		GetModuleFileName(nullptr, PathBuffer, MAX_PATH);
		PathRemoveFileSpec(PathBuffer);
		std::wstring Path(PathBuffer);
		SetCurrentDirectory(Path.c_str());

		for (uint32_t i = 0; i < 21; i++)
		{
			Texture* newTexture = new Texture(device, fileNamezzz[i].c_str());
			mAllTextures[fileNamezzz[i]] = newTexture;
			auto j = mAllTextures.Size();
			j;
		}
		
	}

	Rendering::~Rendering()
	{

		delete mSpriteBatch;
	}

	void Rendering::Update(Sector& s)
	{
		UNREFERENCED_PARAMETER(s);

		RuleCheckEntity::Board& board = FieaGameEngine::LevelManager::mBoard;

		for (uint32_t i = 0u; i < RuleCheckEntity::BOARD_SIZE; ++i)
		{
			for (uint32_t j = 0u; j < RuleCheckEntity::BOARD_SIZE; ++j)
			{
				for (GameObject* entity : board[i][j])
				{
					DrawObjectOnGrid(entity->GetGameObjectPosition()[1], entity->GetGameObjectPosition()[0], entity->GetGameObjectType());
				}
			}
		}
	}


	void Rendering::DrawObjectOnGrid(uint32_t x, uint32_t y, const BoardSpaceObject & type) const
	{
		DrawSpriteAtLocation(glm::vec4(x*tileWidth, y * tileHeight, 0, 0), type);
	}




	void Rendering::DrawSpriteAtLocation(const glm::vec4 & location, const BoardSpaceObject & type) const
	{
		location; type;
		tagRECT t;
		t.left = static_cast<long>(location[0]);
		t.right = static_cast<long>(location[0]) + tileHeight;
		t.top = static_cast<long>(location[1]);
		t.bottom = static_cast<long>(location[1]) + tileWidth;
		const RECT drawRect(t);

		ID3D11BlendState* g_pBlendState = NULL;
		mDeviceContext->OMGetBlendState(&g_pBlendState, 0, 0u);
		mSpriteBatch->Begin(SpriteSortMode_Deferred, g_pBlendState);

		std::string typeName = GetFileNameFromType(type);

		/*if (type == BoardSpaceObject::BABA && LevelManager::mLevel >= 1)
		{
			typeName = "Sprites/PAUL.PNG";
		}
		else if (type == BoardSpaceObject::BABA_WORD && LevelManager::mLevel >= 1)
		{
			typeName = "Sprites/PAUL_WORD.PNG";
		}*/

		mSpriteBatch->Draw(mAllTextures.At(typeName)->mTextureView, drawRect);
		mSpriteBatch->End();
	}




	std::string Rendering::GetFileNameFromType(const BoardSpaceObject & type) const
	{
		return fileNamezzz[static_cast<int>(type)];
	}




	std::string* Rendering::GetFileNamezzz()
	{
		return fileNamezzz;
	}




	Texture::Texture(ID3D11Device * device, std::string filePath)
	{
		size_t newsize = strlen(filePath.c_str()) + 1;
		wchar_t * wcstring = new wchar_t[newsize];
		size_t convertedChars = 0;

		mbstowcs_s(&convertedChars, wcstring, newsize, filePath.c_str(), _TRUNCATE);


		auto hit = DirectX::CreateWICTextureFromFile(device, wcstring, nullptr, &mTextureView);
		hit;
		assert(!FAILED(hit));
		delete[] wcstring;
	}




	Texture::~Texture()
	{

		mTextureView->Release();
	}

}
