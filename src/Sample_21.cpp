/*
 * Sample_21.cpp
 *
 *  Created on: Mar 12, 2013
 *      Author: Andrew Zhabura
 */

#include "Sample_21.h"

#include <SDL/SDL.h>

#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <cmath>

int	Sample_21::s_steps[STEPS]={ 1, 2, 4, 5, 10, 20 };                // Stepping Values For Slow Video Adjustment

Sample_21::Sample_21()
:	m_filled(false)
,	m_gameover(false)
,	m_anti(false)
,	m_delay(0)
,	m_adjust(3)
,	m_lives(5)
,	m_level(1)
,	m_level2(m_level)
,	m_stage(1)
,	m_base(0)
{
	m_imageFont.loadBMP( "data/font_1.bmp" );
	m_imagePict.loadBMP( "data/image.bmp" );

	glGenTextures(TEX_QTY, &m_texture[TEX_1]);                  // Create Two Texture

	m_base = glGenLists( SYM_QTY );

	ResetObjects();
}

Sample_21::~Sample_21()
{
	// Clean up our font list
	glDeleteLists( m_base, SYM_QTY );

	// Clean up our textures
	glDeleteTextures( TEX_QTY, &m_texture[TEX_1] );

#ifdef SOUND
	// Stop playing the music
	Mix_HaltMusic( );

	// Free up the memory for the music
	Mix_FreeMusic( music );

	// Free up any memory for the sfx
	Mix_FreeChunk( chunk );

	// Close our audio device
	Mix_CloseAudio( );

	// Close up the sound sub system
	SDL_QuitSubSystem( SDL_INIT_AUDIO );
#endif
}

void Sample_21::reshape(int w, int h)
{
	if (h==0)                              // Prevent A Divide By Zero By
	{
		h=1;                           // Making h Equal One
	}

	glViewport(0,0,w,h);                       // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                           // Reset The Projection Matrix

	glOrtho(0.0f,w,h,0.0f,-1.0f,1.0f);             // Create Ortho 640x480 View (0,0 At Top Left)

	glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
	glLoadIdentity();                           // Reset The Modelview Matrix
}

