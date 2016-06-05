#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include "console.h"
#include <string>
#include <conio.h>
#include <time.h>

using namespace std;

enum TrangThai {UP, DOWN, LEFT, RIGHT};

#define Width 80
#define Height 25

struct Data
{
	int x, y;
	char s;
	TrangThai tt;
};
typedef struct Data DATA;

struct Node
{
	DATA data;
	struct Node *pNext;
	struct Node *pPrev;
};
typedef struct Node NODE;

struct List
{
	NODE *pHead;
	NODE *pTail;
};
typedef struct List LIST;

struct Prey
{
	int xp, yp;
};
typedef struct Prey PREY;

void InitP(PREY &p)
{
	p.xp = 1 + rand() % 79;
	p.yp = 1 + rand() % 24;
}

void Init(LIST &l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}

int isEmpty(LIST l)
{
	return (l.pHead == NULL ? 1 : 0);
}

NODE* GetNode(DATA &x)
{
	NODE *p = new NODE;
	p->data = x;
	p->pNext = NULL;
	p->pPrev = NULL;
	return p;
}

void InputXY(DATA &s)
{
	s.x = 0;
	s.y = 0;
	s.s = '*';
	s.tt = RIGHT;
}

void AddHead(LIST &l, NODE *p)
{
	if(l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		p->pNext = l.pHead;
		l.pHead->pPrev = p;
		l.pHead = p;
	}
}

void AddTail(LIST &l, NODE *p)
{
	if(l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		p->pPrev = l.pTail;
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

void DelHead(LIST &l)
{
	NODE *p = l.pHead;
	l.pHead = l.pHead->pNext;
	delete p;
}

void DelLast(LIST &l)
{
	NODE *p;
	for(NODE *k = l.pHead; k != NULL; p = p->pNext)
	{
		if(k == l.pTail)
		{
			l.pTail = p;
			l.pTail->pNext = NULL;
			delete k;
			return;
		}
		p = k;
	}
}

void MakeHead(LIST &l)
{
	DATA m;
	InputXY(m);
	NODE *p = GetNode(m);
	AddHead(l, p);
}

void OutputP(PREY p)
{
	gotoXY(p.xp, p.yp);
	cout << '0';
}

void EatPrey(LIST &l, PREY &p)
{
	DATA k;
	if(l.pHead->data.x == p.xp && l.pHead->data.y == p.yp)
	{
		k.x = p.xp;
		k.y = p.yp;
		k.s = '*';
		k.tt = l.pHead->data.tt;
		NODE *n = GetNode(k);
		AddTail(l, n);
		p.xp = 1 + rand() % 79;
		p.yp = 1 + rand() % 24;
		OutputP(p);
	}		
}

void Move(LIST &l)
{
	NODE *p = l.pTail;
	for(; p != l.pHead; p = p->pPrev)
	{
		p->data = p->pPrev->data;

		gotoXY(p->data.x,p->data.y);
		printf("x");
	}
	if(l.pHead->data.y <= 0)
		l.pHead->data.tt = DOWN;
	else if(l.pHead->data.y >= Height - 1)
		l.pHead->data.tt = UP;
	else if(l.pHead->data.x <= 0)
		l.pHead->data.tt = RIGHT;
	else if(l.pHead->data.x >= Width - 1)
		l.pHead->data.tt = LEFT;

	if(kbhit())
	{
		char key = getch();

		if(key == 'a' || key == 'A')
			l.pHead->data.tt = LEFT;
		else if(key == 'D' || key == 'd')
			l.pHead->data.tt = RIGHT;
		else if(key == 'w' || key == 'W')
			l.pHead->data.tt = UP;
		else if(key == 's' || key == 'S')
			l.pHead->data.tt = DOWN;
	}

	if(l.pHead->data.tt == DOWN)
		l.pHead->data.y++;
	else if(l.pHead->data.tt == UP)
		l.pHead->data.y--;
	else if(l.pHead->data.tt == LEFT)
		l.pHead->data.x--;
	else if(l.pHead->data.tt == RIGHT)
		l.pHead->data.x++;

	gotoXY(l.pHead->data.x,l.pHead->data.y);
	printf("x");
}

void DelList(LIST &l)
{
	NODE *p;
	while(l.pHead != NULL)
	{
		p = l.pHead;
		l.pHead = l.pHead->pNext;
		delete p;
	}
}

int main ()
{
	srand(time(NULL));
	LIST l;
	PREY p;
	DATA i;
	Init(l);
	InitP(p);
	MakeHead(l);
	i.x = 1;
	i.y = 0;
	i.tt = l.pHead->data.tt;
	i.s = '*';
	NODE *o = GetNode(i);
	AddHead(l, o);
	while(1)
	{
		clrscr();	
		TextColor(8 + rand() % 8);

		EatPrey(l, p);
		OutputP(p);
		Move(l);

		/*for(NODE *p=l.pHead;p!=NULL;p=p->pNext)
		{
		gotoXY(p->data.x,p->data.y);
		printf("x");
		}*/

		Sleep(100);
	}	
	DelList(l);	
	return 0;
}