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

#ifndef __DRAWING_H__
#define __DRAWING_H__

#include "../System.h"

#include "Brush.h"
#include "Color.h"
#include "Font.h"
#include "Graphics.h"
#include "Image.h"
#include "Pen.h"
#include "Point.h"
#include "PointF.h"
#include "Rectangle.h"
#include "Size.h"
#include "SizeF.h"
#include "SolidBrush.h"
#include "SystemColors.h"
#include "SystemFonts.h"
#include "TextureBrush.h"

namespace mUI{ namespace System{  namespace Drawing{

bool Initialize();
void Dispose();

Graphics MUI_ENTRY *CreateGraphics(const Drawing::Rectangle& clip_rect);

}}}

#endif
