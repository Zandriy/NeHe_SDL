/*
 * Sample_02.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_02_H_
#define Sample_02_H_

#include "Sample.h"

class Sample_02 : public Sample
{
	enum classConsts {
		INIT_W = 640,
		INIT_H = 480
	};
public:
	Sample_02();
	virtual ~Sample_02();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"02. First Polygon";
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

#endif /* Sample_02_H_ */
