/*
 * Sample_02.h
 *
 *  Created on: Feb 21, 2023
 *      Author: Andrew Zhabura
 */

#ifndef Sample_02_H_
#define Sample_02_H_

#include "Sample.h"

class Sample_02 : public Sample
{
public:
	Sample_02();
	virtual ~Sample_02();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"02. NeHe's First Polygon";
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
};

#endif /* Sample_02_H_ */
