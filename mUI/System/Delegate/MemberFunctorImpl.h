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


template <TPL_TYPENAME>
class MemberFunctor
#ifndef MEMBERFUNCTOR_ROOT
	<T_CLASS_RET_ARGS> 
#endif // MEMBERFUNCTOR_ROOT
	: public Functor<T_RET_ARGS>
{
public:
	typedef TRet (TClass::*Func)(T_ARGS);

	MemberFunctor(TClass& C, Func F) : c(C), f(F)
	{}

	virtual TRet operator() (FUN_T_ARGS)
	{
		return (c.*f)(ARGS);
	}

	virtual bool operator== (const Functor<T_RET_ARGS>& rhs) const
	{
		if (&rhs == this)
			return true;
			
		const MemberFunctor<T_CLASS_RET_ARGS>* mf = 
			dynamic_cast<const MemberFunctor<T_CLASS_RET_ARGS>*>(&rhs);
		if (mf != 0)
			return &(mf->c) == &c && mf->f == f;
		return false;
	}

	virtual Functor<T_RET_ARGS>* Clone() const
	{
		return new MemberFunctor(c, f);
	}

private:
	TClass& c;
	Func f;
};
