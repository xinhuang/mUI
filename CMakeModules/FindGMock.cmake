# Locate GMock Library

SET(GMOCK_FOUND FALSE)

if (WIN32)
	find_path(GMOCK_INCLUDE_DIR gmock/gmock.h
			"${CMAKE_SOURCE_DIR}/dependency/Inc"
			)

	find_path(GMOCK_LIBRARY_DIR 
			NAMES 
				Debug/gmock.lib Debug/gmock_main.lib 
				Release/gmock.lib Release/gmock_main.lib
			HINTS
			"${CMAKE_SOURCE_DIR}/dependency/Lib"
			)
	
	IF (GMOCK_INCLUDE_DIR AND GMOCK_LIBRARY_DIR)
		SET(GMOCK_FOUND TRUE)
		SET(GMOCK_INCLUDE_DIR "${GMOCK_INCLUDE_DIR}")
	ENDIF()
endif ()
