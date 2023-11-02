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

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//�������� ���������� ��������� ����

void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, esc = 27 };

void setCursor(int x, int y)
{
	COORD myCoords = { x,y };//�������������� ������������� ���������� ������ ���������
	SetConsoleCursorPosition(hStdOut, myCoords);
}


//������ ����� �������� �� ��� ��������
//����� ������� �������� ������ �������� �������� , ������ ������
//���� ������ root ���� ������ ������ ������ ��������� �� ����
//���� � ������ ���� ��������, �� ��� ������ �������� �� �������� �������
//���������� ��� ���������� ������(�����������,������������)
//������������ ���������� ������ ������� ������ ��������� ����� ����������� ��������
//����������� ��������� � ���� ��� ������������� ��-������� ����� ������������� ��������, ������������� ����������� � ����� ������� (call stack)

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
	cout << "������� ������ ������: ";
	cin >> n;
	cout << endl;
	Tree tree;

	for (int i = 0; i < n; i++)
	{
		tree.insert(rand(rand_number), tree.getRoot());
	}

	tree.print(tree.getRoot());
	cout << endl << endl;

	cout << "����������� �����: " << tree.minValue(tree.getRoot()) << endl << endl;
	cout << "������������ �����: " << tree.maxValue(tree.getRoot()) << endl << endl;
	cout << "����� �����: " << tree.sum(tree.getRoot()) << endl << endl;
	cout << "������� �������� �����: " << tree.avg() << endl << endl;
	cout << "������� ������: " << tree.depth(tree.getRoot()) << endl << endl;
	cout << "������ ������: " << tree.size() << endl << endl;


	tree.clear();
	cout << "������� � ������ ����� ������:" << endl << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand(rand_number), tree.getRoot());
	}

	tree.print(tree.getRoot());
	cout << endl << endl;

	cout << "������ ������: " << endl;
	tree.print_tree(tree.getRoot());
}