//#include "pch.h"
#include <string>

//#include "SOIL.h"

#include "Tileset.h"

TileSet::TileSet(std::string textureName, int width, int height) {
	mTextureName = textureName;
	mPixelWidth = width;
	mPixelHeight = height;

	//mTextureId = SOIL_load_OGL_texture(textureName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}