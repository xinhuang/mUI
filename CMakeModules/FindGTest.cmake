# Locate GTest Library

SET(GTEST_FOUND FALSE)

if (WIN32)
	find_path(GTEST_INCLUDE_DIR gtest/gtest.h
			"${CMAKE_SOURCE_DIR}/dependency/inc"
			)

	find_path(GTEST_LIBRARY_DIR 
			NAMES 
				Debug/gtest.lib Release/gtest.lib
			HINTS
			"${CMAKE_SOURCE_DIR}/dependency/lib"
			)
	
	IF (GTEST_INCLUDE_DIR AND GTEST_LIBRARY_DIR)
		SET(GTEST_FOUND TRUE)
		SET(GTEST_INCLUDE_DIR "${GTEST_INCLUDE_DIR}")
	ENDIF()
endif ()
