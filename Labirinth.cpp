#include"pch.h"
#include"Labirinth.h"





lab::lab() { start = nullptr; }
void lab::clear() 
{
	link next;
	while (start != NULL)
	{
		next = start->b;
		clear(start);
		start = next;
	}
}
void lab::clear(link& l)
{
	if (l == nullptr)return;
	clear(l->r);
	delete l;
}

void lab::PrepareCells(int heigh, int len)
{
	start = new cell;
	link pos = start;
	for (int i = 1; i < len; i++)
	{
		pos->r = new cell;
		pos->r->l = pos;
		pos = pos->r;
	}

	link top = start;
	link rb = start;
	pos = start;

	for (int i = 1; i < heigh; i++)
	{
		rb->b = new cell;
		rb->b->t = rb;

		top = rb;
		rb = rb->b;
		pos = rb;

		for (int j = 1; j < len; j++)
		{
			pos->r = new cell;
			pos->r->l = pos;
			pos->r->t = top->r;
			top->r->b = pos->r;

			top = top->r;
			pos = pos->r;
		}
	}
	pos->finish = 1;
}

link lab::dir(link& c)
{
	vector<link>ds;
	if (c->b != nullptr)
		if (c->b->visited == 0)ds.push_back(c->b);

	if (c->r != nullptr)
		if (c->r->visited == 0)ds.push_back(c->r);

	if (c->t != nullptr)
		if (c->t->visited == 0)ds.push_back(c->t);

	if (c->l != nullptr)
		if (c->l->visited == 0)ds.push_back(c->l);

	if (ds.empty())return nullptr;
	int d = double(ds.size()) * rand() / double(RAND_MAX + 1);

	if (ds[d] == c->b)
	{
		ds[d]->in = top;
	}
	if (ds[d] == c->l)
	{
		ds[d]->in = right;
	}
	if (ds[d] == c->r)
	{
		ds[d]->in = left;
	}
	if (ds[d] == c->t)ds[d]->in = bot;

	return ds[d];
}

void lab::CreateLab(int heigh, int len)
{
	clear();
	srand(time(NULL));
	PrepareCells(heigh, len);

	int size = len * heigh;
	int ctr = 1;

	link pos = start;
	stack<link>s;

	while (ctr < size)
	{
		pos->visited = 1;
		link next = dir(pos);

		while (next == nullptr)
		{
			pos = s.top();
			s.pop();
			next = dir(pos);
		}

		ctr++;
		if (next->finish == 0)
		{
			s.push(pos);
			pos = next;
		}
		else next->visited = 1;
	}
}



void lab::FindPath(int len, int heigh)
{
	link pos = start;
	link rb = start;
	for (int i = 0; i < len; i++)
	{
		pos->visited = 0;
		pos = pos->r;
	}
	for (int i = 1; i < heigh; i++)
	{
		rb = rb->b;
		pos = rb;
		for (int j = 0; j < len; j++)
		{
			pos->visited = 0;
			pos = pos->r;
		}
	}


	stack<link>s;
	pos = start;
	link next = start;
	while (!next->finish)
	{
		pos->visited = 1;
		next = fdir(pos);
		while (next == nullptr)
		{
			pos->c = yellow;
			pos = s.top();
			s.pop();
			next = dir(pos);
		}
		pos->c = green;
		s.push(pos);
		pos = next;
	}
}


link lab::fdir(link& c)
{
	if (c->t != nullptr)
	{
		if (c->t->in == bot)
			if (c->t->visited == 0)return c->t;
	}
	
	if (c->r != nullptr)
	{
		if (c->r->in == left)
			if (c->r->visited == 0)return c->r;
	}
		
	if (c->b != nullptr)
	{
		if (c->b->in == top)
			if (c->b->visited == 0)return c->b;
	}
			
	if (c->l != nullptr)
	{
		if (c->l->in == right)
			if (c->l->visited == 0)return c->l;
	}
		
	return nullptr;
}
