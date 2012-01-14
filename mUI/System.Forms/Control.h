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

#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <vector>
using std::vector;

#include <queue>
using std::queue;

#include <map>
using std::map;

#include <System/System.h>
#include <System.ComponentModel/ComponentModel.h>
#include <System.Threading/Threading.h>

#include "ControlEventArgs.h"
#include "MouseEventArgs.h"
#include "PaintEventArgs.h"
#include "LayoutEventArgs.h"
#include "KeyPressEventArgs.h"

#include "ImageLayout.h"
#include "AnchorStyles.h"

#include <System.Drawing/Drawing.h>
using mUI::System::Drawing::Color;
using mUI::System::Drawing::Size;
using mUI::System::Drawing::Point;
using mUI::System::Drawing::Graphics;

// -------------------------------------------------------------- //

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif

namespace mUI{ namespace System{  namespace Drawing{
	class Image;
	class Font;
}}}

namespace mUI{ namespace System{  namespace Forms{

class Form;

class FORMS_ENTRY Control : public ComponentModel::ISynchronizeInvoke, public Threading::Lockable
{
public:

	// -------------------------------------------------------//
	ControlEventHandler		ControlAdded;
	ControlEventHandler		ControlRemoved;

	EventHandler<>			MouseEnter;
	MouseEventHandler		MouseMove;
	EventHandler<>			MouseHover;
	MouseEventHandler		MouseDown;
	MouseEventHandler		MouseUp;
	MouseEventHandler		MouseWheel;
	EventHandler<>			MouseLeave;
	MouseEventHandler		MouseClick;

	KeyPressEventHandler	KeyPress;

	EventHandler<>			Click;

	PaintEventHandler		Paint;

	EventHandler<>			SizeChanged;
	EventHandler<>			BackColorChanged;
	EventHandler<>			TextChanged;
	EventHandler<>			LocationChanged;
	EventHandler<>			VisibleChanged;
	EventHandler<>			BackgroundImageChanged;
	EventHandler<>			BackgroundImageLayoutChanged;
	LayoutEventHandler		Layout;

	EventHandler<>			Enter;
	EventHandler<>			Leave;
	EventHandler<>			GotFocus;			// TODO: Need more study about the event and keyboard/mouse input.
	EventHandler<>			LostFocus;			// TODO:

	// -------------------------------------------------------//
	Control();
	virtual ~Control();

	// -------------------------------------------------------//
	Graphics* CreateGraphics();

	void Refresh();
	void Invalidate() {}
	void Update();

	const Control* GetChildAtPoint(const Point& pt) const;
	Control* Control::GetChildAtPoint( const Point& pt );

	virtual Point PointToScreen(Point pt) const;
	Drawing::Rectangle RectangleToScreen(Drawing::Rectangle rect) const;

	static Control* FromHandle(const IntPtr& handle);

	// -------------------------------------------------------//
	const Size& get_Size() const;
	void set_Size(const Drawing::Size& size);

	bool get_AutoSize() const;
	void set_AutoSize(bool value);

	void set_Height( int value );
	int get_Height() const;

	void set_Width( int value );
	int get_Width() const;

	Size get_ClientSize() const;
	Drawing::Rectangle get_ClientRectangle() const;

	Drawing::Rectangle get_Bounds() const;
	void set_Bounds(const Drawing::Rectangle& value);

	const Color& get_BackColor() const;
	void set_BackColor(const Color& color); 

	const Color& get_ForeColor() const;
	void set_ForeColor(const Color& color);

	const String& get_Text() const;
	void set_Text(const String& text);

	const Drawing::Font* get_Font() const;
	void set_Font(const Drawing::Font& value);

	const Point& get_Location() const;
	void set_Location(const Point& pt);

	int get_Top() const;
	void set_Top(int value);

	void set_Left(int value) { set_Location(Point(value, get_Top())); }
	int get_Left() const { return get_Location().X; }

	int get_Right() const { return get_Location().X + get_Width(); }

	IntPtr get_Handle() const { return handle_; }

	bool get_Visible() const { return visibility_; }
	void set_Visible(bool Value);

	bool get_Focused() const;
	void set_Focused(bool value);

	Drawing::Image* get_BackgroundImage() { return background_image_; }
	const Drawing::Image* get_BackgroundImage() const { return background_image_; }
	void set_BackgroundImage(Drawing::Image* image);
	void set_BackgroundImage(Drawing::Image* image, bool delete_old);

	ImageLayout get_BackgroundImageLayout() const { return background_image_layout_; }
	void set_BackgroundImageLayout(const ImageLayout& value);

