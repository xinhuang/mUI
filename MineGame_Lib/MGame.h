#ifndef __MGAME_H__
#define __MGAME_H__

#include <mUI.h>

using mUI::System::Drawing::Size;

class MineField;

class MGame
{
public:
	MGame();
	virtual ~MGame();

	void set_MineFieldWidth(int width);
	void set_MineFieldHeight(int height);
	const Size& get_MineFieldSize() const;
	void set_MineTotal(int mineTotal);
	int get_MineTotal() const;

	void NewGame();
	void Uncover(int rowIndex, int columnIndex);

private:
	Size _MineFieldSize;
	int _MineTotal;
	MineField* _MineField;
};

#endif // __MGAME_H__
