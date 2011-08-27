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

#ifndef __FUNCTORBINDER10_H__
#define __FUNCTORBINDER10_H__

#include "Functor.h"

namespace mUI{ namespace System{

	template<
		typename TArg0 = void, 
		typename TArg1 = void, 
		typename TArg2 = void, 
		typename TArg3 = void, 
		typename TArg4 = void, 
		typename TArg5 = void, 
		typename TArg6 = void, 
		typename TArg7 = void, 
		typename TArg8 = void, 
		typename TArg9 = void>
	struct Arguments
	{
		Arguments(TArg0 a0, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4,
			TArg5 a5, TArg6 a6, TArg7 a7, TArg8 a8, TArg9 a9) 
			: arg0(a0), arg1(a1), arg2(a2), arg3(a3), arg4(a4), 
			arg5(a5), arg6(a6), arg7(a7), arg8(a8), arg9(a9)
		{}

		virtual bool operator== (const Arguments<TArg0, TArg1, TArg2, TArg3, TArg4, 
												TArg5, TArg6, TArg7, TArg8, TArg9>& args) const
		{
			return args.arg0 == arg0
				&& args.arg1 == arg1
				&& args.arg2 == arg2
				&& args.arg3 == arg3
				&& args.arg4 == arg4
				&& args.arg5 == arg5
				&& args.arg6 == arg6
				&& args.arg7 == arg7
				&& args.arg8 == arg8
				&& args.arg9 == arg9;
		}

		TArg0 arg0;
		TArg1 arg1;
		TArg2 arg2;
		TArg3 arg3;
		TArg4 arg4;
		TArg5 arg5;
		TArg6 arg6;
		TArg7 arg7;
		TArg8 arg8;
		TArg9 arg9;
	};

	template<typename TRet = void,
		typename TArg0 = void, 
		typename TArg1 = void, 
		typename TArg2 = void, 
		typename TArg3 = void, 
		typename TArg4 = void, 
		typename TArg5 = void, 
		typename TArg6 = void, 
		typename TArg7 = void, 
		typename TArg8 = void, 
		typename TArg9 = void>
	class FunctorBinder : 
		public Functor<TRet>
	{
	public:
		FunctorBinder(const Functor<TRet, 
			TArg0, TArg1, TArg2, TArg3, TArg4, 
			TArg5, TArg6, TArg7, TArg8, TArg9>& f, 
			const TArg0& arg0, const TArg1& arg1, const TArg2& arg2, const TArg3& arg3, const TArg4& arg4,
			const TArg5& arg5, const TArg6& arg6, const TArg7& arg7, const TArg8& arg8, const TArg9& arg9)
			: functor_(f.Clone()), args_(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)
		{}
		template<typename TClass>
		FunctorBinder(TClass& c, TRet (TClass::*F)(TArg0, TArg1, TArg2, TArg3, TArg4,
													TArg5, TArg6, TArg7, TArg8, TArg9), 
			const TArg0& arg0, const TArg1& arg1, const TArg2& arg2, const TArg3& arg3, const TArg4& arg4,
			const TArg5& arg5, const TArg6& arg6, const TArg7& arg7, const TArg8& arg8, const TArg9& arg9)
			: args_(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)
		{
			functor_ = new MemberFunctor<TClass, TRet, 
				TArg0, TArg1, TArg2, TArg3, TArg4, 
				TArg5, TArg6, TArg7, TArg8, TArg9>(c, F);
			assert(functor_ != NULL);
		}

		~FunctorBinder()
		{
			delete functor_;
			functor_ = NULL;
		}

		virtual TRet operator() ()
		{
			return (*functor_)(
				args_.arg0, 
				args_.arg1, 
				args_.arg2, 
				args_.arg3, 
				args_.arg4, 
				args_.arg5, 
				args_.arg6, 
				args_.arg7, 
				args_.arg8, 
				args_.arg9
				);
		}
		virtual bool operator== (const Functor<TRet>& rhs) const
		{
			if (&rhs == this)
				return true;
			else
			{
				const FunctorBinder<TRet, 
					TArg0, TArg1, TArg2, TArg3, TArg4, 
					TArg5, TArg6, TArg7, TArg8, TArg9>* fb = 
					dynamic_cast<const FunctorBinder<TRet, 
					TArg0, TArg1, TArg2, TArg3, TArg4, 
					TArg5, TArg6, TArg7, TArg8, TArg9>*>(&rhs);
				if (fb)
				{
					return (fb->args_) == args_ && *fb->functor_ == *functor_;
				}
			}
			return false;
		}
		virtual Functor<TRet>* Clone() const
		{
			return new FunctorBinder(*functor_, 
				args_.arg0, args_.arg1, args_.arg2, args_.arg3, args_.arg4,
				args_.arg5, args_.arg6, args_.arg7, args_.arg8, args_.arg9);
		}

	private:
		Functor<TRet, TArg0, TArg1, TArg2, TArg3, TArg4,
			TArg5, TArg6, TArg7, TArg8, TArg9>* functor_;
		Arguments<TArg0, TArg1, TArg2, TArg3, TArg4, 
			TArg5, TArg6, TArg7, TArg8, TArg9> args_;
	};

}}

#endif