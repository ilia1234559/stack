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
		if (!(s[i] >= '0' && s[i] <= '9'))
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


void show(Stack* topS, Stack* botS)
{
	Stack* element = NULL;
	cout << "queue" << endl;
	element = botS;
	int count = 1;
	while (element != NULL)
	{
		cout << count << ")" << " " << element->info << endl;
		element = element->next;
		count++;
	}
	element = topS;
	cout << "stack" << endl;
	count = 1;
	while (element != NULL)
	{
		cout << count << ")" << " " << element->info << endl;
		element = element->prev;
		count++;
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


Stack* task(Stack* topT, Stack* botT)
{
	Stack* elem = topT;
	if (fmod(elem->info, 10) == 5)
	{
		Stack* buf = elem;
		elem = elem->prev;
		delete buf;
		elem->next = NULL;
	}
	else
	{
		elem = elem->prev;
	}

	if (elem->next == NULL)
	{
		elem = elem->prev;
	}

	while (elem != botT)
	{
		if (fmod(elem->info, 10) == 5)
		{
			elem->next->prev = elem->prev;
			Stack* buf = elem;
			elem = elem->prev;
			elem->next = buf->next;
			delete buf;
		}
		else
		{
			elem = elem->prev;
		}
	}
	if (fmod(elem->info, 10) == 5)
	{
		botT = elem->next;
		botT->prev = NULL;
		delete elem;
		elem = botT;
	}
	else
	{
		botT = elem;
	}
	return botT;
}

Stack* topSearch(Stack* bot)
{
	if (bot != NULL)
	{
		while (bot->next != NULL)
		{
			bot = bot->next;
		}
	}
	return bot;
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
			}
			else
			{
				cout << "how many elements you want to add?" << endl;
				kol = inp();

				while (1)
				{
					cout << "1 - enter at top\n2 - enter at bot\n";
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
				show(top, bot);
				break;
				show(top, bot);
				break;
			}
			else
			{
				cout << "\nno elements in list!!!\n";
			}
			break;
		case '3':
			if (top == NULL || bot == NULL)
			{
				cout << "\nno elements in list!!!\n";
			}
			else
			{
				bot = task(top, bot);
				top = topSearch(bot);
			}
			break;
		case '4':
			top = deleteStack(top);
			return 0;
			break;
		}
	}
}

