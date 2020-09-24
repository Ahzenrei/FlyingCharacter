#pragma once
#include <fstream>

class FileReader
{
public:
	static const char** getSpritesFromFile(std::string fileName, int& nbFrames, int& height, int& width);
	static void freeSprites(const char**& sprites, int nbSprites);

private:
};

