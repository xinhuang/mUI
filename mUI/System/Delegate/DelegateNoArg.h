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

#ifndef __DELEGATENOARG_H__
#define __DELEGATENOARG_H__

namespace mUI{ namespace System{
	// -----------------------------------------------------------
	// No Argument
	template <typename TRet>
	class SYSTEM_ENTRY Delegate<TRet>
	{
	public:
		typedef vector<TRet> ReturnType;

		Delegate() {}
		
		virtual ~Delegate()
		{
			for (size_t i = 0; i < delegates.size(); ++i)
			{
				assert(delegates[i]);
				delete delegates[i];
				delegates[i] = NULL;
			}
		}


		Delegate(const Delegate<TRet>& delegate)
		{
			for (size_t i = 0; i < delegate.delegates.size(); ++i)
			{
				Add(delegate.delegates[i]);
			}
		}


		Delegate& operator=(const Delegate<TRet>& delegate)
		{
			RemoveAll();
			Add(delegate);
			return *this;
		}
		
		template <typename TClass>
		Delegate(TClass& C, TRet (TClass::*F)())
		{
			Add<TClass>(C, F);
		}
		
		template <typename TClass>
		Delegate(TClass* pC, TRet (TClass::*F)())
		{
			Add<TClass>(pC, F);
		}

		
		Delegate& operator += (const Delegate<TRet>& Value)
		{
			Add(Value);
			return *this;
		}
		
		Delegate& operator -= (const Delegate<TRet>& Value)
		{
			Remove(Value);
			return *this;
		}

		
		virtual TRet operator() () const
		{
			TRet ret;
			for (size_t i = 0; i < delegates.size(); ++i)
			{
				Functor<TRet>* f = delegates[i];
				assert(f);
				ret = (*f)();
			}
			return ret;
		}

		
		template<typename TClass>
		void Add(TClass& C, TRet (TClass::*F)())
		{
			Functor<TRet>* f = new MemberFunctor<TClass, TRet>(C, F);
			assert(f);
			delegates.push_back(f);
		}
		
		template<typename TClass>
		void Add(TClass* pC, TRet (TClass::*F)())
		{
			assert(pC);
			Functor<TRet>* f = new MemberFunctor<TClass, TRet>(*pC, F);
			assert(f);
			delegates.push_back(f);
		}
		
		void Add(const Delegate<TRet>& D)
		{
			for (size_t i = 0; i < D.delegates.size(); ++i)
			{
				Add(D.delegates[i]);
			}
		}
		
		void Remove(const Delegate<TRet>& D)
		{
			if (&D == this)
				RemoveAll();
			else
				for (size_t i = 0; i < D.delegates.size(); ++i)
				{
					Functor<TRet>* f = D.delegates[i];
					assert(f);
					Remove(f);
				}
		}

		void RemoveAll()
		{
			for (size_t i = 0; i < delegates.size(); ++i)
			{
				assert(delegates[i] != NULL);
				delete delegates[i];
				delegates[i] = NULL;
			}
			delegates.clear();
		}

		// Arguments Binding

		template <typename TClass, typename TArg0>
		Delegate(TClass& c, TRet (TClass::*F)(TArg0), const TArg0& arg0)
		{
			Add(c, F, arg0);
		}

		
		template <typename TClass, typename TArg0>
		void Add(TClass& c, TRet (TClass::*F)(TArg0), const TArg0& arg0)
		{
			Functor<TRet>* f = new FunctorBinder<TRet, TArg0>(c, F, arg0);
			assert(f != NULL);
			delegates.push_back(f);
		}
		
		template <typename TClass, typename TArg0>
		void Remove(TClass& c, TRet (TClass::*F)(TArg0), const TArg0& arg0)
		{
			Remove(&FunctorBinder<TRet, TArg0>(c, F, arg0));
		}

		
		template <typename TClass, typename TArg0, typename TArg1>
		void Add(TClass& c, TRet (TClass::*F)(TArg0, TArg1), const TArg0& arg0, const TArg1& arg1)
		{
			Functor<TRet>* f = new FunctorBinder<TRet, TArg0, TArg1>(c, F, arg0, arg1);
			assert(f != NULL);
			delegates.push_back(f);
		}
		
