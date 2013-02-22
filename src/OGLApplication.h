/*
 * OGLApplication.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
*/

#ifndef OGL_APPLICATION_H_
#define OGL_APPLICATION_H_

#include <SDL/SDL.h>
#include "OGLConsumer.h"

class OGL_Application
{
public:
	OGL_Application();
	~OGL_Application();
	void init();
	int exec();
private:
	SDL_Surface *m_surface;
	unsigned int  m_videoFlags;
	int  m_breakReason;
	bool m_isActive;
	unsigned int  m_width;
	unsigned int  m_height;
	unsigned int  m_bpp;
	OGL_Consumer * m_OGL_Consumer;
	unsigned int  m_curSample;
	char m_sampleNum[2];

	void setSample();
	bool resizeWindow( int width, int height );
	void handleKeyPress( SDL_keysym *keysym );
	void drawGLScene();
};

#endif // OGL_APPLICATION_H_
