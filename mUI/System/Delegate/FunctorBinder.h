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

#ifndef __FUNCTORBINDER_H__
#define __FUNCTORBINDER_H__

#define BINDER_ROOT

#define TPL_T_RET_ARG       typename TRet = void, typename TArg0 = void, typename TArg1 = void, typename TArg2 = void
#define TPL_T_ARG           typename TArg0 = void, typename TArg1 = void, typename TArg2 = void
#define T_RET_ARG           TRet, TArg0, TArg1, TArg2
#define T_ARG               TArg0, TArg1, TArg2

#define ARG_DECL            const TArg0& arg0, const TArg1& arg1, const TArg1& arg2
#define ARG                 arg0, arg1, arg2
#define FUN_T_ARG_ARG       TArg0 arg0, TArg1 arg1, TArg2 arg2

#define MEMBER_ARG_DECL     TArg0 arg0_; TArg1 arg1_; TArg2 arg2_
#define MEMBER_ARG          arg0_, arg1_, arg2_
#define MEMBER_ARG_ASSIGN   do { arg0_ = arg0; arg1_ = arg1; arg2_ = arg2; } while (0)
#define ARGUMENTS_EQUAL     args.arg0_ == arg0_ && args.arg1_ == arg1_ && args.arg2_ == arg2_

#define BINDING_ARG         args_.arg0_, args_.arg1_, args_.arg2_

#                           include "FunctorBinderImpl.h"

#undef TPL_T_RET_ARG
#undef TPL_T_ARG
#undef T_RET_ARG
#undef T_ARG 

#undef ARG_DECL 
#undef ARG 
#undef FUN_T_ARG_ARG

#undef MEMBER_ARG_DECL
#undef MEMBER_ARG
#undef MEMBER_ARG_ASSIGN
#undef ARGUMENTS_EQUAL

#undef BINDING_ARG


#undef BINDER_ROOT

// ----------------------------------------------------

#define TPL_T_RET_ARG       typename TRet, typename TArg0, typename TArg1
#define TPL_T_ARG           typename TArg0, typename TArg1
#define T_RET_ARG           TRet, TArg0, TArg1
#define T_ARG               TArg0, TArg1

#define ARG_DECL            const TArg0& arg0, const TArg1& arg1
#define ARG                 arg0, arg1
#define FUN_T_ARG_ARG       TArg0 arg0, TArg1 arg1

#define MEMBER_ARG_DECL     TArg0 arg0_; TArg1 arg1_
#define MEMBER_ARG          arg0_, arg1_
#define MEMBER_ARG_ASSIGN   do { arg0_ = arg0; arg1_ = arg1; } while (0)
#define ARGUMENTS_EQUAL     args.arg0_ == arg0_ && args.arg1_ == arg1_

#define BINDING_ARG         args_.arg0_, args_.arg1_

#                           include "FunctorBinderImpl.h"

#undef TPL_T_RET_ARG
#undef TPL_T_ARG
#undef T_RET_ARG
#undef T_ARG 

#undef ARG_DECL 
#undef ARG 
#undef FUN_T_ARG_ARG

#undef MEMBER_ARG_DECL
#undef MEMBER_ARG
#undef MEMBER_ARG_ASSIGN
#undef ARGUMENTS_EQUAL

#undef BINDING_ARG


#undef BINDER_ROOT

// ----------------------------------------------------

#define TPL_T_RET_ARG typename TRet, typename TArg0
#define TPL_T_ARG typename TArg0
#define T_RET_ARG TRet, TArg0
#define T_ARG TArg0

#define ARG_DECL const TArg0& arg0
#define ARG arg0
#define FUN_T_ARG_ARG TArg0 arg0

#define MEMBER_ARG_DECL TArg0 arg0_
#define MEMBER_ARG arg0_
#define MEMBER_ARG_ASSIGN do { arg0_ = arg0; } while (0)
#define ARGUMENTS_EQUAL args.arg0_ == arg0_

#define BINDING_ARG args_.arg0_

#   include "FunctorBinderImpl.h"

#undef FUNCTOR_ROOT
#undef TPL_T_RET_ARG
#undef TPL_T_ARG
#undef T_RET_ARG
#undef T_ARG 

#undef ARG_DECL 
#undef ARG 
#undef FUN_T_ARG_ARG

#undef MEMBER_ARG_DECL
#undef MEMBER_ARG
#undef MEMBER_ARG_ASSIGN
#undef ARGUMENTS_EQUAL

#undef BINDING_ARG

#endif