#pragma once
#include "glm\glm.hpp"
#include "RuleCheckEntity.h"
#include <SpriteBatch.h>

namespace FieaGameEngine
{

	class Texture
	{
	public:
		Texture(ID3D11Device * device, std::string filePath);
		~Texture();
		ID3D11ShaderResourceView * mTextureView;
	};

	class Rendering
	{
	public:
		Rendering(ID3D11DeviceContext * context, ID3D11Device * device);
		~Rendering();

		void Update(Sector& s);

		void DrawObjectOnGrid(uint32_t x, uint32_t y, const BoardSpaceObject & type) const;

		std::string* GetFileNamezzz();

	private:

		std::string GetFileNameFromType(const BoardSpaceObject & type) const;

		void DrawSpriteAtLocation(const glm::vec4 & location, const BoardSpaceObject & type) const;
		ID3D11Device * mDevice;
		ID3D11DeviceContext * mDeviceContext;
		const long tileWidth;
		const long tileHeight;

		HashMap<std::string, Texture*> mAllTextures;
	
		class DirectX::SpriteBatch * mSpriteBatch;

		std::string fileNamezzz[21]{
			"Sprites/INVALID.PNG",
			"Sprites/IS_WORD.PNG",
			"Sprites/BABA_WORD.PNG",
			"Sprites/ROCK_WORD.PNG",
			"Sprites/FLAG_WORD.PNG",
			"Sprites/BONE_WORD.PNG",
			"Sprites/WALL_WORD.PNG",
			"Sprites/PUSH_WORD.PNG",
			"Sprites/STOP_WORD.PNG",
			"Sprites/KILL_WORD.PNG",
			"Sprites/WIN_WORD.PNG",
			"Sprites/YOU_WORD.PNG",
			"Sprites/BABA.PNG",
			"Sprites/ROCK.PNG",
			"Sprites/FLAG.PNG",
			"Sprites/BONE.PNG",
			"Sprites/WALL.PNG",
			"Sprites/GRASS.PNG",
			"Sprites/MAX.PNG",
			"Sprites/PAUL.PNG",
			"Sprites/PAUL_WORD.PNG"
		};
	};

	

}