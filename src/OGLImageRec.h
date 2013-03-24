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
#include    <stdio.h>                             // Header File For Standard Input / Output
#include    <stdarg.h>                                // Header File For Variable Argument Routines
#include    <string.h>                                // Header File For String Management

class OGLImageRec
{
public:
	OGLImageRec()
	:	m_sizeX(0)
	,	m_sizeY(0)
	,	m_bpp(24)
	,	m_data(NULL)
	{
	}

	~OGLImageRec()
	{
		delete [] m_data;
	}

	unsigned int sizeX() { return m_sizeX; }
	unsigned int sizeY() { return m_sizeY; }
	unsigned int bpp() { return m_bpp; }
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

	bool loadTGA(std::string filename)                 // Loads A TGA File Into Memory
	{
	    GLubyte     TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};            // Uncompressed TGA Header
	    GLubyte     TGAcompare[12];                         // Used To Compare TGA Header
	    GLubyte     header[6];                          // First 6 Useful Bytes From The Header
	    GLuint      bytesPerPixel;                          // Holds Number Of Bytes Per Pixel Used In The TGA File
	    GLuint      imageSize;                          // Used To Store The Image Size When Setting Aside Ram
	    GLuint      temp;                               // Temporary Variable
	    FILE *file = fopen(filename.c_str(), "rb");                     // Open The TGA File

	    if( file==NULL ||                               // Does File Even Exist?
	        fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||  // Are There 12 Bytes To Read?
	        memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0       ||  // Does The Header Match What We Want?
	        fread(header,1,sizeof(header),file)!=sizeof(header))            // If So Read Next 6 Header Bytes
	    {
	        if (file == NULL)                           // Did The File Even Exist? *Added Jim Strong*
	            return false;                           // Return False
	        else
	        {
	            fclose(file);                           // If Anything Failed, Close The File
	            return false;                           // Return False
	        }
	    }
	    m_sizeX  = header[1] * 256 + header[0];                   // Determine The TGA Width  (highbyte*256+lowbyte)
	    m_sizeY = header[3] * 256 + header[2];                   // Determine The TGA Height (highbyte*256+lowbyte)

	    if( m_sizeX   <=0  ||                      // Is The Width Less Than Or Equal To Zero
	        m_sizeY  <=0  ||                      // Is The Height Less Than Or Equal To Zero
	        (header[4]!=24 && header[4]!=32))                   // Is The TGA 24 or 32 Bit?
	    {
	        fclose(file);                               // If Anything Failed, Close The File
	        return false;                               // Return False
	    }
	    m_bpp = header[4];                            // Grab The TGA's Bits Per Pixel (24 or 32)
	    bytesPerPixel   = m_bpp/8;                        // Divide By 8 To Get The Bytes Per Pixel
	    imageSize   = m_sizeX*m_sizeY*bytesPerPixel;           // Calculate The Memory Required For The TGA Data
	    m_data=(GLubyte *)malloc(imageSize);             // Reserve Memory To Hold The TGA Data

	    if( m_data==NULL ||                      // Does The Storage Memory Exist?
	        fread(m_data, 1, imageSize, file)!=imageSize)        // Does The Image Size Match The Memory Reserved?
	    {
	        if(m_data!=NULL)                     // Was Image Data Loaded
	            free(m_data);                    // If So, Release The Image Data

	        fclose(file);                               // Close The File
	        return false;                               // Return False
	    }
	    for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)              // Loop Through The Image Data
	    {                                       // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
	        temp=m_data[i];                      // Temporarily Store The Value At Image Data 'i'
	        m_data[i] = m_data[i + 2];            // Set The 1st Byte To The Value Of The 3rd Byte
	        m_data[i + 2] = temp;                    // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	    }

	    fclose (file);                                  // Close The File

	    return true;                                    // Texture Building Went Ok, Return True
	}

private:
	unsigned int m_sizeX;
	unsigned int m_sizeY;
	unsigned int m_bpp;
	unsigned char *m_data;
};

#endif /* OGLIMAGEREC_H_ */
