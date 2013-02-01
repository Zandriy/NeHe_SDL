# it can exclude SDLmain lib on Linux, FMI: read FindSDL.cmake
# SET(SDL_BUILDING_LIBRARY FALSE)

find_package(SDL REQUIRED)

if(NOT SDL_FOUND)
	message( FATAL ERROR "SDL not found!")
endif(NOT SDL_FOUND)

find_package(OpenGL REQUIRED)

if(NOT OPENGL_FOUND)
	message( FATAL ERROR "GL not found!")
endif(NOT OPENGL_FOUND)

IF(APPLE)
	SET(SDL_MAIN_SOURCE SDLMain.m)
ELSE()
	SET(SDL_MAIN_SOURCE)
ENDIF()

SET(NeHe_PROJECT_SOURCE
	prg.cpp
)

SET(NeHe_PROJECT_TARGET prg)

include_directories(
	${SDL_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
	)

link_libraries(
	${SDL_LIBRARY}
	${OPENGL_LIBRARY}
	)

<<<<<<< HEAD
ADD_EXECUTABLE(${SDL_OGL_PROJECT_TARGET} ${SDL_MAIN_SOURCE} ${SDL_OGL_PROJECT_SOURCE})
=======
ADD_EXECUTABLE(${NeHe_PROJECT_TARGET} ${SDL_MAIN_SOURCE} ${NeHe_PROJECT_SOURCE})
>>>>>>> 6d3970dbbe61e23d05e7cad415f013df7f5dde7e

message("============ INFO ============")
message("OS: " ${CMAKE_SYSTEM})
message("PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})
message("SDL INCLUDE: " ${SDL_INCLUDE_DIR})
message("OPENGL INCLUDE: " ${OPENGL_INCLUDE_DIR})
message("SDL LIB: " ${SDL_LIBRARY})
message("OpenGL LIB: " ${OPENGL_LIBRARY})
message("==============================")
message(" !!! always do `pwd -P` before `rm` !!!")
message("==============================")
