/*
 * Sample_09.h
 *
 *  Created on: Feb 23, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_09_H_
#define Sample_09_H_

#include "Sample.h"
#include "OGLImageRec.h"

class SDL_Surface;

class Sample_09 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480,
		NUM_STARS =	50
	};
public:
	Sample_09();
	virtual ~Sample_09();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"09. Moving Bitmaps In 3D Space (s,t,PgUP,PgDOWN,arrows(UP,DOWN))";
	}
	virtual int width() const
	{
		return INIT_W;
	}
	virtual int height() const
	{
		return INIT_H;
	}

	virtual bool sendMessage(int message, int mode, int x, int y);

protected:
	void draw();
	void initGL();
	void restoreGL();

private:
	enum texFilters {
		TEX_1,
		TEX_QTY
	};

	bool	m_twinkle;			// Twinkling Stars

	typedef struct				// Create A Structure For Star
	{
		int r, g, b;			// Stars Color
		GLfloat dist,			// Stars Distance From Center
				angle;			// Stars Current Angle
	}
	stars;

	stars m_star[NUM_STARS];			// Need To Keep Track Of 'NUM' Stars
	GLfloat	m_zoom;				// Distance Away From Stars
	GLfloat m_tilt;				// Tilt The View
	GLfloat	m_spin;				// Spin Stars
	GLuint	m_loop;				// General Loop Variable

	GLuint		m_texture[TEX_QTY];	// Storage For One Texture
	SDL_Surface *m_imageSDL;
	OGLImageRec	m_image;
	bool	m_useSDLImage;
};

#endif /* Sample_09_H_ */
