mUI
===

mUI is a 2D game GUI based on HGE, in C++, similiar to WinForm .NET.

mUI is has implementation of C# `delegate`, and adopt same event driven model and threading interface as WinForm .NET.  
It's a prototype for finding a delegent way to design UI in C++, despite of its unoptimized code.

Example
====

The way to add UI widget and listen to event is just the WinForm way in C++:

    void MGameView::InitializeComponents()
    {
        SuspendLayout();
    
        set_Text(L"Mine Game v0.1");
        set_DragMove(true);
    
        Controls.Add(_d->gameButton);
        _d->gameButton.set_NormalImage(L"res/smile.png");
        _d->gameButton.set_PressedImage(L"res/smile_pressed.png");
        _d->gameButton.set_Size(Size(24, 24));
        _d->gameButton.Click += EventHandler<>(this, &MGameView::OnGameButtonClicked);
    
        Controls.Add(_d->fieldView);
        _d->fieldView.Uncover += SquareEventHandler(this, &MGameView::OnSquareUncovered);
        _d->fieldView.ToggleFlag += SquareEventHandler(this, &MGameView::OnSquareToggleFlag);
        _d->fieldView.SquareMouseDown += MouseEventHandler(this, &MGameView::OnSquareMouseDown);
        _d->fieldView.SquareMouseUp += MouseEventHandler(this, &MGameView::OnSquareMouseUp);
    
        Controls.Add(_d->remainMines);
        _d->remainMines.set_Location(Point(5, 5));
        _d->remainMines.set_Size(Size(39, 24));
        _d->remainMines.set_Anchor(AnchorStyles::TopLeft);
    
        ResumeLayout(true);

        _d->configForm->Show();
    }
    
Demos
====
There are 2 demos using mUI:

***Mine Game***
=====
The classic Windows game with exact same apperance.

***Visual Sort***
=====
A visually demo of quick sort, with a worker thread sorting the array while showing sort steps on screen.


Dependencies
====

Rendering: [HGE](http://hge.relishgames.com/)    
Font:      [FreeType](http://www.freetype.org/)    
Testing:   [googletest](https://code.google.com/p/googletest/) 
           [googlemock](http://code.google.com/p/googlemock/)    
           
License
====
[Apache License](http://www.apache.org/licenses/LICENSE-2.0)
