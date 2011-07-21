#include "Font.h"
#include "Internal/FontImpl.h"

namespace mUI{ namespace System{ namespace Drawing{

Font::Font( const String& family_name, float size )
{
	impl_ = FontImpl::CreateFont(family_name, size);
}

Font::~Font()
{
	delete impl_;
	impl_ = 0;
}

bool Font::get_Bold() const
{
	return impl_->get_Bold();
}

bool Font::get_Italic() const
{
	return impl_->get_Italic();
}

bool Font::get_Strikeout() const
{
	return impl_->get_Strikeout();
}

bool Font::get_Underline() const
{
	return impl_->get_Underline();
}

size_t Font::get_Height() const
{
	return impl_->get_Height();
}

float Font::get_SizeInPoints() const
{
	return impl_->get_SizeInPoints();
}

const String Font::get_Name() const
{
	return impl_->get_Name();
}

mUI::System::IntPtr Font::ToHfont() const
{
	return reinterpret_cast<IntPtr>(impl_);
}

bool Font::Initialize()
{
	return FontImpl::Initialize();
}

bool Font::Dispose()
{
	return FontImpl::Dispose();
}

}}}
