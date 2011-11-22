# Locate GTest Library

SET(GTEST_FOUND FALSE)

if (WIN32)
	find_path(GTEST_INCLUDE_DIR gtest.h
			"${CMAKE_SOURCE_DIR}/dependency/include/gtest"
			)

	find_path(GTEST_LIBRARY_DIR 
			NAMES gtest.lib gtest_main.lib
			HINTS
			"${CMAKE_SOURCE_DIR}/dependency/lib/gtest"
			)
	
	IF (GTEST_INCLUDE_DIR AND GTEST_LIBRARY_DIR)
		SET(GTEST_FOUND TRUE)
	ENDIF()
endif ()
