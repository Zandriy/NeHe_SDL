/*
 * OGLInspector.h
 *
 *  Created on: Dec 15, 2012
 *      Author: Andrew Zhabura
 */

#ifndef OGLInspector_H
#define OGLInspector_H

#include <cstring>
#include <string>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

class OGLInspector
{
public:
	OGLInspector();
	~OGLInspector();

	bool isExtSupported(const std::string& extName);
	bool PBOSupported();
	bool ImagingSupported();
	bool MultiTexSupported();
	bool TexCombineSupported();

	static std::string  GetLastError();
	static std::string  GetVendor();
	static std::string  GetRenderer();
	static std::string  GetVersion();
	static std::string  GetSoftVersion();
	static std::string  GetExtensions();
	static std::string  GetGluVersion();
	static std::string  GetGluExtensions();

	static void BuffersReport();
	static void StencilReport();
private:
	std::string m_extNames;
};


#endif