void Sample_21::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear Screen And Depth Buffer
	glBindTexture(GL_TEXTURE_2D, m_texture[0]);               // Select Our Font Texture
	glColor3f(1.0f,0.5f,1.0f);                      // Set Color To Purple
	glPrint(207,24,0,(char*)&"GRID CRAZY");                     // Write GRID CRAZY On The Screen
	glColor3f(1.0f,1.0f,0.0f);                      // Set Color To Yellow
	glPrint(20,20,1,(char*)&"Level:%2i",m_level2);                    // Write Actual Level Stats
	glPrint(20,40,1,(char*)&"Stage:%2i",m_stage);                 // Write Stage Stats

	if (m_gameover)                               // Is The Game Over?
	{
		glColor3ub(rand()%255,rand()%255,rand()%255);           // Pick A Random Color
		glPrint(472,20,1,(char*)&"GAME OVER");                  // Write GAME OVER To The Screen
		glPrint(456,40,1,(char*)&"PRESS SPACE");                // Write PRESS SPACE To The Screen
	}
	for (int loop=0; loop<m_lives-1; loop++)                    // Loop Through Lives Minus Current Life
	{
		glLoadIdentity();                       // Reset The View
		glTranslatef(490+(loop*40.0f),40.0f,0.0f);         // Move To The Right Of Our Title Text
		glRotatef(-m_player.spin,0.0f,0.0f,1.0f);             // Rotate Counter Clockwise
		glColor3f(0.0f,1.0f,0.0f);                  // Set Player Color To Light Green
		glBegin(GL_LINES);                      // Start Drawing Our Player Using Lines
		glVertex2d(-5,-5);                  // Top Left Of Player
		glVertex2d( 5, 5);                  // Bottom Right Of Player
		glVertex2d( 5,-5);                  // Top Right Of Player
		glVertex2d(-5, 5);                  // Bottom Left Of Player
		glEnd();                            // Done Drawing The Player
		glRotatef(-m_player.spin*0.5f,0.0f,0.0f,1.0f);            // Rotate Counter Clockwise
		glColor3f(0.0f,0.75f,0.0f);                 // Set Player Color To Dark Green
		glBegin(GL_LINES);                      // Start Drawing Our Player Using Lines
		glVertex2d(-7, 0);                  // Left Center Of Player
		glVertex2d( 7, 0);                  // Right Center Of Player
		glVertex2d( 0,-7);                  // Top Center Of Player
		glVertex2d( 0, 7);                  // Bottom Center Of Player
		glEnd();                            // Done Drawing The Player
	}

	int loop1, loop2;

	m_filled=true;                                // Set Filled To True Before Testing
	glLineWidth(2.0f);                          // Set Line Width For Cells To 2.0f
	glDisable(GL_LINE_SMOOTH);                      // Disable Antialiasing
	glLoadIdentity();                           // Reset The Current Modelview Matrix
	for (loop1=0; loop1<LIN_QTY; loop1++)                 // Loop From Left To Right
	{
		for (loop2=0; loop2<LIN_QTY; loop2++)             // Loop From Top To Bottom
		{
			glColor3f(0.0f,0.5f,1.0f);              // Set Line Color To Blue
			if (m_hline[loop1][loop2])                // Has The Horizontal Line Been Traced
			{
				glColor3f(1.0f,1.0f,1.0f);          // If So, Set Line Color To White
			}
			if (loop1<GAP_QTY)                        // Dont Draw To Far Right
			{
				if (!m_hline[loop1][loop2])           // If A Horizontal Line Isn't Filled
				{
					m_filled=false;               // filled Becomes False
				}
				glBegin(GL_LINES);              // Start Drawing Horizontal Cell Borders
				glVertex2d(20+(loop1*60),70+(loop2*40));    // Left Side Of Horizontal Line
				glVertex2d(80+(loop1*60),70+(loop2*40));    // Right Side Of Horizontal Line
				glEnd();                    // Done Drawing Horizontal Cell Borders
			}
			glColor3f(0.0f,0.5f,1.0f);              // Set Line Color To Blue
			if (m_vline[loop1][loop2])                // Has The Horizontal Line Been Traced
			{
				glColor3f(1.0f,1.0f,1.0f);          // If So, Set Line Color To White
			}
			if (loop2<GAP_QTY)                        // Dont Draw To Far Down
			{
				if (!m_vline[loop1][loop2])           // If A Verticle Line Isn't Filled
				{
					m_filled=false;               // filled Becomes False
				}
				glBegin(GL_LINES);              // Start Drawing Verticle Cell Borders
				glVertex2d(20+(loop1*60),70+(loop2*40));    // Left Side Of Horizontal Line
				glVertex2d(20+(loop1*60),110+(loop2*40));   // Right Side Of Horizontal Line
				glEnd();                    // Done Drawing Verticle Cell Borders
			}
			glEnable(GL_TEXTURE_2D);                // Enable Texture Mapping
			glColor3f(1.0f,1.0f,1.0f);              // Bright White Color
			glBindTexture(GL_TEXTURE_2D, m_texture[1]);       // Select The Tile Image
			if ((loop1<10) && (loop2<10))             // If In Bounds, Fill In Traced Boxes
			{
				// Are All Sides Of The Box Traced?
				if (m_hline[loop1][loop2] && m_hline[loop1][loop2+1] &&
						m_vline[loop1][loop2] && m_vline[loop1+1][loop2])
				{
					glBegin(GL_QUADS);          // Draw A Textured Quad
					glTexCoord2f(float(loop1/10.0f)+0.1f,1.0f-(float(loop2/10.0f)));
					glVertex2d(20+(loop1*60)+59,(70+loop2*40+1));   // Top Right
					glTexCoord2f(float(loop1/10.0f),1.0f-(float(loop2/10.0f)));
					glVertex2d(20+(loop1*60)+1,(70+loop2*40+1));    // Top Left
					glTexCoord2f(float(loop1/10.0f),1.0f-(float(loop2/10.0f)+0.1f));
					glVertex2d(20+(loop1*60)+1,(70+loop2*40)+39);   // Bottom Left
					glTexCoord2f(float(loop1/10.0f)+0.1f,1.0f-(float(loop2/10.0f)+0.1f));
					glVertex2d(20+(loop1*60)+59,(70+loop2*40)+39);  // Bottom Right
					glEnd();                // Done Texturing The Box
				}
			}
			glDisable(GL_TEXTURE_2D);               // Disable Texture Mapping
		}
	}
	glLineWidth(1.0f);                          // Set The Line Width To 1.0f

	if (m_anti)                               // Is Anti TRUE?
	{
		glEnable(GL_LINE_SMOOTH);                   // If So, Enable Antialiasing
	}

	if (m_hourglass.fx==1)                            // If fx=1 Draw The Hourglass
	{
		glLoadIdentity();                       // Reset The Modelview Matrix
		glTranslatef(20.0f+(m_hourglass.x*60),70.0f+(m_hourglass.y*40),0.0f);   // Move To The Fine Hourglass Position
		glRotatef(m_hourglass.spin,0.0f,0.0f,1.0f);           // Rotate Clockwise
		glColor3ub(rand()%255,rand()%255,rand()%255);           // Set Hourglass Color To Random Color

		glBegin(GL_LINES);                      // Start Drawing Our Hourglass Using Lines
		glVertex2d(-5,-5);                  // Top Left Of Hourglass
		glVertex2d( 5, 5);                  // Bottom Right Of Hourglass
		glVertex2d( 5,-5);                  // Top Right Of Hourglass
		glVertex2d(-5, 5);                  // Bottom Left Of Hourglass
		glVertex2d(-5, 5);                  // Bottom Left Of Hourglass
		glVertex2d( 5, 5);                  // Bottom Right Of Hourglass
		glVertex2d(-5,-5);                  // Top Left Of Hourglass
		glVertex2d( 5,-5);                  // Top Right Of Hourglass
		glEnd();                            // Done Drawing The Hourglass
	}

	glLoadIdentity();                           // Reset The Modelview Matrix
	glTranslatef(m_player.fx+20.0f,m_player.fy+70.0f,0.0f);         // Move To The Fine Player Position
	glRotatef(m_player.spin,0.0f,0.0f,1.0f);                  // Rotate Clockwise
	glColor3f(0.0f,1.0f,0.0f);                      // Set Player Color To Light Green
	glBegin(GL_LINES);                          // Start Drawing Our Player Using Lines
	glVertex2d(-5,-5);                      // Top Left Of Player
	glVertex2d( 5, 5);                      // Bottom Right Of Player
	glVertex2d( 5,-5);                      // Top Right Of Player
	glVertex2d(-5, 5);                      // Bottom Left Of Player
	glEnd();                                // Done Drawing The Player

	glRotatef(m_player.spin*0.5f,0.0f,0.0f,1.0f);             // Rotate Clockwise
	glColor3f(0.0f,0.75f,0.0f);                     // Set Player Color To Dark Green
	glBegin(GL_LINES);                          // Start Drawing Our Player Using Lines
	glVertex2d(-7, 0);                      // Left Center Of Player
	glVertex2d( 7, 0);                      // Right Center Of Player
	glVertex2d( 0,-7);                      // Top Center Of Player
	glVertex2d( 0, 7);                      // Bottom Center Of Player
	glEnd();                                // Done Drawing The Player

	for (loop1=0; loop1<(m_stage*m_level); loop1++)              // Loop To Draw Enemies
	{
		glLoadIdentity();                       // Reset The Modelview Matrix
		glTranslatef(m_enemy[loop1].fx+20.0f,m_enemy[loop1].fy+70.0f,0.0f);
		glColor3f(1.0f,0.5f,0.5f);                  // Make Enemy Body Pink
		glBegin(GL_LINES);                      // Start Drawing Enemy
		glVertex2d( 0,-7);                  // Top Point Of Body
		glVertex2d(-7, 0);                  // Left Point Of Body
		glVertex2d(-7, 0);                  // Left Point Of Body
		glVertex2d( 0, 7);                  // Bottom Point Of Body
		glVertex2d( 0, 7);                  // Bottom Point Of Body
		glVertex2d( 7, 0);                  // Right Point Of Body
		glVertex2d( 7, 0);                  // Right Point Of Body
		glVertex2d( 0,-7);                  // Top Point Of Body
		glEnd();                            // Done Drawing Enemy Body

		glRotatef(m_enemy[loop1].spin,0.0f,0.0f,1.0f);            // Rotate The Enemy Blade
		glColor3f(1.0f,0.0f,0.0f);                  // Make Enemy Blade Red
		glBegin(GL_LINES);                      // Start Drawing Enemy Blade
		glVertex2d(-7,-7);                  // Top Left Of Enemy
		glVertex2d( 7, 7);                  // Bottom Right Of Enemy
		glVertex2d(-7, 7);                  // Bottom Left Of Enemy
		glVertex2d( 7,-7);                  // Top Right Of Enemy
		glEnd();                            // Done Drawing Enemy Blade
	}
}

