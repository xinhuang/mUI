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

#ifndef __MEMBERFUNCTOR_H__
#define __MEMBERFUNCTOR_H__

namespace mUI{ namespace System{

// --------------------------------------------------------------
	
#define TPL_TYPENAME typename TClass, typename TRet = void,	\
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
#define T_CLASS_RET_ARGS TClass, TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, \
										TArg6, TArg7, TArg8, TArg9
#define T_RET_ARGS TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9
#define T_ARGS TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9
#define FUN_T_ARGS TArg0 a0, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4, TArg5 a5, \
						TArg6 a6, TArg7 a7, TArg8 a8, TArg9 a9
#define ARGS a0, a1, a2, a3, a4, a5, a6, a7, a8, a9
#define MEMBERFUNCTOR_ROOT

#include "MemberFunctorImpl.h"

#undef MEMBERFUNCTOR_ROOT
#undef TPL_TYPENAME
#undef T_CLASS_RET_ARGS
#undef T_RET_ARGS
#undef T_ARGS 
#undef FUN_T_ARGS 
#undef ARGS
	
// --------------------------------------------------------------
	
#define TPL_TYPENAME typename TClass, typename TRet,	\
										typename TArg0, \
										typename TArg1, \
										typename TArg2, \
										typename TArg3, \
										typename TArg4, \
										typename TArg5, \
										typename TArg6, \
										typename TArg7, \
										typename TArg8
#define T_CLASS_RET_ARGS TClass, TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, \
										TArg6, TArg7, TArg8
#define T_RET_ARGS TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8
#define T_ARGS TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8
#define FUN_T_ARGS TArg0 a0, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4, TArg5 a5, \
						TArg6 a6, TArg7 a7, TArg8 a8
#define ARGS a0, a1, a2, a3, a4, a5, a6, a7, a8

#include "MemberFunctorImpl.h"

#undef TPL_TYPENAME
#undef T_CLASS_RET_ARGS
#undef T_RET_ARGS
#undef T_ARGS 
#undef FUN_T_ARGS 
#undef ARGS

// --------------------------------------------------------------
	
#define TPL_TYPENAME typename TClass, typename TRet,	\
										typename TArg0, \
										typename TArg1, \
										typename TArg2, \
										typename TArg3, \
										typename TArg4, \
										typename TArg5, \
										typename TArg6, \
										typename TArg7
#define T_CLASS_RET_ARGS TClass, TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, \
										TArg6, TArg7
#define T_RET_ARGS TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7
#define T_ARGS TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7
#define FUN_T_ARGS TArg0 a0, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4, TArg5 a5, \
						TArg6 a6, TArg7 a7
#define ARGS a0, a1, a2, a3, a4, a5, a6, a7

#include "MemberFunctorImpl.h"

#undef TPL_TYPENAME
#undef T_CLASS_RET_ARGS
#undef T_RET_ARGS
#undef T_ARGS 
#undef FUN_T_ARGS 
#undef ARGS
	
// --------------------------------------------------------------
	
#define TPL_TYPENAME typename TClass, typename TRet,	\
										typename TArg0, \
										typename TArg1, \
										typename TArg2, \
										typename TArg3, \
										typename TArg4, \
										typename TArg5, \
										typename TArg6
#define T_CLASS_RET_ARGS TClass, TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, \
										TArg6
#define T_RET_ARGS TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6
#define T_ARGS TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6
#define FUN_T_ARGS TArg0 a0, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4, TArg5 a5, \
						TArg6 a6
#define ARGS a0, a1, a2, a3, a4, a5, a6

#include "MemberFunctorImpl.h"

#undef TPL_TYPENAME
#undef T_CLASS_RET_ARGS
#undef T_RET_ARGS
#undef T_ARGS 
#undef FUN_T_ARGS 
#undef ARGS
	
// --------------------------------------------------------------
	
#define TPL_TYPENAME typename TClass, typename TRet,	\
										typename TArg0, \
										typename TArg1, \
										typename TArg2, \
										typename TArg3, \
										typename TArg4, \
										typename TArg5
#define T_CLASS_RET_ARGS TClass, TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5
#define T_RET_ARGS TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5
#define T_ARGS TArg0, TArg1, TArg2, TArg3, TArg4, TArg5
#define FUN_T_ARGS TArg0 a0, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4, TArg5 a5
#define ARGS a0, a1, a2, a3, a4, a5

#include "MemberFunctorImpl.h"

#undef TPL_TYPENAME
#undef T_CLASS_RET_ARGS
#undef T_RET_ARGS
#undef T_ARGS 
#undef FUN_T_ARGS 
#undef ARGS
	
// --------------------------------------------------------------
	
#define TPL_TYPENAME typename TClass, typename TRet,	\
										typename TArg0, \
										typename TArg1, \
										typename TArg2, \
										typename TArg3, \
										typename TArg4
#define T_CLASS_RET_ARGS TClass, TRet, TArg0, TArg1, TArg2, TArg3, TArg4
#define T_RET_ARGS TRet, TArg0, TArg1, TArg2, TArg3, TArg4
#define T_ARGS TArg0, TArg1, TArg2, TArg3, TArg4
#define FUN_T_ARGS TArg0 a0, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4
#define ARGS a0, a1, a2, a3, a4

#include "MemberFunctorImpl.h"

#undef TPL_TYPENAME
#undef T_CLASS_RET_ARGS
#undef T_RET_ARGS
#undef T_ARGS 
#undef FUN_T_ARGS 
#undef ARGS
	
// --------------------------------------------------------------
	
#define TPL_TYPENAME typename TClass, typename TRet,	\
										typename TArg0, \
										typename TArg1, \
										typename TArg2, \
										typename TArg3
#define T_CLASS_RET_ARGS TClass, TRet, TArg0, TArg1, TArg2, TArg3
#define T_RET_ARGS TRet, TArg0, TArg1, TArg2, TArg3
#define T_ARGS TArg0, TArg1, TArg2, TArg3
#define FUN_T_ARGS TArg0 a0, TArg1 a1, TArg2 a2, TArg3 a3
#define ARGS a0, a1, a2, a3

#include "MemberFunctorImpl.h"

#undef TPL_TYPENAME
#undef T_CLASS_RET_ARGS
#undef T_RET_ARGS
#undef T_ARGS 
#undef FUN_T_ARGS 
#undef ARGS

// --------------------------------------------------------------
	
#define TPL_TYPENAME typename TClass, typename TRet, typename TArg0, typename TArg1, typename TArg2
#define T_CLASS_RET_ARGS TClass, TRet, TArg0, TArg1, TArg2
#define T_RET_ARGS TRet, TArg0, TArg1, TArg2
#define T_ARGS TArg0, TArg1, TArg2
#define FUN_T_ARGS TArg0 a0, TArg1 a1, TArg2 a2
#define ARGS a0, a1, a2

#include "MemberFunctorImpl.h"

#undef TPL_TYPENAME
#undef T_CLASS_RET_ARGS
#undef T_RET_ARGS
#undef T_ARGS 
#undef FUN_T_ARGS 
#undef ARGS

// --------------------------------------------------------------
	
#define TPL_TYPENAME typename TClass, typename TRet, typename TArg0, typename TArg1
#define T_CLASS_RET_ARGS TClass, TRet, TArg0, TArg1
#define T_RET_ARGS TRet, TArg0, TArg1
#define T_ARGS TArg0, TArg1
#define FUN_T_ARGS TArg0 a0, TArg1 a1
#define ARGS a0, a1

#include "MemberFunctorImpl.h"

#undef TPL_TYPENAME
#undef T_CLASS_RET_ARGS
#undef T_RET_ARGS
#undef T_ARGS 
#undef FUN_T_ARGS 
#undef ARGS
	
// --------------------------------------------------------------

#define TPL_TYPENAME typename TClass, typename TRet, typename TArg0
#define T_CLASS_RET_ARGS TClass, TRet, TArg0
#define T_RET_ARGS TRet, TArg0
#define T_ARGS TArg0
#define FUN_T_ARGS TArg0 a0
#define ARGS a0

#include "MemberFunctorImpl.h"

#undef TPL_TYPENAME
#undef T_CLASS_RET_ARGS
#undef T_RET_ARGS
#undef T_ARGS 
#undef FUN_T_ARGS 
#undef ARGS
	
// --------------------------------------------------------------

#define TPL_TYPENAME typename TClass, typename TRet
#define T_CLASS_RET_ARGS TClass, TRet
#define T_RET_ARGS TRet
#define T_ARGS 
#define FUN_T_ARGS
#define ARGS 

#include "MemberFunctorImpl.h"

#undef TPL_TYPENAME
#undef T_CLASS_RET_ARGS
#undef T_RET_ARGS
#undef T_ARGS 
#undef FUN_T_ARGS 
#undef ARGS

}}

