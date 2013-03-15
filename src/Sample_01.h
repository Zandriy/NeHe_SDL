/*
 * Sample_01.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_01_H_
#define Sample_01_H_

#include "Sample.h"

class Sample_01 : public Sample
{
	enum classConsts {
		INIT_W = 400,
		INIT_H = 300
	};
public:
	Sample_01();
	virtual ~Sample_01();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "01. OpenGL Framework";
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
};

#endif /* Sample_01_H_ */
