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

#ifndef __MEMBERFUNCTOR10_H__
#define __MEMBERFUNCTOR10_H__

#include "Functor.h"

namespace mUI{ namespace System{

	// ----------------------------------------------------------------
	// 10 Arguments
	template <typename TClass,
		typename TRet = void,
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
	class MemberFunctor : public Functor<TRet, TArg0, TArg1, TArg2, TArg3, TArg4, 
		TArg5, TArg6, TArg7, TArg8, TArg9>
	{
	public:
		typedef TRet (TClass::*Func)(TArg0, TArg1, TArg2, TArg3, TArg4, 
			TArg5, TArg6, TArg7, TArg8, TArg9);

		MemberFunctor(TClass& C, Func F) : c(C), f(F)
		{}

		virtual TRet operator() (TArg0 a0, TArg1 a1, TArg2 a2, TArg3 a3, TArg4 a4,
			TArg5 a5, TArg6 a6, TArg7 a7, TArg8 a8, TArg9 a9)
		{ return (c.*f)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9); }

		virtual bool operator== (const Functor<TRet, TArg0, TArg1, TArg2, TArg3, TArg4, 
			TArg5, TArg6, TArg7, TArg8, TArg9>& rhs) const
		{
			if (&rhs == this)
				return true;
			else
			{
				const MemberFunctor<TClass, TRet, TArg0, TArg1, TArg2, TArg3, TArg4, 
					TArg5, TArg6, TArg7, TArg8, TArg9>* 
					mf = dynamic_cast<const MemberFunctor<TClass, TRet, 
					TArg0, TArg1, TArg2, TArg3, TArg4, 
					TArg5, TArg6, TArg7, TArg8, TArg9>*>(&rhs);
				if (mf)
				{
					return &(mf->c) == &c && mf->f == f;
				}
			}
			return false;
		}

		virtual Functor<TRet, TArg0, TArg1, TArg2, TArg3, TArg4, 
			TArg5, TArg6, TArg7, TArg8, TArg9>* Clone() const
		{
			return new MemberFunctor(c, f);
		}

	private:
		TClass& c;
		Func f;
	};

}}

#endif