#ifndef NDEBUG

namespace {

class Test
{
public:
	void foo() {};
	void foo(int) {};
	void foo(int, int) {};
	void foo(int, int, int) {};
	void foo(int, int, int, int) {};
	void foo(int, int, int, int, int) {};
	void foo(int, int, int, int, int, int) {};
	void foo(int, int, int, int, int, int, int) {};
	void foo(int, int, int, int, int, int, int, int) {};
	void foo(int, int, int, int, int, int, int, int, int) {};
	void foo(int, int, int, int, int, int, int, int, int, int) {};
	void foo(int, int, int, int, int, int, int, int, int, int, int) {};
};

Test t;
mUI::System::MemberFunctor<Test, void>					a0(t, &Test::foo);
mUI::System::MemberFunctor<Test, void, int>				a1(t, &Test::foo);
mUI::System::MemberFunctor<Test, void, int, int>		a2(t, &Test::foo);
mUI::System::MemberFunctor<Test, void, int, int, int>	a3(t, &Test::foo);
mUI::System::MemberFunctor<Test, void, int, int, int, int>	a4(t, &Test::foo);
mUI::System::MemberFunctor<Test, void, int, int, int, int, int>	a5(t, &Test::foo);
mUI::System::MemberFunctor<Test, void, int, int, int, int, int, int>	a6(t, &Test::foo);
mUI::System::MemberFunctor<Test, void, int, int, int, int, int, int, int>	a7(t, &Test::foo);
mUI::System::MemberFunctor<Test, void, int, int, int, int, int, int, int, int>	a8(t, &Test::foo);
mUI::System::MemberFunctor<Test, void, int, int, int, int, int, int, int, int, int>	a9(t, &Test::foo);
mUI::System::MemberFunctor<Test, void, int, int, int, int, int, int, int, int, int, int>	a10(t, &Test::foo);

}

#endif // NDEBUG

#endif //  __MEMBERFUNCTOR_H__
