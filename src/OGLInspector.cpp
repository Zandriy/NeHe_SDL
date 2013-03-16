/*
 * OGLInspector.cpp
 *
 *  Created on: Dec 15, 2012
 *      Author: Andrew Zhabura
 */

#include <algorithm>
#include <stdio.h>

#include "OGLInspector.h"

OGLInspector::OGLInspector()
{
	char* str = 0;
	char* token = 0;

	m_extNames = GetExtensions();
	m_extNames.append(" ");
	m_extNames.append(GetGluExtensions());
}

OGLInspector::~OGLInspector()
{
	m_extNames.clear();
}

bool OGLInspector::isExtSupported(const std::string& extName)
{
	if ( m_extNames.find(extName) != std::string::npos )
		return true;

	return false;
}

bool OGLInspector::PBOSupported()
{
	return isExtSupported("GL_ARB_pixel_buffer_object");
}

bool OGLInspector::ImagingSupported()
{
	return isExtSupported("GL_ARB_imaging");
}

bool OGLInspector::MultiTexSupported()
{
	return isExtSupported("GL_ARB_multitexture");
}

bool OGLInspector::TexCombineSupported()
{
	return isExtSupported("GL_EXT_texture_env_combine");
}

std::string OGLInspector::GetLastError()
{
	return (char*)(gluErrorString(glGetError()));
}

std::string  OGLInspector::GetVendor()
{
	return (char*)(glGetString(GL_VENDOR));
}

std::string  OGLInspector::GetRenderer()
{
	return (char*)(glGetString(GL_RENDERER));
}

std::string  OGLInspector::GetVersion()
{
	return (char*)(glGetString(GL_VERSION));
}

std::string  OGLInspector::GetSoftVersion()
{
#ifdef	GL_VERSION_1_5
	return "1.5";
#endif
#ifdef	GL_VERSION_1_4
	return "1.4";
#endif
#ifdef	GL_VERSION_1_3
	return "1.3";
#endif
#ifdef	GL_VERSION_1_2
	return "1.2";
#endif
#ifdef	GL_VERSION_1_1
	return "1.1";
#endif
#ifdef	GL_VERSION_1_0
	return "1.0";
#endif

	return "newer than 1.5";
}

std::string  OGLInspector::GetExtensions()
{
	return (char*)(glGetString(GL_EXTENSIONS));
}

std::string  OGLInspector::GetGluVersion()
{
#ifndef GLU_VERSION_1_1
	return "1.0";
#else
	return (char*)(gluGetString(GLU_VERSION));
#endif
}

std::string  OGLInspector::GetGluExtensions()
{
#ifndef GLU_VERSION_1_1
	return "";
#else
	return (char*)(gluGetString(GLU_EXTENSIONS));
#endif
}


/** auxiliary functions
 *
 */
void printStencilFunc(GLint func)
{
	switch(func)
	{
	case GL_NEVER:
		printf("GL_NEVER");
		break;
	case GL_ALWAYS:
		printf("GL_ALWAYS");
		break;
	case GL_LESS:
		printf("GL_LESS");
		break;
	case GL_LEQUAL:
		printf("GL_LEQUAL");
		break;
	case GL_GEQUAL:
		printf("GL_GEQUAL");
		break;
	case GL_GREATER:
		printf("GL_GREATER");
		break;
	case GL_EQUAL:
		printf("GL_EQUAL");
		break;
	case GL_NOTEQUAL:
		printf("GL_NOTEQUAL");
		break;
	default:
		printf("!!!wrong");
		break;
	}
}

void printStencilOpFunc(GLint func)
{
	switch(func)
	{
	case GL_KEEP:
		printf("GL_KEEP");
		break;
	case GL_ZERO:
		printf("GL_ZERO");
		break;
	case GL_REPLACE:
		printf("GL_REPLACE");
		break;
	case GL_INCR:
		printf("GL_INCR");
		break;
	case GL_DECR:
		printf("GL_DECR");
		break;
	case GL_INVERT:
		printf("GL_INVERT");
		break;
	default:
		printf("!!!wrong");
		break;
	}
}

/** static functions
 *
 */