		template <typename TClass, typename TArg0, typename TArg1>
		void Remove(TClass& c, TRet (TClass::*F)(TArg0, TArg1), const TArg0& arg0, const TArg1& arg1)
		{
			Remove(&FunctorBinder<TRet, TArg0, TArg1>(c, F, arg0, arg1));
		}

		
		template <typename TClass, 
			typename TArg0, typename TArg1, typename TArg2, typename TArg3, typename TArg4,
			typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9>
			void Add(TClass& c, 
				TRet (TClass::*F)(TArg0, TArg1, TArg2, TArg3, TArg4, 
								TArg5, TArg6, TArg7, TArg8, TArg9), 
				const TArg0& arg0, 
				const TArg1& arg1, 
				const TArg2& arg2, 
				const TArg3& arg3, 
				const TArg4& arg4, 
				const TArg5& arg5, 
				const TArg6& arg6, 
				const TArg7& arg7, 
				const TArg8& arg8, 
				const TArg9& arg9)
		{
			Functor<TRet>* f = new FunctorBinder<TRet,
				TArg0, TArg1, TArg2, TArg3, TArg4, 
				TArg5, TArg6, TArg7, TArg8, TArg9>
				(c, F, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			assert(f != NULL);
			delegates.push_back(f);
		}
	
		template <typename TClass, 
			typename TArg0, typename TArg1, typename TArg2, typename TArg3, typename TArg4,
			typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9>
		void Remove(TClass& c, 
			TRet (TClass::*F)(TArg0, TArg1, TArg2, TArg3, TArg4, 
							TArg5, TArg6, TArg7, TArg8, TArg9), 
			const TArg0& arg0, 
			const TArg1& arg1, 
			const TArg2& arg2, 
			const TArg3& arg3, 
			const TArg4& arg4, 
			const TArg5& arg5, 
			const TArg6& arg6, 
			const TArg7& arg7, 
			const TArg8& arg8, 
			const TArg9& arg9)
		{
			Remove(&FunctorBinder<TRet, TArg0, TArg1, TArg2, TArg3, TArg4, 
				TArg5, TArg6, TArg7, TArg8, TArg9>(c, F, arg0, arg1, arg2, arg3, arg4, arg5, 
				arg6, arg7, arg8, arg9));
		}

	
	protected:
		
		void Add(const Functor<TRet>* F)
		{
			assert(F);
			delegates.push_back(F->Clone());
		}
		
		void Remove(const Functor<TRet>* F)
		{
			assert(F);
			for (vector<Functor<TRet>*>::const_iterator iter = delegates.begin();
				iter != delegates.end(); ++iter)
			{
				const Functor<TRet>* f = *iter;
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
		vector<Functor<TRet>*> delegates;
	};


	// ------------------------------------------------------------------
	// Void Return Type Specialization
	template <>
	class Delegate<void>
	{
		typedef void TRet;

	public:

		typedef TRet ReturnType;

		Delegate() {}
		virtual ~Delegate()
		{
			RemoveAll();
		}

		Delegate(const Delegate<TRet>& delegate)
		{
			Add(delegate);
		}
		Delegate& operator=(const Delegate<TRet>& delegate)
		{
			RemoveAll();
			Add(delegate);
			return *this;
		}

		template <typename TClass>
		Delegate(TClass& C, TRet (TClass::*F)())
		{
			Add<TClass>(C, F);
		}
		template <typename TClass>
		Delegate(TClass* pC, TRet (TClass::*F)())
		{
			Add<TClass>(pC, F);
		}

		Delegate& operator += (const Delegate<TRet>& Value)
		{
			Add(Value);
			return *this;
		}
		Delegate& operator -= (const Delegate<TRet>& Value)
		{
			Remove(Value);
			return *this;
		}

		virtual void operator() () const
		{
			for (size_t i = 0; i < delegates.size(); ++i)
			{
				Functor<TRet>* f = delegates[i];
				assert(f);
				(*f)();
			}
		}


		template<typename TClass>
		void Add(TClass& C, TRet (TClass::*F)())
		{
			Functor<TRet>* f = new MemberFunctor<TClass, TRet>(C, F);
			assert(f);
			delegates.push_back(f);
		}
		template<typename TClass>
		void Add(TClass* pC, TRet (TClass::*F)())
		{
			assert(pC);
			Functor<TRet>* f = new MemberFunctor<TClass, TRet>(*pC, F);
			assert(f);
			delegates.push_back(f);
		}
		void Add(const Delegate<TRet>& D)
		{
			for (size_t i = 0; i < D.delegates.size(); ++i)
			{
				Add(D.delegates[i]);
			}
		}
		void Remove(const Delegate<TRet>& D)
		{
			for (size_t i = 0; i < D.delegates.size(); ++i)
			{
				Functor<TRet>* f = D.delegates[i];
				assert(f);
				Remove(f);
			}
		}

		void RemoveAll()
		{
			for (size_t i = 0; i < delegates.size(); ++i)
			{
				assert(delegates[i] != NULL);
				delete delegates[i];
				delegates[i] = NULL;
			}
			delegates.clear();
		}

		// -------------------------------------------------------
		// Arguments binding

#define TPL_RET_ARGLIST typename TRet, typename TArg0
#define TPL_ARGLIST typename TArg0
#define RET_ARGLIST TRet, TArg0
#define T_ARGLIST TArg0
#define ARGLIST arg0
#define FUN_ARGLIST const TArg0& arg0

		template <typename TClass, typename TClassF, TPL_ARGLIST>
		Delegate(TClass& c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Add(c, f, ARGLIST);
		}

		template <typename TClass, typename TClassF, TPL_ARGLIST>
		Delegate(TClass* c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			assert(c != NULL);
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Add(*c, f, ARGLIST);
		}

		template <typename TClass, typename TClassF, TPL_ARGLIST>
		void Add(TClass& c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Functor<TRet>* functor = new FunctorBinder<TRet, T_ARGLIST>(c, f, ARGLIST);
			assert(functor != NULL);
			delegates.push_back(functor);
		}
		template <typename TClass, typename TClassF, TPL_ARGLIST>
		void Remove(TClass& c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Remove(&FunctorBinder<TRet, T_ARGLIST>(c, f, ARGLIST));
		}

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST


#define TPL_RET_ARGLIST typename TRet, typename TArg0, typename TArg1
#define TPL_ARGLIST typename TArg0, typename TArg1
#define RET_ARGLIST TRet, TArg0, TArg1
#define T_ARGLIST TArg0, TArg1
#define ARGLIST arg0, arg1
#define FUN_ARGLIST const TArg0& arg0, const TArg1& arg1

		template <typename TClass, typename TClassF, TPL_ARGLIST>
		Delegate(TClass& c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Add(c, f, ARGLIST);
		}

		template <typename TClass, typename TClassF, TPL_ARGLIST>
		Delegate(TClass* c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			assert(c != NULL);
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Add(*c, f, ARGLIST);
		}

		template <typename TClass, typename TClassF, TPL_ARGLIST>
		void Add(TClass& c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Functor<TRet>* functor = new FunctorBinder<TRet, T_ARGLIST>(c, f, ARGLIST);
			assert(functor != NULL);
			delegates.push_back(functor);
		}
		template <typename TClass, typename TClassF, TPL_ARGLIST>
		void Remove(TClass& c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Remove(&FunctorBinder<TRet, T_ARGLIST>(c, f, ARGLIST));
		}

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST


#define TPL_RET_ARGLIST	typename TRet,  \
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4, \
	typename TArg5, \
	typename TArg6, \
	typename TArg7, \
	typename TArg8, \
	typename TArg9
#define TPL_ARGLIST	\
	typename TArg0, \
	typename TArg1, \
	typename TArg2, \
	typename TArg3, \
	typename TArg4, \
	typename TArg5, \
	typename TArg6, \
	typename TArg7, \
	typename TArg8, \
	typename TArg9
#define RET_ARGLIST TRet, TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9
#define T_ARGLIST TArg0, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9
#define ARGLIST arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9
#define FUN_ARGLIST	const TArg0& arg0, const TArg1& arg1, const TArg2& arg2, const TArg3& arg3, const TArg4& arg4, \
	const TArg5& arg5, const TArg6& arg6, const TArg7& arg7, const TArg8& arg8, const TArg9& arg9

		template <typename TClass, typename TClassF, TPL_ARGLIST>
		Delegate(TClass& c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Add(c, f, ARGLIST);
		}

		template <typename TClass, typename TClassF, TPL_ARGLIST>
		Delegate(TClass* c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			assert(c != NULL);
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Add(*c, f, ARGLIST);
		}

		template <typename TClass, typename TClassF, TPL_ARGLIST>
		void Add(TClass& c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Functor<TRet>* functor = new FunctorBinder<TRet, T_ARGLIST>(c, f, ARGLIST);
			assert(functor != NULL);
			delegates.push_back(functor);
		}
		template <typename TClass, typename TClassF, TPL_ARGLIST>
		void Remove(TClass& c, TRet (TClassF::*F)(T_ARGLIST), FUN_ARGLIST)
		{
			TRet (TClass::*f)(T_ARGLIST);
			f = F;
			Remove(&FunctorBinder<TRet, T_ARGLIST>(c, f, ARGLIST));
		}

#undef TPL_RET_ARGLIST
#undef TPL_ARGLIST
#undef RET_ARGLIST
#undef T_ARGLIST
#undef ARGLIST
#undef FUN_ARGLIST

	protected:

		void Add(const Functor<TRet>* F)
		{
			assert(F);
			delegates.push_back(F->Clone());
		}
		void Remove(const Functor<TRet>* F)
		{
			assert(F);
			for (vector<Functor<TRet>*>::const_iterator iter = delegates.begin();
				iter != delegates.end(); ++iter)
			{
				const Functor<TRet>* f = *iter;
				assert(f);
				if (*f == *F)
				{
					delete *iter;
					delegates.erase(iter);
					break;
				}
			}
		}


		template <typename TArg0>
		void Add(const Functor<TRet, TArg0>& F, TArg0 arg0)
		{
			Functor<TRet>* f = new FunctorBinder<TRet, TArg0>(F, arg0);
			assert(f != NULL);
			delegates.push_back(f);
		}
		template<typename TArg0>
		void Remove(const Functor<TRet, TArg0>& F, TArg0 arg0)
		{
			Remove(&FunctorBinder<TRet, TArg0>(F, arg0));
		}

	private:
		vector<Functor<TRet>*> delegates;
	};


}}

#endif
