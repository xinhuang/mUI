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

#ifndef __FUNCTORBINDER01_H__
#define __FUNCTORBINDER01_H__

#include "Functor.h"

namespace mUI{ namespace System{

	template<typename TArg0>
	struct Arguments<TArg0>
	{
		Arguments(TArg0 a0) : arg0(a0)
		{}

		virtual bool operator== (const Arguments<TArg0>& args) const
		{
			return args.arg0 == arg0;
		}

		TArg0 arg0;
	};

	template<typename TRet, typename TArg0>
	class FunctorBinder<TRet, TArg0> : public Functor<TRet>
	{
	public:
		FunctorBinder(const Functor<TRet, TArg0>& f, const TArg0& arg0)
			: functor_(f.Clone()), args_(arg0)
		{}
		template<typename TClass>
		FunctorBinder(TClass& c, TRet (TClass::*F)(TArg0), const TArg0& arg0)
			: args_(arg0)
		{
			functor_ = new MemberFunctor<TClass, TRet, TArg0>(c, F);
			assert(functor_ != NULL);
		}

		virtual ~FunctorBinder()
		{
			delete functor_;
			functor_ = NULL;
		}

		virtual TRet operator() ()
		{
			return (*functor_)(args_.arg0);
		}
		virtual bool operator== (const Functor<TRet>& rhs) const
		{
			if (&rhs == this)
				return true;
			else
			{
				const FunctorBinder<TRet, TArg0>* fb = 
					dynamic_cast<const FunctorBinder<TRet, TArg0>*>(&rhs);
				if (fb)
				{
					return (fb->args_) == args_ && *fb->functor_ == *functor_;
				}
			}
			return false;
		}
		virtual Functor<TRet>* Clone() const
		{
			return new FunctorBinder(*functor_, args_.arg0);
		}

	private:
		Functor<TRet, TArg0>* functor_;
		Arguments<TArg0> args_;
	};

}}

#endif