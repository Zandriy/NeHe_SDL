/*
 * Sample.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_H_
#define Sample_H_

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#ifndef GL_EXT_texture_env_combine
#define GL_COMBINE_EXT                    0x8570
#define GL_COMBINE_RGB_EXT                0x8571
#endif
#elif	__linux__
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#endif

#ifndef	GL_ALL_CLIENT_ATTRIB_BITS
#define	GL_ALL_CLIENT_ATTRIB_BITS	GL_CLIENT_PIXEL_STORE_BIT | GL_CLIENT_VERTEX_ARRAY_BIT
#endif

class Sample
{
public:
	virtual ~Sample(){}

	virtual void reshape(int width, int height) = 0;
	virtual const char* name() const = 0;
	virtual int width() const = 0;
	virtual int height() const = 0;
	virtual void draw() = 0;
	virtual void initGL() = 0;
	virtual void restoreGL() = 0;

	virtual bool sendMessage(int message, int mode, int x, int y)
	{
		return false;
	}

	virtual void sendIdleMessage(){}
};

#endif /* Sample_2_10_H_ */
