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

#ifndef __PICTUREBOX_H__
#define __PICTUREBOX_H__

#include "Control.h"
#include <System/System.h>
#include <System.Drawing/Drawing.h>

namespace mUI{ namespace System{  namespace Forms{

class FORMS_ENTRY PictureBox : public Control
{
public:
	PictureBox();
	virtual ~PictureBox();

	virtual void Load(String ImageLocation);
	//virtual void AsyncLoad(const String& get_ImageLocation);

	Drawing::Image* get_Image() { return image_; }
	const Drawing::Image* get_Image() const { return image_; }
	void set_Image(Drawing::Image& image);

	const String& get_ImageLocation() const { return image_location_; }
	void set_ImageLocation(const String& image_location);

protected:
	virtual void OnPaint( PaintEventArgs* e );

private:
	Drawing::Image* image_;
	String image_location_;
};

}}}

#endif 
