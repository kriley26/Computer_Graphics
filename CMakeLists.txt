cmake_minimum_required (VERSION 3.16)

project (test_sdl)

if(WIN32)
	set(BUILD_MS_WINDOWS 1)
elseif(APPLE)
	set(BUILD_MACOS 1)
elseif(UNIX AND NOT APPLE)
	set(BUILD_LINUX 1)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DRESOURCE_DIR=${CMAKE_SOURCE_DIR}/resources/)

if(BUILD_MS_WINDOWS)
	find_library(SDL_LIB NAMES SDL2 PATHS ${CMAKE_SOURCE_DIR}/lib/win/SDL2-2.0.20/lib/x64)
	find_library(SDL_MAIN_LIB NAMES SDL2main PATHS ${CMAKE_SOURCE_DIR}/lib/win/SDL2-2.0.20/lib/x64)
	find_library(SDL_IMAGE_LIB NAMES SDL2_image PATHS ${CMAKE_SOURCE_DIR}/lib/win/SDL2_image-2.0.5/lib/x64)
	find_library(SDL_MIXER_LIB NAMES SDL2_mixer PATHS ${CMAKE_SOURCE_DIR}/lib/win/SDL2_mixer-2.0.4/lib/x64)
	find_path(SDL_INCLUDES SDL.h ${CMAKE_SOURCE_DIR}/lib/win/SDL2-2.0.20/include)
	find_path(SDL_IMAGE_INCLUDES SDL_image.h ${CMAKE_SOURCE_DIR}/lib/win/SDL2_image-2.0.5/include)
	find_path(SDL_MIXER_INCLUDES SDL_mixer.h ${CMAKE_SOURCE_DIR}/lib/win/SDL2_mixer-2.0.4/include)
elseif(BUILD_MACOS)
	find_library(SDL_LIB NAMES SDL2)
	find_library(SDL_IMAGE_LIB NAMES SDL2_image)
	find_library(SDL_MIXER_LIB NAMES SDL2_mixer)
	include_directories(/usr/local/include)
elseif(BUILD_LINUX)
	find_library(SDL_LIB NAMES libSDL2.so)
	find_library(SDL_MAIN_LIB NAMES libSDL2main.a)
	find_library(SDL_IMAGE_LIB NAMES libSDL2_image.so)
	find_library(SDL_MIXER_LIB NAMES libSDL2_mixer.so)
	find_path(SDL_INCLUDES SDL.h /usr/include/SDL2)
	find_library(PTHREAD_LIBRARY NAMES pthread)
endif()

#include_directories(${SDL_INCLUDES}/../../)
#include_directories(${SDL_IMAGE_INCLUDES})
include_directories(${CMAKE_SOURCE_DIR})
#include_directories(/usr/local/include)

file(GLOB SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})

if(BUILD_MS_WINDOWS)
	target_link_libraries(
		${PROJECT_NAME} PRIVATE
		${SDL_LIB}
		${SDL_MAIN_LIB}
		${SDL_IMAGE_LIB}
		${SDL_MIXER_LIB}
		${CMAKE_DL_LIBS} 
		${PTHREAD_LIBRARY})

	file(GLOB SDL_DLLS 
		${CMAKE_SOURCE_DIR}/lib/win/SDL2-2.0.20/lib/x64/*.dll
		${CMAKE_SOURCE_DIR}/lib/win/SDL2_image-2.0.5/lib/x64/*.dll
		${CMAKE_SOURCE_DIR}/lib/win/SDL2_mixer-2.0.4/lib/x64/*.dll
	)
	foreach( file_i ${SDL_DLLS})
		add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy  
			${file_i}
			$<TARGET_FILE_DIR:${PROJECT_NAME}>)
	endforeach( file_i )
else()
	target_link_libraries(
		${PROJECT_NAME} PRIVATE
		${SDL_LIB}
		${SDL_IMAGE_LIB} 
		${SDL_MIXER_LIB} 
		${CMAKE_DL_LIBS} 
		${PTHREAD_LIBRARY})
endif()
