#include "FileReader.h"
//#include <fstream>

char** FileReader::getSpritesFromFile(std::string fileName, int& nbFrames, int& height, int& width)
{
	std::ifstream fileStream = std::ifstream(fileName);

	fileStream >> nbFrames;
	fileStream >> height;
	fileStream >> width;
	int size = height * width;

	char** sprites = (char**)malloc(sizeof(char*) * nbFrames);

	if (sprites == nullptr)
	{
		return nullptr;
	}

	char* charSprite = nullptr;
	for (int i = 0; i < nbFrames; i++)
	{
		//sprites[i] = nullptr;

		charSprite = (char*)malloc(sizeof(char) * (size));

		if (charSprite == nullptr)
		{
			freeSprites(sprites, i);
			return nullptr;
		}

		fileStream.get();
		for (int j = 0; j < size; j += width)
		{
			fileStream.get();
			fileStream.read(&charSprite[j], width);
		}

		sprites[i] = charSprite;
	}

	return sprites;
}

void FileReader::freeSprites(char**& sprites, int nbSprites)
{
	if (sprites != nullptr)
	{
		for (int i = 0; i < nbSprites; i++)
		{
			if (sprites[i] != nullptr)
			{
				free(sprites[i]);
			}
		}
		free(sprites);
	}
}
