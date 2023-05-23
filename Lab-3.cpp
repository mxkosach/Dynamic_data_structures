#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include "Tree.h"
using namespace std;

int main()
{

	srand(time(0));
	setlocale(LC_ALL, "rus");

	Node* u;
	Tree tr(10), tr2;
	int k = 0, max, kol;

	max = 20;
	kol = 6;

	char menu[][100] = {
		{"  PushElement"}, {"  ShowTree"}, {"  CopyTree"}, {"  CountLeaves"}, {"  PrintLeaves"}, {"  EXIT"}
		
	};
	while (true)
	{
		switch (mmm(kol, menu, max, k))
		{
		case 1: {
			int data;
			cout << "Введите число:";
			cin >> data;
			tr.Push(tr.root, data);
			dump1(tr.root);
			system("pause");
			break;
		}
		case 2: {
			if (tr.root == 0)
				cout << "Дерево пустое\n";
			else {
				cout << "Наше дерево:\n";
				dump1(tr.root);
			}
			system("pause");
			break;
		}
		case 3: {
			if (tr.root == 0)
				cout << "Дерево пустое";
			else {
				tr2.CopyTree(tr2.root, tr.root);
				dump1(tr2.root);
			}
			system("pause");
			break;
		}
		case 4: {
			tr.lv = 0;
			tr.CountLeaves(tr.root);
			cout << "Количество листьев: " << tr.lv << endl;
			system("pause");
			break;
		}
		case 5: {
			if (tr.root == 0)
				cout << "Дерево пустое";
			else {
				cout << "Листья:\n";
				tr.PrintLeaves(tr.root);
			}
			system("pause");
			break;
		}
		case 6: {
			exit(0);
		}
		default:
			cout << "Incorrect number!\n";
			system("pause");
			break;
		}
	}
	return 0;
}


int mmm(int kol, char menu[][100], int max, int k)
{
	int variant = 0;
	char* s = new char[512];
	//system("cls");
	cout << "---------------------------" << endl;
	cout << "Что вы хотите сделать?" << endl;

	for (int i = 0; i < kol; i++)
	{
		cout << i + 1 << "." << menu[i] << endl;
	}
	cout << ">";
	cin >> s;
	variant = atoi(s);
	return variant;
}
