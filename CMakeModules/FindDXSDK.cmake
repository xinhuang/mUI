# -*- cmake -*-

#TODO: Add version recognizing here.

if (WIN32)
	find_path(DXSDK_INCLUDE_DIR dxdiag.h
			"$ENV{DXSDK_DIR}/Include"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (March 2009)/Include"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (August 2008)/Include"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (June 2008)/Include"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (March 2008)/Include"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (November 2007)/Include"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (August 2007)/Include"
			"$ENV{PROGRAMFILES}/Microsoft DirectX 9.0 SDK (Summer 2004)/Include"
			"$ENV{PROGRAMFILES}/Microsoft DirectX 9.0 SDK (October 2004)/Include"
			"C:/DX90SDK/Include"
			"$ENV{PROGRAMFILES}/DX90SDK/Include"
			)

	find_path(DXSDK_LIBRARY_DIR dxguid.lib
			"$ENV{DXSDK_DIR}/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (March 2009)/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (August 2008)/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (June 2008)/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (March 2008)/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (November 2007)/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK (August 2007)/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX 9.0 SDK (Summer 2004)/Lib"
			"$ENV{PROGRAMFILES}/Microsoft DirectX 9.0 SDK (October 2004)/Lib"
			"C:/DX90SDK/Lib"
			"$ENV{PROGRAMFILES}/DX90SDK/Lib"
			)
	
	IF (DXSDK_INCLUDE_DIR AND DXSDK_LIBRARY_DIR)
		SET(DXSDK_FOUND TRUE)
	ENDIF()
endif ()