void OGLInspector::BuffersReport()
{
	GLint resInt;
	GLboolean resBool;

	printf("####################################################\n");
	printf("################## BuffersReport ###################\n");
	printf("####################################################\n");

	printf("=================================================================\n");

	glGetIntegerv(GL_RED_BITS, &resInt);
	printf("| GL_RED_BITS\t| GL_GREEN_BITS\t| GL_BLUE_BITS\t| GL_ALPHA_BITS\t|\n| %d\t\t", resInt);
	glGetIntegerv(GL_GREEN_BITS, &resInt);
	printf("| %d\t\t", resInt);
	glGetIntegerv(GL_BLUE_BITS, &resInt);
	printf("| %d\t\t", resInt);
	glGetIntegerv(GL_RED_BITS, &resInt);
	printf("| %d\t\t|\n", resInt);

	printf("=================================================================\n");

	glGetIntegerv(GL_INDEX_BITS, &resInt);
	printf("| GL_INDEX_BITS\t| GL_DEPTH_BITS\t| GL_STENCIL_BITS\t|\n| %d\t\t", resInt);
	glGetIntegerv(GL_DEPTH_BITS, &resInt);
	printf("| %d\t\t", resInt);
	glGetIntegerv(GL_STENCIL_BITS, &resInt);
	printf("| %d\t\t\t|\n", resInt);

	printf("=================================================================================================\n");

	glGetIntegerv(GL_ACCUM_RED_BITS, &resInt);
	printf("| GL_ACCUM_RED_BITS\t| GL_ACCUM_GREEN_BITS\t| GL_ACCUM_BLUE_BITS\t| GL_ACCUM_ALPHA_BITS\t|\n| %d\t\t\t", resInt);
	glGetIntegerv(GL_ACCUM_GREEN_BITS, &resInt);
	printf("| %d\t\t\t", resInt);
	glGetIntegerv(GL_ACCUM_BLUE_BITS, &resInt);
	printf("| %d\t\t\t", resInt);
	glGetIntegerv(GL_ACCUM_RED_BITS, &resInt);
	printf("| %d\t\t\t|\n", resInt);

	printf("=================================================================================================\n");

	glGetBooleanv(GL_STEREO, &resBool);
	printf("| GL_STEREO\t| GL_DOUBLEBUFFER\t| GL_AUX_BUFFERS\t|\n| %s\t\t", resBool ? "yes" : "no");
	glGetBooleanv(GL_DOUBLEBUFFER, &resBool);
	printf("| %s\t\t\t", resBool ? "yes" : "no");
	glGetIntegerv(GL_AUX_BUFFERS, &resInt);
	printf("| %d\t\t\t|\n", resInt);

	printf("===================================================================================\n");
}

void OGLInspector::StencilReport()
{
	GLint resInt;
	GLboolean resBool = glIsEnabled(GL_STENCIL_TEST);

	printf("####################################################\n");
	printf("################## StencilReport ###################\n");
	printf("####################################################\n");

	printf("+++++++++++ GL_STENCIL_TEST enabled: %s +++++++++++\n",  resBool ? "yes" : " no");

	glGetIntegerv(GL_STENCIL_BITS, &resInt);
	if (!resInt)
		printf("!!!!!!!!!!! STENCIL BUFFER doesn't exist !!!!!!!!!!!\n");

	printf("=========================================================\n");

	printf("| GL_STENCIL_WRITEMASK\t| GL_STENCIL_BACK_WRITEMASK\t|\n");
	glGetIntegerv(GL_STENCIL_WRITEMASK, &resInt);
	printf("| 0x%08X\t\t", resInt);
	glGetIntegerv(GL_STENCIL_BACK_WRITEMASK, &resInt);
	printf("| 0x%08X\t\t\t|\n", resInt);

	printf("=========================================================================\n");

	printf("| GL_STENCIL_FUNC\t| GL_STENCIL_REF\t| GL_STENCIL_VALUE_MASK\t|\n");
	glGetIntegerv(GL_STENCIL_FUNC, &resInt);
	printf("| ");
	printStencilFunc(resInt);
	printf("\t\t");

	glGetIntegerv(GL_STENCIL_REF, &resInt);
	printf("| 0x%08X\t\t", resInt);
	glGetIntegerv(GL_STENCIL_VALUE_MASK, &resInt);
	printf("| 0x%08X\t\t|\n", resInt);

	printf("=========================================================================================\n");

	printf("| GL_STENCIL_FAIL\t| GL_STENCIL_PASS_DEPTH_FAIL\t| GL_STENCIL_PASS_DEPTH_PASS\t|\n");
	glGetIntegerv(GL_STENCIL_FAIL, &resInt);
	printf("| ");
	printStencilOpFunc(resInt);
	printf("\t\t");
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &resInt);
	printf("| ");
	printStencilOpFunc(resInt);
	printf("\t\t\t");
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &resInt);
	printf("| ");
	printStencilOpFunc(resInt);
	printf("\t\t\t|\n");

	printf("=========================================================================================\n");
}
