/*
 * Sample_11.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_11_H_
#define Sample_11_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_11 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};
public:
	Sample_11();
	virtual ~Sample_11();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "11. Flag Effect or Waving Texture";
	}
	virtual int width() const
	{
		return INIT_W;
	}
	virtual int height() const
	{
		return INIT_H;
	}

protected:
	virtual void draw();
	virtual void initGL();
	virtual void restoreGL();

private:
	enum texFilters {
		TEX_1,
		TEX_QTY
	};

	enum theConsts {
		COORD_QTY = 3,
		GRID_SIZE = 45
	};

	GLfloat		m_xrot;				// X Rotation
	GLfloat		m_yrot;				// Y Rotation
	GLfloat		m_zrot;				// Z Rotation
	GLuint		m_texture[TEX_QTY];	// Storage For One Texture
	OGLImageRec	m_image;

	float m_points[ 45 ][ 45 ][COORD_QTY];		// The Array For The Points On The Grid Of Our "Wave"
	int m_wiggle_count;					// Counter Used To Control How Fast Flag Waves
	GLfloat m_hold;						// Temporarily Holds A Floating Point Value
};

#endif /* Sample_11_H_ */