void Sample_21::initGL()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// set here server attributes (states)
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
	glClearDepth(1.0f);                         // Depth Buffer Setup
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);                 // Set Line Antialiasing
	glEnable(GL_BLEND);                         // Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);          // Type Of Blending To Use

	glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
	// set here client attributes (states)

	// Build All The Textures
	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_imageFont.sizeY(), m_imageFont.sizeY(), 0, GL_RGB,
			GL_UNSIGNED_BYTE, m_imageFont.data() );

	glBindTexture(GL_TEXTURE_2D, m_texture[TEX_2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_imagePict.sizeY(), m_imagePict.sizeY(), 0, GL_RGB,
			GL_UNSIGNED_BYTE, m_imagePict.data() );

	buildFont();
}

void Sample_21::restoreGL()
{
	// restore server and client attributes (states)
	glPopClientAttrib();
	glPopAttrib();
}

bool Sample_21::sendMessage(int message, int mode, int x, int y)
{
	bool result = true;

	switch (message) {
	case SDLK_a:
		m_anti=!m_anti;                 // Toggle Antialiasing
		break;
	case SDLK_RIGHT:
	    if ( ( m_player.x < 10 ) && ( m_player.fx == m_player.x * 60 ) &&
		 ( m_player.fy == m_player.y * 40 ) )
		{
		    /* Mark The Current Horizontal Border As Filled */
	    	m_hline[m_player.x][m_player.y] = true;
		    /* Move The Player Right */
	    	m_player.x++;
		}
	    break;
	case SDLK_LEFT:
	    if ( ( m_player.x > 0 ) && ( m_player.fx == m_player.x * 60 ) &&
		 ( m_player.fy == m_player.y * 40 ) )
		{
		    /* Move The Player Left */
	    	m_player.x--;
		    /* Mark The Current Horizontal Border As Filled */
	    	m_hline[m_player.x][m_player.y] = true;
		}
	    break;
	case SDLK_UP:
	    if ( ( m_player.y > 0 ) && (m_player.fx == m_player.x * 60 ) &&
		 ( m_player.fy == m_player.y * 40 ) )
		{
		    /* Move The Player Up */
	    	m_player.y--;
		    /* Mark The Current Vertical Border As Filled */
	    	m_vline[m_player.x][m_player.y] = true;
		}
	    break;
	case SDLK_DOWN:
	    if ( ( m_player.y < 10 ) && ( m_player.fx == m_player.x * 60 ) &&
		 ( m_player.fy == m_player.y * 40 ) )
		{
		    /* Mark The Current Vertical Border As Filled */
	    	m_vline[m_player.x][m_player.y] = true;
		    /* Move The Player Down */
	    	m_player.y++;
		}
	    break;
	case SDLK_SPACE:
	    if ( m_gameover )
		{
	    	m_gameover = false; /* gameover Becomes FALSE             */
	    	m_filled   = true;  /* filled Becomes TRUE                */
	    	m_level    = 1;     /* Starting Level Is Set Back To One  */
	    	m_level2   = 1;     /* Displayed Level Is Also Set To One */
	    	m_stage    = 1;     /* Game Stage Is Set To Zero          */
	    	m_lives    = 5;     /* Lives Is Set To Five               */
		}
	    break;
	default:
		result = false;
		break;
	}

	int loop1, loop2;

	if (!message && !mode && !x && !y && !m_gameover)                // If Game Isn't Over And Programs Active Move Objects
	{
		for (loop1=0; loop1<(m_stage*m_level); loop1++)  // Loop Through The Different Stages
		{
			if ((m_enemy[loop1].x<m_player.x) && (m_enemy[loop1].fy==m_enemy[loop1].y*40))
			{
				m_enemy[loop1].x++;       // Move The Enemy Right
			}

			if ((m_enemy[loop1].x>m_player.x) && (m_enemy[loop1].fy==m_enemy[loop1].y*40))
			{
				m_enemy[loop1].x--;       // Move The Enemy Left
			}

			if ((m_enemy[loop1].y<m_player.y) && (m_enemy[loop1].fx==m_enemy[loop1].x*60))
			{
				m_enemy[loop1].y++;       // Move The Enemy Down
			}

			if ((m_enemy[loop1].y>m_player.y) && (m_enemy[loop1].fx==m_enemy[loop1].x*60))
			{
				m_enemy[loop1].y--;       // Move The Enemy Up
			}
			if (m_delay>(3-m_level) && (m_hourglass.fx!=2))        // If Our Delay Is Done And Player Doesn't Have Hourglass
			{
				m_delay=0;                    // Reset The Delay Counter Back To Zero
				for (loop2=0; loop2<(m_stage*m_level); loop2++)  // Loop Through All The Enemies
				{
					if (m_enemy[loop2].fx<m_enemy[loop2].x*60)   // Is Fine Position On X Axis Lower Than Intended Position?
					{
						m_enemy[loop2].fx+=s_steps[m_adjust]; // If So, Increase Fine Position On X Axis
						m_enemy[loop2].spin+=s_steps[m_adjust];   // Spin Enemy Clockwise
					}
					if (m_enemy[loop2].fx>m_enemy[loop2].x*60)   // Is Fine Position On X Axis Higher Than Intended Position?
					{
						m_enemy[loop2].fx-=s_steps[m_adjust]; // If So, Decrease Fine Position On X Axis
						m_enemy[loop2].spin-=s_steps[m_adjust];   // Spin Enemy Counter Clockwise
					}
					if (m_enemy[loop2].fy<m_enemy[loop2].y*40)   // Is Fine Position On Y Axis Lower Than Intended Position?
					{
						m_enemy[loop2].fy+=s_steps[m_adjust]; // If So, Increase Fine Position On Y Axis
						m_enemy[loop2].spin+=s_steps[m_adjust];   // Spin Enemy Clockwise
					}
					if (m_enemy[loop2].fy>m_enemy[loop2].y*40)   // Is Fine Position On Y Axis Higher Than Intended Position?
					{
						m_enemy[loop2].fy-=s_steps[m_adjust]; // If So, Decrease Fine Position On Y Axis
						m_enemy[loop2].spin-=s_steps[m_adjust];   // Spin Enemy Counter Clockwise
					}
				}
			}
			// Are Any Of The Enemies On Top Of The Player?
			if ((m_enemy[loop1].fx==m_player.fx) && (m_enemy[loop1].fy==m_player.fy))
			{
				m_lives--;            // If So, Player Loses A Life

				if (m_lives==0)           // Are We Out Of Lives?
				{
					m_gameover=true;      // If So, gameover Becomes TRUE
				}

				ResetObjects();         // Reset Player / Enemy Positions
				//PlaySound("Data/Die.wav", NULL, SND_SYNC);  // Play The Death Sound
			}
		}

		if (m_filled)                     // Is The Grid Filled In?
		{
		    //PlaySound("Data/Complete.wav", NULL, SND_SYNC); // If So, Play The Level Complete Sound
			m_stage++;                    // Increase The Stage
		    if (m_stage>3)                 // Is The Stage Higher Than 3?
		    {
		    	m_stage=1;                // If So, Set The Stage To One
		    	m_level++;                // Increase The Level
		    	m_level2++;               // Increase The Displayed Level
		        if (m_level>3)             // Is The Level Greater Than 3?
		        {
		        	m_level=3;            // If So, Set The Level To 3
		        	m_lives++;            // Give The Player A Free Life
		            if (m_lives>5)         // Does The Player Have More Than 5 Lives?
		            {
		            	m_lives=5;        // If So, Set Lives To Five
		            }
		        }
		    }
		    ResetObjects();                 // Reset Player / Enemy Positions

		    for (loop1=0; loop1<11; loop1++)     // Loop Through The Grid X Coordinates
		    {
		        for (loop2=0; loop2<11; loop2++) // Loop Through The Grid Y Coordinates
		        {
		            if (loop1<10)            // If X Coordinate Is Less Than 10
		            {
		            	m_hline[loop1][loop2]=false;  // Set The Current Horizontal Value To FALSE
		            }
		            if (loop2<10)            // If Y Coordinate Is Less Than 10
		            {
		            	m_vline[loop1][loop2]=false;  // Set The Current Vertical Value To FALSE
		            }
		        }
		    }
		}

		// If The Player Hits The Hourglass While It's Being Displayed On The Screen
		if ((m_player.fx==m_hourglass.x*60) && (m_player.fy==m_hourglass.y*40) && (m_hourglass.fx==1))
		{
		    // Play Freeze Enemy Sound
		    //PlaySound("Data/freeze.wav", NULL, SND_ASYNC | SND_LOOP);
			m_hourglass.fx=2;                 // Set The hourglass fx Variable To Two
			m_hourglass.fy=0;                 // Set The hourglass fy Variable To Zero
		}

		m_player.spin+=0.5f*s_steps[m_adjust];            // Spin The Player Clockwise
		if (m_player.spin>360.0f)                  // Is The spin Value Greater Than 360?
		{
			m_player.spin-=360;               // If So, Subtract 360
		}

		m_hourglass.spin-=0.25f*s_steps[m_adjust];            // Spin The Hourglass Counter Clockwise
		if (m_hourglass.spin<0.0f)             // Is The spin Value Less Than 0?
		{
			m_hourglass.spin+=360.0f;             // If So, Add 360
		}

		m_hourglass.fy+=s_steps[m_adjust];                // Increase The hourglass fy Variable
		if ((m_hourglass.fx==0) && (m_hourglass.fy>6000/m_level))  // Is The hourglass fx Variable Equal To 0 And The fy
		{                           // Variable Greater Than 6000 Divided By The Current Level?
		    //PlaySound("Data/hourglass.wav", NULL, SND_ASYNC);   // If So, Play The Hourglass Appears Sound
			m_hourglass.x=rand()%10+1;            // Give The Hourglass A Random X Value
			m_hourglass.y=rand()%11;              // Give The Hourglass A Random Y Value
			m_hourglass.fx=1;                 // Set hourglass fx Variable To One (Hourglass Stage)
			m_hourglass.fy=0;                 // Set hourglass fy Variable To Zero (Counter)
		}

		if ((m_hourglass.fx==1) && (m_hourglass.fy>6000/m_level))  // Is The hourglass fx Variable Equal To 1 And The fy
		{                           // Variable Greater Than 6000 Divided By The Current Level?
			m_hourglass.fx=0;                 // If So, Set fx To Zero (Hourglass Will Vanish)
			m_hourglass.fy=0;                 // Set fy to Zero (Counter Is Reset)
		}

		if ((m_hourglass.fx==2) && (m_hourglass.fy>500+(500*m_level)))// Is The hourglass fx Variable Equal To 2 And The fy
		{                           // Variable Greater Than 500 Plus 500 Times The Current Level?
		    //PlaySound(NULL, NULL, 0);           // If So, Kill The Freeze Sound
			m_hourglass.fx=0;                 // Set hourglass fx Variable To Zero
			m_hourglass.fy=0;                 // Set hourglass fy Variable To Zero
		}

		m_delay++;                        // Increase The Enemy Delay Counter
	}

	drawGLScene();
	return result;
}

