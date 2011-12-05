# Locate GMock Library

SET(GMOCK_FOUND FALSE)

if (WIN32)
	find_path(GMOCK_INCLUDE_DIR gmock.h
			"${CMAKE_SOURCE_DIR}/dependency/include/gmock"
			)

	find_path(GMOCK_LIBRARY_DIR 
			NAMES gmock.lib gmock_main.lib
			HINTS
			"${CMAKE_SOURCE_DIR}/dependency/lib/gmock"
			)
	
	IF (GMOCK_INCLUDE_DIR AND GMOCK_LIBRARY_DIR)
		SET(GMOCK_FOUND TRUE)
		SET(GMOCK_INCLUDE_DIR "${GMOCK_INCLUDE_DIR}")
	ENDIF()
endif ()
