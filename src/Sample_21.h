/*
 * Sample_21.h
 *
 *  Created on: Mar 12, 2013
 *      Author: Andrew Zhabura
 */

#ifndef Sample_21_H_
#define Sample_21_H_

// Comment this out if you don't want sound.
//#define SOUND

#include "Sample.h"
#include "OGLImageRec.h"

#ifdef SOUND
#include "SDL_mixer.h"
#endif

class Sample_21 : public Sample
{
	enum theConsts {
		INIT_W = 800,
		INIT_H = 600,
		LIN_QTY = 11,
		GAP_QTY = 10,
		ENEMIES = 9,
		STEPS = 6,
		SYM_QTY = 256,
		FIRST_SYM = 32
	};

	enum textures {
		TEX_1,
		TEX_2,
		TEX_QTY
	};

	struct      object                              // Create A Structure For Our Player
	{
		int fx, fy;                             // Fine Movement Position
		int x, y;                               // Current Player Position
		float   spin;                               // Spin Direction
	};


public:
	Sample_21();
	virtual ~Sample_21();

	virtual void reshape(int width, int height);
	virtual char* name() const
	{
		return (char*)&"21. Lines, Antialiasing, Timing, Ortho View And Simple Sounds";
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
	void draw();
	void initGL();
	void restoreGL();

private:
	bool m_vline[LIN_QTY][GAP_QTY];		// Keeps Track Of Vertical Lines
	bool m_hline[GAP_QTY][LIN_QTY];		// Keeps Track Of Horizontal Lines
	bool m_filled;						// Done Filling In The Grid?
	bool m_gameover;					// Is The Game Over?
	bool m_anti;						// Antialiasing?

	int m_delay;						// Enemy Delay
	int m_adjust;                       // Speed Adjustment For Really Slow Video Cards
	int m_lives;             			// Player Lives
	int m_level;                		// Internal Game Level
	int m_level2;                 		// Displayed Game Level
	int m_stage;             			// Game Stage

	struct  object  m_player;                             // Player Information
	struct  object  m_enemy[ENEMIES];                   // Enemy Information
	struct  object  m_hourglass;                          // Hourglass Information

	static	int	s_steps[STEPS];                // Stepping Values For Slow Video Adjustment

	GLuint	m_texture[TEX_QTY];                         // Font Texture Storage Space
	GLuint	m_base;                               // Base Display List For The Font

#ifdef SOUND
	// audio chunk
	Mix_Chunk *chunk;
	Mix_Music *music;
#endif

	OGLImageRec	m_imageFont;
	OGLImageRec	m_imagePict;

	void ResetObjects();

	void buildFont();
	void glPrint( GLint x, GLint y, int set, const char *fmt, ... );
	void playSound( char *sound, int repeat );
};

#endif /* Sample_21_H_ */
