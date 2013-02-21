/*
 * OGLApplication.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: Andrew Zhabura
 */

#include "OGLApplication.h"

// if BPP is 0, it will be set to maximum possible
// #define SURFACE_BPP		24
#define SURFACE_BPP		0

#define INIT_W		500
#define INIT_H		500
#define INIT_SAMPLE		0

OGL_Application::OGL_Application()
:	m_surface (NULL)
,	m_videoFlags (0)
,	m_breakReason(0)
,	m_isActive(true)
,	m_width(INIT_W)
,	m_height(INIT_H)
,	m_bpp(SURFACE_BPP)
,	m_OGL_Consumer(NULL)
,	m_curSample(INIT_SAMPLE)
{
	 m_sampleNum[0] = m_sampleNum[1] = 0;
}

OGL_Application::~OGL_Application()
{
	// clean up the window
	SDL_Quit( );
}

void OGL_Application::init()
{
	// initialize SDL
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf( stderr, "Video initialization failed: %s\n",
				SDL_GetError( ) );
		m_breakReason = -1;
		return;
	}

	// this holds some info about our display
	const SDL_VideoInfo *m_videoInfo;

	// Fetch the video info
	m_videoInfo = SDL_GetVideoInfo( );

	if ( !m_videoInfo )
	{
		fprintf( stderr, "Video query failed: %s\n",
				SDL_GetError( ) );
		m_breakReason = -1;
		return;
	}

	// the flags to pass to SDL_SetVideoMode
	m_videoFlags  = SDL_OPENGL;         // Enable OpenGL in SDL
	m_videoFlags |= SDL_DOUBLEBUF; 		// Enable double buffering (valid only with SDL_HWSURFACE)
	m_videoFlags |= SDL_HWSURFACE; 		// Enable creation the video surface in video memory
	m_videoFlags |= SDL_HWPALETTE;      // Store the palette in hardware
	m_videoFlags |= SDL_RESIZABLE;      // Enable window resizing

	// This checks to see if surfaces can be stored in memory
	if ( m_videoInfo->hw_available )
		m_videoFlags |= SDL_HWSURFACE;
	else
		m_videoFlags |= SDL_SWSURFACE;

	// This checks if hardware blits can be done
	if ( m_videoInfo->blit_hw )
		m_videoFlags |= SDL_HWACCEL;

	// Sets up OpenGL attributes, this must be done before SDL_SetVideoMode()
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );	// double buffering
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );	// the minimum number of bits in the depth buffer
	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );	// the minimum number of bits in the stencil buffer
	SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 8 ); // the minimum number of bits for the red channel of the accumulation buffer
	SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 8 ); // the minimum number of bits for the green channel of the accumulation buffer
	SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 8 ); // the minimum number of bits for the blue channel of the accumulation buffer
	SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 8 ); // the minimum number of bits for the alpha channel of the accumulation buffer

	// get a SDL surface
	m_surface = SDL_SetVideoMode( m_width, m_height, m_bpp,
			m_videoFlags );

	// Verify there is a surface
	if ( !m_surface )
	{
		fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
		m_breakReason = -1;
		return;
	}

	m_OGL_Consumer = new OGL_Consumer;
}

int OGL_Application::exec()
{
	// the start Sample
	m_OGL_Consumer->setSample(m_curSample);
	SDL_WM_SetCaption(m_OGL_Consumer->getSampleName(), NULL);
	resizeWindow( INIT_W, INIT_H );

	// used to collect events
	SDL_Event event;

	// wait for events
	while ( !m_breakReason )
	{
		// handle the events in the queue

		while ( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
			case SDL_ACTIVEEVENT:
				// Something's happend with our focus
				// If we lost focus or we are iconified, we
				// shouldn't draw the m_surface

				if ( event.active.gain == 0 )
					m_isActive = false;
				else
					m_isActive = true;
				break;
			case SDL_VIDEORESIZE:
				// handle resize m_event
				resizeWindow( event.resize.w, event.resize.h);
				break;
			case SDL_KEYDOWN:
				// handle key presses
				handleKeyPress( &event.key.keysym );
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				m_OGL_Consumer->sendMessage(m_curSample, event.button.button, event.button.state,
						event.button.x, event.button.y);
				break;
			case SDL_MOUSEMOTION:
				m_OGL_Consumer->sendMessage(m_curSample, event.button.button, event.motion.state,
						event.motion.x, event.motion.y);
				break;
			case SDL_QUIT:
				// handle quit requests
				m_breakReason = SDL_QUIT;
				break;
			default:
				break;
			}
		}

		// draw the scene
		if ( m_isActive )
		{
			drawGLScene();
		}
	}

	if (m_breakReason == SDL_QUIT)
		m_breakReason = 0;

	return m_breakReason;
}

// function to reset our viewport after a window resize
bool OGL_Application::resizeWindow( int width, int height )
{
	m_width = width;
	m_height = height;

	m_surface = SDL_SetVideoMode( m_width, m_height, m_bpp, m_videoFlags );
	if ( !m_surface )
	{
		fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
		m_breakReason = SDL_VIDEORESIZE;
	}

	m_OGL_Consumer->reshape( m_width, m_height );

	drawGLScene();

	return true;
}

// function to handle key press events
void OGL_Application::handleKeyPress( SDL_keysym *keysym )
{
	char num = 0;

	if ( m_OGL_Consumer->sendMessage(m_curSample, keysym->sym, keysym->mod, 0, 0) )
		return;

	switch ( keysym->sym )
	{
	case SDLK_ESCAPE:
		// ESC key was pressed
		m_breakReason = SDL_QUIT;
		break;
	case SDLK_F10:
		// !!! This part is not finished yet and it doesn't work properly.
		// F10 key was pressed
		// this toggles fullm_surface mode
		//int flags = m_surface->flags; /* Save the current flags in case toggling fails */
		m_surface = SDL_SetVideoMode(0, 0, m_bpp, m_surface->flags ^ SDL_FULLSCREEN); /*Toggles FullScreen Mode */
		//if(m_surface == NULL) m_surface = SDL_SetVideoMode(0, 0, 0, flags); /* If toggle FullScreen failed, then switch back */
		if(m_surface == NULL) m_breakReason = SDL_QUIT; /* If you can't switch back for some reason, then epic fail */
		break;
	case SDLK_0:
		num = '0';
		break;
	case SDLK_1:
		num = '1';
		break;
	default:
		break;
	}

	if (num)
	{
		if ( !m_sampleNum[0] )
			m_sampleNum[0] = num;
		else
		{
			m_sampleNum[1] = num;

			m_curSample = m_sampleNum[0] - 48;
			m_curSample += (m_sampleNum[1] - 48);
			m_sampleNum[0] = m_sampleNum[1] = 0;

			m_OGL_Consumer->setSample(m_curSample-1);
			resizeWindow( 800, 600 );
		}
	}

	SDL_WM_SetCaption(m_OGL_Consumer->getSampleName(), NULL);
}

// Here goes our drawing code
void OGL_Application::drawGLScene()
{
	// These are to calculate our fps
	// static Uint32 T0     = 0;
	// static Uint32 Frames = 0;

	m_OGL_Consumer->drawGLScene();

	/* Draw it to the screen */
	SDL_GL_SwapBuffers( );

	/* // Gather our frames per second
	Frames++;
	{
		Uint32 t = SDL_GetTicks();
		if (t - T0 >= 5000) {
			float seconds = (t - T0) / 1000.0;
			float fps = Frames / seconds;
			// debug output
			 printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
			T0 = t;
			Frames = 0;
		}
	}
	 */
}
