/*
	Copyright 2011 hello.patz@gmail.com

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#ifndef __DELEGATE_H__
#define __DELEGATE_H__

#include "../Export.h"

#include "Functor.h"
#include "MemberFunctor.h"
#include "FunctorBinder.h"

#include <vector>
using std::vector;

#include <cassert>

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif

// -------------------------------------------------------- //

#define TPL_RET_ARGLIST	typename TRet = void, \
	typename TArg0 = void, \
	typename TArg1 = void, \
	typename TArg2 = void, \
	typename TArg3 = void, \
	typename TArg4 = void, \
	typename TArg5 = void, \
	typename TArg6 = void, \
	typename TArg7 = void, \
	typename TArg8 = void, \
	typename TArg9 = void
#define TPL_ARGLIST	\
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4, \
	typename TArg5, \
	typename TArg6, \
	typename TArg7, \
	typename TArg8, \
	typename TArg9
#define RET_ARGLIST TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9
#define T_ARGLIST TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9
#define ARGLIST arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9
#define FUN_ARGLIST	TArg0 arg0, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, \
	TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9

#	include "DelegateRoot.h"

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST


// --------------------------------------------------- //

#define TPL_RET_ARGLIST	typename TRet,  \
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4, \
	typename TArg5, \
	typename TArg6, \
	typename TArg7, \
	typename TArg8
#define TPL_ARGLIST	\
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4, \
	typename TArg5, \
	typename TArg6, \
	typename TArg7, \
	typename TArg8
#define RET_ARGLIST TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8
#define T_ARGLIST TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8
#define ARGLIST arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8
#define FUN_ARGLIST	TArg0 arg0, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, \
	TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8 

#	include "DelegateSpec.h"

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST

// --------------------------------------------------- //

#define TPL_RET_ARGLIST	typename TRet,  \
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4, \
	typename TArg5, \
	typename TArg6, \
	typename TArg7
#define TPL_ARGLIST	\
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4, \
	typename TArg5, \
	typename TArg6, \
	typename TArg7
#define RET_ARGLIST TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7
#define T_ARGLIST TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7
#define ARGLIST arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7
#define FUN_ARGLIST	TArg0 arg0, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, \
	TArg5 arg5, TArg6 arg6, TArg7 arg7

#	include "DelegateSpec.h"

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST

// --------------------------------------------------- //

#define TPL_RET_ARGLIST	typename TRet,  \
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4, \
	typename TArg5, \
	typename TArg6
#define TPL_ARGLIST	\
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4, \
	typename TArg5, \
	typename TArg6
#define RET_ARGLIST TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6
#define T_ARGLIST TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6
#define ARGLIST arg0, arg1, arg2, arg3, arg4, arg5, arg6
#define FUN_ARGLIST	TArg0 arg0, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, \
	TArg5 arg5, TArg6 arg6

#	include "DelegateSpec.h"

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST

// --------------------------------------------------- //

#define TPL_RET_ARGLIST	typename TRet,  \
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4, \
	typename TArg5
#define TPL_ARGLIST	\
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4, \
	typename TArg5
#define RET_ARGLIST TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5
#define T_ARGLIST TArg0, TArg1, TArg2, TArg3, TArg4, TArg5
#define ARGLIST arg0, arg1, arg2, arg3, arg4, arg5
#define FUN_ARGLIST	TArg0 arg0, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, \
	TArg5 arg5

#	include "DelegateSpec.h"

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST

// --------------------------------------------------- //

#define TPL_RET_ARGLIST	typename TRet,  \
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4
#define TPL_ARGLIST	\
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4
#define RET_ARGLIST TRet, TArg0, TArg1, TArg2, TArg3, TArg4
#define T_ARGLIST TArg0, TArg1, TArg2, TArg3, TArg4
#define ARGLIST arg0, arg1, arg2, arg3, arg4
#define FUN_ARGLIST	TArg0 arg0, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4

#	include "DelegateSpec.h"

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST

// --------------------------------------------------- //

#define TPL_RET_ARGLIST	typename TRet,  \
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3
#define TPL_ARGLIST	\
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3
#define RET_ARGLIST TRet, TArg0, TArg1, TArg2, TArg3
#define T_ARGLIST TArg0, TArg1, TArg2, TArg3
#define ARGLIST arg0, arg1, arg2, arg3
#define FUN_ARGLIST	TArg0 arg0, TArg1 arg1, TArg2 arg2, TArg3 arg3

#	include "DelegateSpec.h"

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST

// --------------------------------------------------- //

#define TPL_RET_ARGLIST	typename TRet,  \
	typename TArg0, \
	typename TArg1, \
	typename TArg2
#define TPL_ARGLIST	\
	typename TArg0, \
	typename TArg1, \
	typename TArg2
#define RET_ARGLIST TRet, TArg0, TArg1, TArg2
#define T_ARGLIST TArg0, TArg1, TArg2
#define ARGLIST arg0, arg1, arg2
#define FUN_ARGLIST	TArg0 arg0, TArg1 arg1, TArg2 arg2

#	include "DelegateSpec.h"

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST

// --------------------------------------------------- //

#define TPL_RET_ARGLIST typename TRet, typename TArg0, typename TArg1
#define TPL_ARGLIST typename TArg0, typename TArg1
#define RET_ARGLIST TRet, TArg0, TArg1
#define T_ARGLIST TArg0, TArg1
#define ARGLIST arg0, arg1
#define FUN_ARGLIST TArg0 arg0, TArg1 arg1

#	include "DelegateSpec.h"

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST

// --------------------------------------------------- //

#define TPL_RET_ARGLIST typename TRet, typename TArg0
#define TPL_ARGLIST typename TArg0
#define RET_ARGLIST TRet, TArg0
#define T_ARGLIST TArg0
#define ARGLIST arg0
#define FUN_ARGLIST TArg0 arg0

#	include "DelegateSpec.h"

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST

// --------------------------------------------------- //

#include "DelegateNoArg.h"

#include "EventHandler.h"

// --------------------------------------------------- //

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif
