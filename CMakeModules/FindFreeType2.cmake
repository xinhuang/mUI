# Locate FreeType2 Library

SET(FT2_FOUND FALSE)

FIND_PATH(FT2_INCLUDE_DIR ft2build.h
		"${CMAKE_SOURCE_DIR}/dependency/Inc/FreeType2"
		)
		
if (NOT FT2_INCLUDE_DIR)
	message("Cannot find ft2build.h")
endif ()
		
FIND_PATH(FT2_LIBRARY_DIR Debug/freetype245MT_D.lib Release/freetype245MT.lib
		"${CMAKE_SOURCE_DIR}/dependency/Lib"
		)
		
if (NOT FT2_LIBRARY_DIR)
	message("Cannot find freetype245MT_D or freetype245MT")
endif ()

IF (FT2_INCLUDE_DIR AND FT2_LIBRARY_DIR)
	SET(FT2_FOUND TRUE)
ENDIF()
