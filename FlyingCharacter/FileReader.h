#pragma once
#include <fstream>

class FileReader
{
public:
	static char** getSpritesFromFile(std::string fileName, int& nbFrames, int& height, int& width);
	static void freeSprites(char**& sprites, int nbSprites);

private:
};

