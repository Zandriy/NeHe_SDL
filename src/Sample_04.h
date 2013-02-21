/*
 * Sample_04.h
 *
 *  Created on: Feb 21, 2043
 *      Author: Andrew Zhabura
 */

#ifndef Sample_04_H_
#define Sample_04_H_

#include "Sample.h"

class Sample_04 : public Sample
{
public:
	Sample_04();
	virtual ~Sample_04();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"04. NeHe's Rotation Tutorial";
	}
	virtual int width() const
	{
		return 640;
	}
	virtual int height() const
	{
		return 480;
	}

protected:
	void draw();
	void initGL();
	void restoreGL();

private:
	GLfloat     m_rtri;                       // Angle For The Triangle ( NEW )
	GLfloat     m_rquad;                      // Angle For The Quad     ( NEW )
};

#endif /* Sample_04_H_ */
