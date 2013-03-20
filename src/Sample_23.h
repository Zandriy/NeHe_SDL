/*
 * Sample_23.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_23_H_
#define Sample_23_H_

#include "Sample.h"

class Sample_23 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};

	enum texFilters {
		TEX_1,
		TEX_2,
		TEX_3,
		TEX_4,
		TEX_5,
		TEX_6,
		TEX_QTY
	};
public:
	Sample_23();
	virtual ~Sample_23();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "23. Sphere Mapping Quadrics (f,l,PgUP,PgDOWN,arrows,space)";
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
	bool	m_light;			// Lighting ON / OFF

	GLfloat		m_xrot;			// X Rotation
	GLfloat		m_yrot;			// Y Rotation
	GLfloat		m_xspeed;		// X Rotation Speed
	GLfloat		m_yspeed;		// Y Rotation Speed
	GLfloat		m_z;			// Depth Into The Screen
	GLuint		m_texture[TEX_QTY];	// Storage For One Texture
	GLuint		m_filter;			// Which Filter To Use

	int m_part1;                    // Start Of Disc
	int m_part2;                    // End Of Disc
	int m_p1;                       // Increase 1
	int m_p2;                       // Increase 2
	GLUquadricObj *m_quadratic;     // Storage For Our Quadratic Objects
	GLuint  m_object;             // Which Object To Draw

	void glDrawCube();
	void LoadGLTextures();
};

#endif /* Sample_23_H_ */
