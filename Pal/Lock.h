#ifndef __MUIPAL_LOCK_H__
#define __MUIPAL_LOCK_H__

#include "Export.h"
#include "MuiSal.h"
#include "BasicType.h"

namespace mUI{ namespace Pal{

PAL_ENTRY IntPtr NewLock();

PAL_ENTRY void AcquireLock(
	IntPtr Lock);

PAL_ENTRY bool TryAcquireLock(
	IntPtr Lock);

PAL_ENTRY void ReleaseLock(
	IntPtr Lock);

PAL_ENTRY void DeleteLock(
	IntPtr Lock);


}}

#endif // __MUIPAL_LOCK_H__
