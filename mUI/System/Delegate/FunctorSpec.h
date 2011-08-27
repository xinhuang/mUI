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

#if defined TPL_RET_ARGLIST && defined RET_ARGLIST && defined FUN_ARGLIST

namespace mUI{ namespace System{

template <TPL_RET_ARGLIST>
class Functor<RET_ARGLIST>
{
public:
	virtual ~Functor() {};
	virtual TRet operator() (FUN_ARGLIST) = 0;
	virtual bool operator== (const Functor<RET_ARGLIST>& lhs) const		{ return false; }
	virtual Functor<RET_ARGLIST>* Clone() const = 0;
};

}}

#else

#	pragma error("Define TPL_RET_ARGLIST RET_ARGLIST FUN_ARGLIST first!")

#endif
