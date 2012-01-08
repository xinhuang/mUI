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

#include "Functor.h"

namespace mUI{ namespace System{

    namespace __internal{

	    template<TPL_T_ARG>
	    struct Arguments
#if !defined BINDER_ROOT
            <T_ARG>
#endif
	    {
		    Arguments(FUN_T_ARG_ARG)
		    {
                MEMBER_ARG_ASSIGN;
            }

		    virtual bool operator== (const Arguments<T_ARG>& args) const
		    {
			    return ARGUMENTS_EQUAL;
		    }

		    MEMBER_ARG_DECL;
	    };

    }

	template<TPL_T_RET_ARG>
	class FunctorBinder
#if !defined BINDER_ROOT
        <T_RET_ARG>
#endif
        : public Functor<TRet>
	{
	public:
		FunctorBinder(const Functor<T_RET_ARG>& f, ARG_DECL)
			: functor_(f.Clone()), args_(ARG)
		{}

		template<typename TClass>
		FunctorBinder(TClass& c, TRet (TClass::*F)(T_ARG), ARG_DECL)
			: args_(ARG)
		{
			functor_ = new MemberFunctor<TClass, T_RET_ARG>(c, F);
			assert(functor_ != null);
		}

		virtual ~FunctorBinder()
		{
			delete functor_;
			functor_ = null;
		}

		virtual TRet operator() ()
		{
			return (*functor_)(BINDING_ARG);
		}

		virtual bool operator== (const Functor<TRet>& rhs) const
		{
			if (&rhs == this)
				return true;

			const FunctorBinder<T_RET_ARG>* fb = 
				dynamic_cast<const FunctorBinder<T_RET_ARG>*>(&rhs);
			if (fb != 0)
				return (fb->args_) == args_ && *fb->functor_ == *functor_;

			return false;
		}

		virtual Functor<TRet>* Clone() const
		{
			return new FunctorBinder(*functor_, BINDING_ARG);
		}

	private:
		Functor<T_RET_ARG>* functor_;
        __internal::Arguments<T_ARG> args_;
	};

}}
