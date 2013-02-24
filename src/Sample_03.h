/*
 * Sample_03.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_03_H_
#define Sample_03_H_

#include "Sample.h"

class Sample_03 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};
public:
	Sample_03();
	virtual ~Sample_03();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"03. Color";
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
	void draw();
	void initGL();
	void restoreGL();
};

#endif /* Sample_03_H_ */
