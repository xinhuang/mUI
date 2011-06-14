#include "Font.h"
#include "IFont.h"

namespace mUI{ namespace System{ namespace Drawing{

int Font::get_Size() const
{
	return impl_->get_Size();
}

const String& Font::get_FontFamily() const
{
	return impl_->get_FontFamily();
}

mUI::System::IntPtr Font::ToHfont() const
{
	return reinterpret_cast<IntPtr>(impl_);
}

Font::Font( const String& family_name, float size )
{
	impl_ = IFont::CreateFont(family_name, size);
}

Font::~Font()
{
	delete impl_;
	impl_ = 0;
}

}}}
