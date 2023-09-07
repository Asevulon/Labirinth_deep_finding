#pragma once

#include<stack>
#include<time.h>
#include<vector>
using namespace std;

enum direction
{
	no = 0,
	top = 1,
	right = 2,
	bot = 3,
	left = 4
};
enum color
{
	none = 0,
	green = 1,
	yellow = 2
};

struct cell
{
	color c = none;

	cell* t = nullptr;
	cell* r = nullptr;
	cell* b = nullptr;
	cell* l = nullptr;

	bool visited = 0;

	direction in = direction::no;

	bool finish = 0;

	cell() {}
};
typedef cell* link;


class lab
{
private:
	


	
protected:
	inline void clear(link& l);
	link dir(link& c);
	link fdir(link& c);
	void PrepareCells(int heigh, int len);
public:
	lab();
	void CreateLab(int heigh, int len);
	void clear();
	link start;

	void FindPath(int len, int heigh);
};