	Control* get_Parent() { return parent_; }
	const Control* get_Parent() const { return parent_; }

	AnchorStyles::Enum get_Anchor() const;
	void set_Anchor(AnchorStyles::Enum value);

	// ---------------------------------------------------------- //

	void Show() { set_Visible(true); }
	void Hide() { set_Visible(false); }

	void BringToFront();

	void SuspendLayout();
	void ResumeLayout();
	void ResumeLayout(bool perform_layout);
	void PerformLayout();
	void PerformLayout(Control* affected_control, const String& affected_property);

	Form& FindForm();
	const Form& FindForm() const;

	virtual IAsyncResult* BeginInvoke(const Delegate<void>& method);
	virtual void EndInvoke(IAsyncResult& asyncResult);
	virtual void Invoke(const Delegate<void>& method);
	virtual bool get_InvokeRequired() const;

	// -------------------------------------------------------//
	// ControlCollection
	class FORMS_ENTRY ControlCollection
	{
	public:
		ControlCollection(Control& outer_class);
		~ControlCollection();

		typedef vector<Control*>::iterator iterator;
		typedef vector<Control*>::const_iterator const_iterator;
		typedef vector<Control*>::reverse_iterator reverse_iterator;
		typedef vector<Control*>::const_reverse_iterator const_reverse_iterator;

		void Add(Control& control);
		void Remove(Control& control);

		iterator begin() { return controls_.begin(); }
		iterator end() { return controls_.end(); }
		reverse_iterator rbegin() { return controls_.rbegin(); }
		reverse_iterator rend() { return controls_.rend(); }
		const_iterator begin() const { return controls_.begin(); }
		const_iterator end() const { return controls_.end(); }
		const_reverse_iterator rbegin() const { return controls_.rbegin(); }
		const_reverse_iterator rend() const { return controls_.rend(); }

	private:
		Control& outer_class_;
		vector<Control*> controls_;
	};

	ControlCollection Controls;

protected:

	friend class Application;
	friend class FormManager;

	virtual void OnControlAdded			( ControlEventArgs* e );
	virtual void OnControlRemoved		( ControlEventArgs* e );

	virtual void OnPaint				( PaintEventArgs* e );

	virtual void OnSizeChanged			( EventArgs* e );
	virtual void OnBackColorChanged		( EventArgs* e );
	virtual void OnTextChanged			( EventArgs* e );
	virtual void OnLocationChanged		( EventArgs* e );
	virtual void OnVisibleChanged		( EventArgs* e );
	virtual void OnBackgroundImageChanged		( EventArgs* e );
	virtual void OnBackgroundImageLayoutChanged	( EventArgs* e );
	virtual void OnLayout				( LayoutEventArgs* e );

	virtual void OnMouseEnter			( EventArgs* e );
	virtual void OnMouseMove			( MouseEventArgs* e );
	virtual void OnMouseHover			( EventArgs* e );
	virtual void OnMouseDown			( MouseEventArgs* e );
	virtual void OnMouseUp				( MouseEventArgs* e );
	virtual void OnMouseWheel			( MouseEventArgs* e );
	virtual void OnMouseLeave			( EventArgs* e );
	virtual void OnMouseClick			( MouseEventArgs* e );

	virtual void OnClick				( EventArgs* e );

	virtual void OnKeyPress				( KeyPressEventArgs* e );

	virtual void OnEnter				( EventArgs* e );
	virtual void OnLeave				( EventArgs* e );
	virtual void OnGotFocus				( EventArgs* e );
	virtual void OnLostFocus			( EventArgs* e );

protected:			// Below is NON-CLR interface.
	void _BringToFront( Control& control);
	static void _Activate(Control& c);
	static void _Deactivate(Control& c);

private:
	class Task;
	IAsyncResult* InvokeHelper(const Delegate<>& method, bool fSynchronous);
	void _InvokeAll();

	void SetAnchor( AnchorStyles::Enum value, const Control &container );
	void Control::PrivateLayout(Control& container, LayoutEventArgs* e);
	const Drawing::Font* GetParentFont() const;
	static const Drawing::Font* get_DefaultFont();

private:
	struct Data;
	Data* _d;

	IntPtr			thread_;
	queue<Task*>	qutaskinvoke_;

	Control*		parent_;
	IntPtr			handle_;

	bool			visibility_;
	String			text_;

	Point			location_;
	Drawing::Size	size_;

	Color			back_color_;

	Drawing::Image*	background_image_;
	ImageLayout		background_image_layout_;

	size_t			suspend_layout_count_;
};

}}}

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif // __CONTROL_H__
