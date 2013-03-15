/*
 * OGLConsumer.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
 */

#ifndef OGL_CONSUMER_H_
#define OGL_CONSUMER_H_

class Sample;

class OGL_Consumer
{
public:
	OGL_Consumer();
	~OGL_Consumer();
	bool setSample(unsigned int SampleNum);
	bool sendMessage(unsigned int SampleNum, int message, int mode, int x, int y);
	void sendIdleMessage();
	void reshape(unsigned int width, unsigned int height);
	void drawGLScene();
	char* sampleName() const;
	int width() const;
	int height() const;

private:
	Sample ** m_Sample;
	unsigned int m_SampleNum;
	bool m_init;
};

#endif // OGL_CONSUMER_H_
