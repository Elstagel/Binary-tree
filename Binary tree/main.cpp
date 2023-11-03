#include<iostream>
#include<random>
#include<Windows.h>
#include<string>

using namespace std;

enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//получаем дискриптор активного окна

void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, esc = 27 };

void setCursor(int x, int y)
{
	COORD myCoords = { x,y };//инициализируем передаваемыми значениями объект координат
	SetConsoleCursorPosition(hStdOut, myCoords);
}


//каждая ветвь делиться на два элемента
//левый потомок содержит маньше текущего элемента , правый больше
//есть корень root если дерево пустое корень указывает на ноль
//если в дереве есть элементы, то его корень казывает на корневой элемент
//существует две реализациИ дерева(рекурсивная,итерационная)
//итерационная реализации каждый элемент должен содержать адрес родительско элемента
//рекурсивной реалзации в этом нет необъодимости по-скольку адрес родительского элемента, автоматически сохраняется в стеке вызовов (call stack)

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
			//cout << "EConstructor\t" << this << endl;
		}
		~Element()
		{
			//cout << "EDestructor\t" << this << endl;

		}
		friend class Tree;
	}*Root;

public:

	Tree()
	{
		Root = nullptr;
		//cout << "TConstructor\t" << this << endl;
	}
	~Tree()
	{
		clear();
		//cout << "TDestructor\t" << this << endl;

	}

	Element* getRoot()
	{
		return Root;
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
		}
		if (Root == nullptr)
		{
			return;
		}
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
			}
			else
			{
				insert(Data, Root->pLeft);
			}
		}
		else
		{
			if (Root->pRight == nullptr)
			{
				Root->pRight = new Element(Data);
			}
			else
			{
				insert(Data, Root->pRight);
			}

		}
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)
		{
			return;
		}
		//cout << Root->Data << "\t";
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
		//cout << Root->Data << "\t";

	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	int minValue(Element* Root)const
	{
		if (Root == nullptr) return 0;
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr) return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int sum(Element* Root)const
	{
		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	int sum()const
	{
		return sum(Root);
	}
	int size(Element* Root)const
	{
		return Root == nullptr ? 0 : size(Root->pLeft) + size(Root->pRight) + 1;
	}
	int size()const
	{
		return size(Root);
	}
	int depth(Element* Root)const
	{
		if (Root == nullptr)
		{
			return 0;
		}
		return 1 + max(depth(Root->pLeft), depth(Root->pRight));
	}

	double avg()const
	{
		return (double)sum(Root) / size(Root);
	}


	void print_tree(const string& prefix, const Element* Root, bool isLeft)
	{
		if (Root != nullptr)
		{
			cout << prefix;
			setColor(Brown,Black);
			cout << (isLeft ? "|--" : "^--");
			setColor(Green, Black);
			cout << Root->Data << endl;
			setColor(Brown, Black);
			print_tree(prefix + (isLeft ? "|   " : "   "), Root->pLeft, true);
			setColor(Green, Black);
			setColor(Brown, Black);
			print_tree(prefix + (isLeft ? "|   " : "   "), Root->pRight, false);
			setColor(White, Black);
		}
	}

	void print_tree(const Element* Root)
	{
		print_tree("", Root, false);
	}
};




void main()
{
	setlocale(LC_ALL, "");

	random_device rd;
	mt19937 rand_number(rd());
	uniform_int_distribution<> rand(1, 50);


	int n;
	cout << "Введите размер дерева: ";
	cin >> n;
	cout << endl;
	Tree tree;

	for (int i = 0; i < n; i++)
	{
		tree.insert(rand(rand_number), tree.getRoot());
	}

	tree.print(tree.getRoot());
	cout << endl << endl;

	cout << "Минимальное число: " << tree.minValue(tree.getRoot()) << endl << endl;
	cout << "Максимальное число: " << tree.maxValue(tree.getRoot()) << endl << endl;
	cout << "Сумма чисел: " << tree.sum(tree.getRoot()) << endl << endl;
	cout << "Среднее значение чисел: " << tree.avg() << endl << endl;
	cout << "Глубина дерева: " << tree.depth(tree.getRoot()) << endl << endl;
	cout << "Размер дерева: " << tree.size() << endl << endl;


	tree.clear();
	cout << "Удалили и вывели новое дерево:" << endl << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand(rand_number), tree.getRoot());
	}

	tree.print(tree.getRoot());
	cout << endl << endl;

	cout << "Ввывод дерева: " << endl;
	tree.print_tree(tree.getRoot());
}