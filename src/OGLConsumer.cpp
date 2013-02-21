/*
 * OGLConsumer.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
 */

#include <exception>

#include "OGLConsumer.h"

#include "Sample_01.h"

#define Sample_QTY 1

OGL_Consumer::OGL_Consumer()
:	m_Sample(new Sample * [Sample_QTY])
,	m_SampleNum(0)
{
	int i = -1;

	m_Sample[++i] = new Sample_01;

	if ( ++i != Sample_QTY )
		throw this;
}

OGL_Consumer::~OGL_Consumer()
{
	for (int i = 0; i < Sample_QTY; ++i)
	{
		if (m_Sample[i])
			delete m_Sample[i];
	}
}

void OGL_Consumer::setSample(unsigned int SampleNum)
{
	if (SampleNum >= Sample_QTY)
		return;

	m_SampleNum = SampleNum;
}

bool OGL_Consumer::sendMessage(unsigned int SampleNum, int message, int mode, int x, int y)
{
	return m_Sample[m_SampleNum]->sendMessage(message, mode, x, y);
}

void OGL_Consumer::reshape(unsigned int width, unsigned int height)
{
	m_Sample[m_SampleNum]->reshape(width, height);
}

// Here goes our drawing code
void OGL_Consumer::drawGLScene()
{
	m_Sample[m_SampleNum]->drawGLScene();
}

char* OGL_Consumer::getSampleName()
{
	return m_Sample[m_SampleNum]->getName();
}