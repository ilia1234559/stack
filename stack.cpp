#include <Windows.h>
#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;


struct Stack {
	int info;
	Stack* next;
	Stack* prev;
};


double inp()
{
	char s[30];
	int i = 0;
	double x;
	cout << "\nenter value : ";
	while (1)
	{
		s[i] = _getch();
		if (s[i] == 13) break;
		if (s[i] >= '0' && s[i] <= 9)
		{
			continue;
		}
		cout << s[i];
		i++;
	}
	s[i] = '\0';
	x = strtod(s, NULL);
	cout << endl;
	return x;
}


Stack* PushNewList(int kol)
{
	Stack* newEl = NULL;
	Stack* top = NULL;

	top = new Stack;
	top->info = inp();
	top->next = NULL;
	top->prev = NULL;

	for (int i = 0; i < kol - 1; i++)
	{
		newEl = new Stack;
		newEl->info = inp();
		newEl->next = NULL;
		newEl->prev = top;
		top->next = newEl;
		top = newEl;
	}
	return top;
}


Stack* botSearch(Stack* top)
{
	Stack* bot = top;
	while (bot->prev != NULL)
	{
		bot = bot->prev;
	}
	return bot;
}


Stack* push(Stack* top, Stack* bot, int kol, char pos)
{
	Stack* newEl = NULL;
	if (pos == '1')
	{
		for (int i = 0; i < kol; i++)
		{
			newEl = new Stack;
			newEl->info = inp();
			newEl->next = NULL;
			newEl->prev = top;
			top->next = newEl;
			top = newEl;
		}
		return top;
	}
	if (pos == '2')
	{
		for (int i = 0; i < kol; i++)
		{
			newEl = new Stack;
			newEl->info = inp();
			newEl->next = bot;
			newEl->prev = NULL;
			bot->prev = newEl;
			bot = newEl;
		}
		return bot;
	}
}


void show(Stack* topS, Stack* botS, char pos)
{
	Stack* element = NULL;
	if (pos == '1')
	{
		element = botS;
		int count = 1;
		while (element != NULL)
		{
			cout << count << ")" << " " << element->info << endl;
			element = element->next;
			count++;
		}
	}

	if (pos == '2')
	{
		element = topS;
		int count = 1;
		while (element != NULL)
		{
			cout << count << ")" << " " << element->info << endl;
			element = element->prev;
			count++;
		}
	}
}


Stack* deleteStack(Stack* topD)
{
	Stack* buff = NULL;
	while (topD != NULL)
	{
		buff = topD->prev;
		delete topD;
		topD = buff;
	}
	delete buff;
	return topD;
}


/*Stack* Task(Stack* p)
{
	Stack* t;
	p = InStack(p, 11);
	Stack* pred = p;
	t = pred->next;
	while (t != NULL)
	{
		if (fmod(t->info, 10) == 5)
		{
			pred->next = t->next;
			delete t;
			t = pred->next;
		}
		else
		{
			pred = t;
			t = t->next;
		}
	}
	t = p;
	p = t->next;
	delete t;
	return p;
}*/


void task(Stack* topT)
{
	Stack* buf;
	Stack* newEl = new Stack;
	buf = newEl;
	newEl->info = '123';
	newEl->next = topT;
	newEl->prev = NULL;
	newEl->next = topT;
	topT = newEl->next;
	while (topT != NULL)
	{
		
		if (fmod(topT->info, 10) == 5)
		{
			cout << "1";
			newEl->next = topT->next;
			delete topT;
			topT = newEl->next;
		}
		else
		{
			cout << "2";
			newEl = topT;
			topT = topT->next;
		}
	}
	newEl = buf;
	delete newEl;
}

int main()
{
	int kol = 1;

	Stack* top = NULL;
	Stack* bot = NULL;
	while (1)
	{
		cout << "\n1. create new list or add new elements." << endl;
		cout << "2. show list." << endl;
		cout << "3. remove elements that ends with 5" << endl;
		cout << "4. exit." << endl;

		switch (_getch())
		{
		case '1':
			if (top == NULL && bot == NULL)
			{
				cout << "\ncreate new list(min 2 elements) : " << endl;
				do
				{
					cout << "how many elements you want to add(2 min)?";
					kol = inp();
				} while (kol < 2);
				top = PushNewList(kol);
				bot = botSearch(top);
				cout << bot->info;
				cout << top->info;
				system("pause");
			}
			else
			{
				cout << "how many elements you want to add?" << endl;
				kol = inp();
				while (1)
				{
					char pos = _getch();
					if (pos == '1')
					{
						top = push(top, bot, kol, pos);
						break;
					}
					else if (pos == '2')
					{
						bot = push(top, bot, kol, pos);
						break;
					}
					else
					{
						cout << "select 1 or 2!!";
					}
				}
			}

			break;

		case '2':

			if (top != NULL)
			{
				cout << "Press 1 - Show from the beginng of the list" << endl
					<< "Press 2 - Show from the end of the list" << endl;
				while (1)
				{
					char pos = _getch();
					if (pos == '1')
					{
						show(top, bot, pos);
						break;
					}
					else if (pos == '2')
					{
						show(top, bot, pos);
						break;
					}
					else
					{
						cout << "select 1 or 2!!";
					}
				}
			}
			else cout << "\nno elements in list!!!\n";
			break;
		case '3':
			cout << "!";
			if (top == NULL && bot == NULL)
			{
				task(top);
			}
			break;
		case '4':return 0; break;
		}
	}
	return 0;
}
