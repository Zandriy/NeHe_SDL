/*
 * Sample_19.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_19_H_
#define Sample_19_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_19 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480,
		MAX_PARTICLES = 1000,
		COL_QTY = 12,
		COL_RGB = 3
	};

	enum texNumbers {
		TEX_1,
		TEX_QTY
	};

	typedef struct                      // Create A Structure For Particle
	{
	    bool    active;                 // Active (Yes/No)
	    float   life;                   // Particle Life
	    float   fade;                   // Fade Speed
	    float   r;                  // Red Value
	    float   g;                  // Green Value
	    float   b;                  // Blue Value
	    float   x;                  // X Position
	    float   y;                  // Y Position
	    float   z;                  // Z Position
	    float   xi;                 // X Direction
	    float   yi;                 // Y Direction
	    float   zi;                 // Z Direction
	    float   xg;                 // X Gravity
	    float   yg;                 // Y Gravity
	    float   zg;                 // Z Gravity
	}
	particles;                      // Particles Structure

public:
	Sample_19();
	virtual ~Sample_19();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"19. Particle Engine Using Triangle Strips ( arrows,PageUp,PageDown,Tab,+,-,Return,Space )";
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
	virtual void draw();
	virtual void initGL();
	virtual void restoreGL();

private:

	bool    m_rainbow;
	float   m_slowdown;        // Slow Down Particles
	float   m_xspeed;          // Base X Speed (To Allow Keyboard Direction Of Tail)
	float   m_yspeed;          // Base Y Speed (To Allow Keyboard Direction Of Tail)
	float   m_zoom;            // Used To Zoom Out
	GLuint  m_col;                // Current Color Selection
	GLuint  m_delay;              // Rainbow Effect Delay
	GLuint	m_texture[TEX_QTY];	// Storage For One Texture
	particles m_particle[MAX_PARTICLES];          // Particle Array (Room For Particle Info)
	static GLfloat	s_colors[COL_QTY][COL_RGB];				// Rainbow Of Colors
	OGLImageRec	m_image;
};

#endif /* Sample_19_H_ */
