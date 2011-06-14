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

#ifndef __MEMBERFUNCTOR00_H__
#define __MEMBERFUNCTOR00_H__

#include "Functor.h"

namespace mUI{ namespace System{

	// ------------------------------------------------------------------------
	// No Argument
	template <typename TClass, typename TRet>
	class MemberFunctor<TClass, TRet> : public Functor<TRet>
	{
		typedef TRet (TClass::*Func)();

	public:

		MemberFunctor(TClass& C, Func F) : c(C), f(F)
		{}

		virtual TRet operator() ()
		{ return (c.*f)(); }

		virtual bool operator== (const Functor<TRet>& rhs) const
		{
			if (&rhs == this)
				return true;
			else
			{
				const MemberFunctor<TClass, TRet>* mf = 
					dynamic_cast<const MemberFunctor<TClass, TRet>*>(&rhs);
				if (mf)
				{
					return &(mf->c) == &c && mf->f == f;
				}
			}
			return false;
		}

		virtual Functor<TRet>* Clone() const
		{
			return new MemberFunctor(c, f);
		}

	private:
		TClass& c;
		Func f;
	};
}}

#endif