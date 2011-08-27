#ifndef __MUIMUISAL_H__
#define __MUIMUISAL_H__

#if defined _WINDOWS || defined WIN32
#	include <sal.h>
#else
#	define __in
#	define __out
#	define __in_opt
#	define __deref
#	define __drv_aliasesMem
#endif

#endif // __MUIMUISAL_H__