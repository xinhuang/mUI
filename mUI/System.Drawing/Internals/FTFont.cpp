#include "FTFont.h"

#include <System/System.h>

#include "Glyph.h"

namespace mUI{ namespace System { namespace Drawing{

FT_Library FTFont::library_;

FTFont::FTFont(const String& filename, float font_size)
{
	Load(filename, 0);
	set_Size(font_size);
}

//FTFont::FTFont( const void* buffer, size_t cb_buf, float font_size )
//{
//	Load(buffer, cb_buf, 0);
//	set_Size(font_size);
//}

FTFont::~FTFont()
{
	while(!glyph_cache_.empty())
		Decache(glyph_cache_.begin()->first);
	if (FT_Done_Face(face_) != 0)
		assert(!"FTFont disposed failed!");
}

void FTFont::Load( const String &filename, size_t index )
{
	int error = FT_New_Face(library_, filename.ToANSI().c_str(), index, &face_);
	switch (error)
	{
	case 0:	// No Error.
		break;

	case FT_Err_Unknown_File_Format:
		assert(!"freetype2 Error: Unknown file format.");

	default:
		assert(!"freetype2 Error: Load font file error.");
	}
}

void FTFont::Load( const void* buffer, size_t cb_buf, size_t index )
{
	const FT_Byte* buf = reinterpret_cast<const FT_Byte*>(buffer);
	int error = FT_New_Memory_Face( library_, buf, cb_buf, index, &face_ );
	if (error == FT_Err_Unknown_File_Format)
		assert(!"freetype2 Error: Unknown file format.");
	else
		assert(!"freetype2 Error: Load font file error.");
}

size_t FTFont::get_NumberOfGlyph() const
{
	return face_->num_glyphs;
}

bool FTFont::get_Scalable() const
{
	return (face_->face_flags & FT_FACE_FLAG_SCALABLE) != 0;
}

Glyph* FTFont::get_Glyph( utf32_t code ) const
{
	if (IsCached(code))
	{
		Glyph* glyph = get_Cache(code);
		assert(glyph != null);
		if (glyph->get_Texture().IsValid())
			return glyph;
		else
			Decache(code);
	}
	if (FT_Load_Char(face_, code, FT_LOAD_RENDER) != 0)
		goto __nil_glyph;

	FT_GlyphSlot slot = face_->glyph;
	int left = slot->bitmap_left;
	int top = slot->bitmap_top;
	int adv_x = slot->advance.x;
	int adv_y = slot->advance.y;
	size_t width = slot->bitmap.width;
	size_t height = slot->bitmap.rows;

	Glyph* glyph = new Glyph(code, 
		reinterpret_cast<int8_t*>(slot->bitmap.buffer),
		width, height, left, -top, adv_x, adv_y);

	if (glyph && glyph->get_Texture().IsValid())
	{
		Cache(glyph);
		return glyph;
	}

	delete glyph;

__nil_glyph:
	// TODO: Nil glyph.
	return null;
}

bool FTFont::get_Bold() const
{
	return (face_->style_flags & FT_STYLE_FLAG_BOLD) != 0;
}

bool FTFont::get_Italic() const
{
	return (face_->style_flags & FT_STYLE_FLAG_ITALIC) != 0;
}

bool FTFont::get_Strikeout() const
{
	assert(!"how to do this?");
	return false;
}

void FTFont::set_Size( float font_size )
{
	ptsize_ = font_size;
	FT_Set_Char_Size(face_, static_cast<FT_F26Dot6>(font_size) * 64, 0, DPI, 0);
}

float FTFont::get_SizeInPoints() const
{
	return ptsize_;
}

const String FTFont::get_Name() const
{
// warning C4996: 'mUI::System::String::String': was declared deprecated
#pragma warning(push)
#pragma warning(disable: 4996)
	return face_->family_name;
#pragma warning(pop)
}

bool FTFont::Initialize()
{
	return FT_Init_FreeType(&library_) == 0;
}

bool FTFont::Dispose()
{
	return FT_Done_FreeType(library_) == 0;
}

bool FTFont::get_Underline() const
{
	assert(!"Not implemented!");
	return false;
}

size_t FTFont::get_Height() const
{
	if (FT_IS_SCALABLE(face_))
		return face_->size->metrics.height >> 6;
	else
		return 0;
}

float FTFont::get_Size() const
{
	return 0.f;
}

Point FTFont::get_Kerning( utf32_t left, utf32_t right ) const
{
	if (!FT_HAS_KERNING(face_))
		goto __no_kerning;

	FT_Vector kerning_vec;
	FT_UInt left_index = FT_Get_Char_Index(face_, left);
	FT_UInt right_index = FT_Get_Char_Index(face_, right);
	if (FT_Get_Kerning(face_, left_index, right_index, FT_KERNING_DEFAULT, &kerning_vec) == 0)
	{
		Point kerning;
		kerning.X = kerning_vec.x;
		kerning.Y = kerning_vec.y;
		return kerning;
	}

__no_kerning:
	return Point::Empty;
}

bool FTFont::IsCached( utf32_t code ) const
{
	map<utf32_t, Glyph*>::iterator iter;
	iter = glyph_cache_.find(code);
	return iter != glyph_cache_.end();
}

void FTFont::Cache( Glyph* glyph ) const
{
	assert(glyph != null && glyph->get_Texture().IsValid());
	assert(!IsCached(glyph->get_Code()));
	glyph_cache_[glyph->get_Code()] = glyph;
}

void FTFont::Decache( utf32_t code ) const
{
	assert(IsCached(code));
	map<utf32_t, Glyph*>::iterator iter;
	iter = glyph_cache_.find(code);
	delete iter->second;
	glyph_cache_.erase(iter);
}

Glyph* FTFont::get_Cache( utf32_t code ) const
{
	map<utf32_t, Glyph*>::iterator iter;
	iter = glyph_cache_.find(code);
	if (iter != glyph_cache_.end())
		return iter->second;
	else
		return null;
}

}}}
