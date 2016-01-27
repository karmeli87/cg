#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

#include <GL/glew.h>
#ifdef _WIN32
#include "GL/wglew.h"
#endif
#include <GL/gl.h>
#include "Common.h"

static class TextureLoadr {
public:
	static void load(GLuint &bindID,const char* path,unsigned int height,unsigned int width){
		std::vector<unsigned char> textureData;
		glGenTextures(1, &bindID);

		printf("loading texture : %s with id %d\n", path, bindID);
		loadPNG(path, textureData, width, height);
		
		glBindTexture(GL_TEXTURE_2D, bindID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, height, width, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		textureData.empty();
	}
	static std::vector<unsigned char> getData(const char* path, unsigned int height, unsigned int width){
		std::vector<unsigned char> textureData;
		loadPNG(path, textureData, width, height);
		return textureData;
	}
};

#endif