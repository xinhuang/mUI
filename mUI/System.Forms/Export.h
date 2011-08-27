﻿/*
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

#ifndef __MUI_SYSTEM_FORMS_EXPORT_H__
#define __MUI_SYSTEM_FORMS_EXPORT_H__

#ifdef MUI_EXPORTS
#	define FORMS_ENTRY __declspec(dllexport)
#else
#	define FORMS_ENTRY __declspec(dllimport)
#endif

#endif // __MUI_EXPORT_H__
