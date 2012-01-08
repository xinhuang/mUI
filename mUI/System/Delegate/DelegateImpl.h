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

#if defined TPL_RET_ARGLIST && defined RET_ARGLIST && defined RET_ARGLIST && defined T_ARGLIST && defined ARGLIST && defined FUN_ARGLIST

namespace mUI{ namespace System{

template <TPL_RET_ARGLIST>
class Delegate
#ifndef DELEGATE_ROOT
    <RET_ARGLIST>
#endif
{
public:
	Delegate() {}
	virtual ~Delegate()
	{
		for (size_t i = 0; i < delegates.size(); ++i)
		{
			assert(delegates[i] != null);
			delete delegates[i];
			delegates[i] = null;
		}
	}

	Delegate(const Delegate<RET_ARGLIST>& delegate)
	{
		Add(delegate);
	}

	Delegate& operator=(const Delegate<RET_ARGLIST>& delegate)
	{
		RemoveAll();
		Add(delegate);
		return *this;
	}

	template <typename TClass, typename TClassF>
	Delegate(TClass& C, TRet (TClassF::*F)(T_ARGLIST))
	{
		TClassF& c = C;
		Add<TClassF>(c, F);
	}
	template <typename TClass, typename TClassF>
	Delegate(TClass* pC, TRet (TClassF::*F)(T_ARGLIST))
	{
		TClassF& c = *pC;
		Add<TClassF>(c, F);
	}

	friend inline Delegate& operator += (Delegate<RET_ARGLIST>& lhs, const Delegate<RET_ARGLIST>& Value)
	{
		lhs.Add(Value);
		return lhs;
	}
	friend inline Delegate& operator -= (Delegate<RET_ARGLIST>& lhs, const Delegate<RET_ARGLIST>& Value)
	{
		lhs.Remove(Value);
		return lhs;
	}

	virtual TRet operator() (FUN_ARGLIST) const
	{
		TRet ret;
		for (size_t i = 0; i < delegates.size(); ++i)
		{
			Functor<RET_ARGLIST>* f = delegates[i];
			assert(f);
			ret = (*f)(ARGLIST);
		}
		return ret;
	}

	template<typename TClass, typename TClassF>
	void Add(TClass& C, TRet (TClassF::*F)(T_ARGLIST))
	{
		TClassF& c = C;
		Functor<RET_ARGLIST>* f = new MemberFunctor<TClassF, RET_ARGLIST>(c, F);
		assert(f);
		delegates.push_back(f);
	}

	template<typename TClass, typename TClassF>
	void Add(TClass* pC, TRet (TClassF::*F)(T_ARGLIST))
	{
		assert(pC);
		Add<TClass>(*pC, F);
	}
	void Add(const Delegate<RET_ARGLIST>& D)
	{
		for (size_t i = 0; i < D.delegates.size(); ++i)
		{
			Add(D.delegates[i]);
		}
	}
	void Remove(const Delegate<RET_ARGLIST>& D)
	{
		for (size_t i = 0; i < D.delegates.size(); ++i)
		{
			Functor<RET_ARGLIST>* f = D.delegates[i];
			assert(f);
			Remove(f);
		}
	}

	void RemoveAll()
	{
		for (size_t i = 0; i < delegates.size(); ++i)
		{
			assert(delegates[i] != null);
			delete delegates[i];
			delegates[i] = null;
		}
		delegates.clear();
	}
protected:
	void Add(const Functor<RET_ARGLIST>* F)
	{
		assert(F);
		delegates.push_back(F->Clone());
	}
	void Remove(const Functor<RET_ARGLIST>* F)
	{
		assert(F);
		for (vector<Functor<RET_ARGLIST>*>::const_iterator iter = delegates.begin();
			iter != delegates.end(); ++iter)
		{
			const Functor<RET_ARGLIST>* f = *iter;
			assert(f);
			if (*f == *F)
			{
				delete *iter;
				delegates.erase(iter);
				break;
			}
		}
	}


private:
	vector<Functor<RET_ARGLIST>*> delegates;
};



// ------------------------------------------------------------------
// Void Return Type Specialization
template <TPL_ARGLIST>
class Delegate<void, T_ARGLIST>
{
	typedef void TRet;

public:
	Delegate() {}
	virtual ~Delegate()
	{
		for (size_t i = 0; i < delegates.size(); ++i)
		{
			assert(delegates[i] != null);
			delete delegates[i];
			delegates[i] = null;
		}
	}

