/*
 * OGLImageRec.h
 *
 *  Created on: Dec 13, 2012
 *      Author: main
 */

#ifndef OGLIMAGEREC_H_
#define OGLIMAGEREC_H_


#include <cstdlib>
#include <iostream>
#include <fstream>

class OGLImageRec
{
public:
	OGLImageRec()
	:	m_sizeX(0)
	,	m_sizeY(0)
	,	m_data(NULL)
	{
	}

	~OGLImageRec()
	{
		delete [] m_data;
	}

	unsigned int sizeX() { return m_sizeX; }
	unsigned int sizeY() { return m_sizeY; }
	unsigned char* data() { return m_data; }

	// Routine to read a bitmap file.
	// Works only for uncompressed m_bmp files of 24-bit color.
	void loadBMP( std::string filename )
	{
		if (m_data)
		{
			delete [] m_data;
			m_data = NULL;
		}

		unsigned int size, offset, headerSize;

		// Read input file name.
		std::ifstream infile(filename.c_str(), std::ios::binary);

		// Get the starting point of the image data.
		infile.seekg(10);
		infile.read((char *) &offset, 4);

		// Get the header size of the bitmap.
		infile.read((char *) &headerSize,4);

		// Get width and height values in the bitmap header.
		infile.seekg(18);
		infile.read( (char *) &m_sizeX, 4);
		infile.read( (char *) &m_sizeY, 4);

		// Allocate buffer for the image.
		size = m_sizeX * m_sizeY * 24;
		m_data = new unsigned char[size];

		// Read bitmap data.
		infile.seekg(offset);
		infile.read((char *) m_data , size);

		// Reverse color from bgr to rgb.
		int temp;
		for (int i = 0; i < size; i += 3)
		{
			temp = m_data[i];
			m_data[i] = m_data[i+2];
			m_data[i+2] = temp;
		}
	}

private:
	unsigned int m_sizeX;
	unsigned int m_sizeY;
	unsigned char *m_data;
};

#endif /* OGLIMAGEREC_H_ */
