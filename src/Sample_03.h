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

#endif /* Sample_03_H_ */
