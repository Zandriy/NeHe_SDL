# it can exclude SDLmain lib on Linux, FMI: read FindSDL.cmake
# SET(SDL_BUILDING_LIBRARY FALSE)

find_package(SDL REQUIRED)

if(NOT SDL_FOUND)
	message( FATAL ERROR "SDL not found!")
endif(NOT SDL_FOUND)

find_package(SDL_mixer REQUIRED)

if(NOT SDLMIXER_FOUND)
	message( FATAL ERROR "SDL MIXER not found!")
endif(NOT SDLMIXER_FOUND)

find_package(OpenGL REQUIRED)

if(NOT OPENGL_FOUND)
	message( FATAL ERROR "OpenGL not found!")
endif(NOT OPENGL_FOUND)

IF(APPLE)
	SET(SDL_MAIN_SOURCE SDLMain.m)
ELSE()
	SET(SDL_MAIN_SOURCE)
ENDIF()

SET(NeHe_PROJECT_SOURCE
	prg.cpp
	OGLApplication.cpp
	OGLConsumer.cpp
	OGLInspector.cpp
	Sample_01.cpp
	Sample_02.cpp
	Sample_03.cpp
	Sample_04.cpp
	Sample_05.cpp
	Sample_06.cpp
	Sample_07.cpp
	Sample_08.cpp
	Sample_09.cpp
	Sample_10.cpp
	Sample_11.cpp
	Sample_12.cpp
	Sample_13.cpp
	Sample_14.cpp
	
	Sample_16.cpp
	Sample_17.cpp
	Sample_18.cpp
	Sample_19.cpp
	Sample_20.cpp
	Sample_21.cpp
	Sample_22.cpp
	Sample_23.cpp
)

SET(NeHe_PROJECT_TARGET prg)

include_directories(
	${SDL_INCLUDE_DIR}
	${SDLMIXER_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
	)

link_libraries(
	${SDL_LIBRARY}
	${SDLMIXER_LIBRARY}
	${OPENGL_LIBRARY}
	)

ADD_EXECUTABLE(${NeHe_PROJECT_TARGET} ${SDL_MAIN_SOURCE} ${NeHe_PROJECT_SOURCE})

message("============ INFO ============")
message("OS: " ${CMAKE_SYSTEM})
message("PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})
message("SDL INCLUDE: " ${SDL_INCLUDE_DIR})
message("SDL MIXER INCLUDE: " ${SDLMIXER_INCLUDE_DIR})
message("OPENGL INCLUDE: " ${OPENGL_INCLUDE_DIR})
message("SDL LIB: " ${SDL_LIBRARY})
message("SDL MIXER LIB: " ${SDLMIXER_LIBRARY})
message("OpenGL LIB: " ${OPENGL_LIBRARY})
message("==============================")
message(" !!! always do `pwd -P` before `rm` !!!")
message(" !!! always do `ls` before `rm` to see what will be removed !!!")
message("==============================")