void Sample_21::ResetObjects()
{
	m_player.x  = 0; // Reset Player X Position To Far Left Of The Screen
	m_player.y  = 0; // Reset Player Y Position To The Top Of The Screen
	m_player.fx = 0; // Set Fine X Position To Match
	m_player.fy = 0; // Set Fine Y Position To Match

	// Loop Through All The Enemies
	for ( int loop = 0; loop < ( m_stage * m_level ); loop++ )
	{
		// A Random X Position
		m_enemy[loop].x  = 5 + rand( ) % 6;
		// A Random Y Position
		m_enemy[loop].y  = rand( ) % 11;
		// Set Fine X To Match
		m_enemy[loop].fx = m_enemy[loop].x * 60;
		// Set Fine Y To Match
		m_enemy[loop].fy = m_enemy[loop].y * 40;
	}
}

void Sample_21::buildFont()
{
	m_base=glGenLists(SYM_QTY);                           // Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, m_texture[0]);               // Select Our Font Texture
	for (int loop=0; loop<SYM_QTY; loop++)                    // Loop Through All 256 Lists
	{
		float cx=float(loop%16)/16.0f;                 // X Position Of Current Character
		float cy=float(loop/16)/16.0f;                 // Y Position Of Current Character

		glNewList(m_base+loop,GL_COMPILE);               // Start Building A List
		glBegin(GL_QUADS);                  // Use A Quad For Each Character
		glTexCoord2f(cx,1.0f-cy-0.0625f);       // Texture Coord (Bottom Left)
		glVertex2d(0,16);               // Vertex Coord (Bottom Left)
		glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);   // Texture Coord (Bottom Right)
		glVertex2i(16,16);              // Vertex Coord (Bottom Right)
		glTexCoord2f(cx+0.0625f,1.0f-cy);       // Texture Coord (Top Right)
		glVertex2i(16,0);               // Vertex Coord (Top Right)
		glTexCoord2f(cx,1.0f-cy);           // Texture Coord (Top Left)
		glVertex2i(0,0);                // Vertex Coord (Top Left)
		glEnd();                        // Done Building Our Quad (Character)
		glTranslated(15,0,0);                   // Move To The Right Of The Character
		glEndList();                            // Done Building The Display List
	}                                   // Loop Until All 256 Are Built
}