	Delegate(const Delegate<RET_ARGLIST>& delegate)
	{
		Add(delegate);
	}


	Delegate& operator=(const Delegate<RET_ARGLIST>& delegate)
	{
		RemoveAll();
		Add(delegate);
		return *this;
	}

	template<typename TClass, typename TClassF>
	Delegate(TClass& C, TRet (TClassF::*F)(T_ARGLIST))
	{
		Add<TClass>(C, F);
	}
	template<typename TClass, typename TClassF>
	Delegate(TClass* pC, TRet (TClassF::*F)(T_ARGLIST))
	{
		Add<TClass>(pC, F);
	}


	friend inline Delegate& operator += (Delegate<RET_ARGLIST>& lhs, const Delegate<RET_ARGLIST>& Value)
	{
		lhs.Add(Value);
		return lhs;
	}
	friend inline Delegate& operator -= (Delegate<RET_ARGLIST>& lhs, const Delegate<RET_ARGLIST>& Value)
	{
		lhs.Remove(Value);
		return lhs;
	}

	virtual void operator() (FUN_ARGLIST) const
	{
		for (size_t i = 0; i < delegates.size(); ++i)
		{
			Functor<RET_ARGLIST>* f = delegates[i];
			assert(f);
			(*f)(ARGLIST);
		}
	}


	template<typename TClass, typename TClassF>
	void Add(TClass& C, TRet (TClassF::*F)(T_ARGLIST))
	{
		TClassF& c = C;
		Functor<RET_ARGLIST>* f = new MemberFunctor<TClassF, RET_ARGLIST>(c, F);
		assert(f);
		delegates.push_back(f);
	}
	template<typename TClass, typename TClassF>
	void Add(TClass* pC, TRet (TClassF::*F)(T_ARGLIST))
	{
		assert(pC);
		Add(*pC, F);
	}
	void Add(const Delegate<RET_ARGLIST>& D)
	{
		for (size_t i = 0; i < D.delegates.size(); ++i)
		{
			Add(D.delegates[i]);
		}
	}

	void Remove(const Delegate<RET_ARGLIST>& D)
	{
		for (size_t i = 0; i < D.delegates.size(); ++i)
		{
			Functor<RET_ARGLIST>* f = D.delegates[i];
			assert(f);
			Remove(f);
		}
	}	

	void RemoveAll()
	{
		for (size_t i = 0; i < delegates.size(); ++i)
		{
			assert(delegates[i] != null);
			delete delegates[i];
			delegates[i] = null;
		}
		delegates.clear();
	}

protected:

	void Add(const Functor<RET_ARGLIST>* F)
	{
		assert(F);
		delegates.push_back(F->Clone());
	}
	void Remove(const Functor<RET_ARGLIST>* F)
	{
		assert(F);
		for (vector<Functor<RET_ARGLIST>*>::const_iterator iter = delegates.begin();
			iter != delegates.end(); ++iter)
		{
			const Functor<RET_ARGLIST>* f = *iter;
			assert(f);
			if (*f == *F)
			{
				delete *iter;
				delegates.erase(iter);
				break;
			}
		}
	}


private:
	vector<Functor<RET_ARGLIST>*> delegates;
};

}}

#else

#	pragma error("Define TPL_RET_ARGLIST RET_ARGLIST RET_ARGLIST T_ARGLIST ARGLIST FUN_ARGLIST first!")

#endif