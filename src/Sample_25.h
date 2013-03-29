/*
 * Sample_25.h
 *
 *  Created on: Mar 29, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_25_H_
#define Sample_25_H_

#include "Sample.h"
#include    <iostream>

typedef struct                                      // Structure For 3D Points
{
	float   x, y, z;                                // X, Y & Z Points
} VERTEX;                                       // Called VERTEX

class Sample_25 : public Sample
{
	enum classConsts {
		INIT_W = 800,
		INIT_H = 600
	};

	typedef struct                                      // Structure For An Object
	{
		int        verts;                                  // Number Of Vertices For The Object
		VERTEX     *points;                                // One Vertice (Vertex x,y & z)
	} OBJECT;                                       // Called OBJECT
public:
	Sample_25();
	virtual ~Sample_25();

	virtual void reshape(int width, int height);
	virtual const char* name() const
	{
		return "25. Morphing & Loading Objects From A File(q,w,e,r;a,s,d,z,x,c;PageUp,PageDown,arrows)";
	}
	virtual int width() const
	{
		return INIT_W;
	}
	virtual int height() const
	{
		return INIT_H;
	}
	virtual bool sendMessage(int message, int mode, int x, int y);

protected:
	virtual void draw();
	virtual void initGL();
	virtual void restoreGL();

private:
	GLfloat     m_xrot,m_yrot,m_zrot,                             // X, Y & Z Rotation
	m_xspeed,m_yspeed,m_zspeed,                           // X, Y & Z Spin Speed
	m_cx,m_cy,m_cz;                               // X, Y & Z Position

	int     m_key;                                  // Used To Make Sure Same Morph Key Is Not Pressed
	int     m_step,m_steps;                           // Step Counter And Maximum Number Of Steps
	bool    m_morph;                                // Default morph To False (Not Morphing)

	int     m_maxver;                                 // Will Eventually Hold The Maximum Number Of Vertices
	OBJECT      m_morph1,m_morph2,m_morph3,m_morph4,                        // Our 4 Morphable Objects (morph1,2,3 & 4)
	m_helper,*m_sour,*m_dest;                         // Helper Object, Source Object, Destination Object

	void objallocate(OBJECT *k,int n) ;
	void objfree(OBJECT *k);
	void readstr(FILE *f, char *string);
	void objload(const char *name,OBJECT *k);
	VERTEX calculate(int i);

};

#endif /* Sample_25_H_ */
