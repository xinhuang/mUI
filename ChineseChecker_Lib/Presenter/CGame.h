#ifndef __CGAME_H__
#define __CGAME_H__

class Board;

class CGame
{
public:
	CGame();
	~CGame();

	Board* get_Board();

private:
	struct Data;
	Data* _d;
};

#endif // __CGAME_H__
