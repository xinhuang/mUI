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

#ifndef __MEMBERFUNCTOR01_H__
#define __MEMBERFUNCTOR01_H__

#include "Functor.h"

namespace mUI{ namespace System{

	// ------------------------------------------------------------------------
	// 1 Argument
	template <typename TClass, typename TRet, typename TArg1>
	class MemberFunctor<TClass, TRet, TArg1> : public Functor<TRet, TArg1>
	{
	public:
		typedef TRet (TClass::*Func)(TArg1);

		MemberFunctor(TClass& C, Func F) : c(C), f(F)
		{}

		virtual TRet operator() (TArg1 a1)
		{ return (c.*f)(a1); }

		virtual bool operator== (const Functor<TRet, TArg1>& rhs) const
		{
			if (&rhs == this)
				return true;
			else
			{
				const MemberFunctor<TClass, TRet, TArg1>* mf = 
					dynamic_cast<const MemberFunctor<TClass, TRet, TArg1>*>(&rhs);
				if (mf)
				{
					return &(mf->c) == &c && mf->f == f;
				}
			}
			return false;
		}

		virtual Functor<TRet, TArg1>* Clone() const
		{
			return new MemberFunctor(c, f);
		}

	private:
		TClass& c;
		Func f;
	};

}}

#endif