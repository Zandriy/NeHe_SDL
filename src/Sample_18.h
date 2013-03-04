/*
 * Sample_18.h
 *
 *  Created on: Mar 4, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_18_H_
#define Sample_18_H_

#include "Sample.h"
#include "OGLImageRec.h"

class Sample_18 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};
public:
	Sample_18();
	virtual ~Sample_18();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"18. Quadrics (f,l,PgUP,PgDOWN,arrows,space)";
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
		NEAREST_FILTER,
		LINEAR_FILTER,
		MIPMAPPED_FILTER,
		TEX_QTY
	};

	bool	m_light;			// Lighting ON / OFF

	GLfloat		m_xrot;			// X Rotation
	GLfloat		m_yrot;			// Y Rotation
	GLfloat		m_xspeed;		// X Rotation Speed
	GLfloat		m_yspeed;		// Y Rotation Speed
	GLfloat		m_z;			// Depth Into The Screen
	GLuint		m_texture[TEX_QTY];	// Storage For One Texture
	GLuint		m_filter;			// Which Filter To Use
	OGLImageRec	m_image;

	int m_part1;                    // Start Of Disc
	int m_part2;                    // End Of Disc
	int m_p1;                       // Increase 1
	int m_p2;                       // Increase 2
	GLUquadricObj *m_quadratic;     // Storage For Our Quadratic Objects
	GLuint  m_object;             // Which Object To Draw

	void glDrawCube();
};

#endif /* Sample_18_H_ */
