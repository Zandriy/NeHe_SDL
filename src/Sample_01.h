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
public:
	Sample_01();
	virtual ~Sample_01();

	virtual void reshape(int width, int height);
	virtual char* getName()
	{
		return (char*)&"NeHe 01";
	}

protected:
	void draw();
	void initGL();
	void restoreGL();
};

#endif /* Sample_01_H_ */