void Sample_21::glPrint(GLint x, GLint y, int set, const char *fmt, ...)         // Where The Printing Happens
{
	char        text[SYM_QTY];                      // Holds Our String
	va_list     ap;                         // Pointer To List Of Arguments

	if (fmt == NULL)                            // If There's No Text
		return;                             // Do Nothing

	va_start(ap, fmt);                          // Parses The String For Variables
	vsprintf(text, fmt, ap);                        // And Converts Symbols To Actual Numbers
	va_end(ap);                             // Results Are Stored In Text

	if (set>1)                               // Did User Choose An Invalid Character Set?
	{
		set=1;                              // If So, Select Set 1 (Italic)
	}
	glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping
	glLoadIdentity();                           // Reset The Modelview Matrix
	glTranslated(x,y,0);                            // Position The Text (0,0 - Bottom Left)
	glListBase(m_base-FIRST_SYM+(SYM_QTY/2 * set));                      // Choose The Font Set (0 or 1)

	if (set==0)                             // If Set 0 Is Being Used Enlarge Font
	{
		glScalef(1.5f,2.0f,1.0f);                   // Enlarge Font Width And Height
	}

	glCallLists(strlen(text),GL_UNSIGNED_BYTE, text);           // Write The Text To The Screen
	glDisable(GL_TEXTURE_2D);                       // Disable Texture Mapping
}
