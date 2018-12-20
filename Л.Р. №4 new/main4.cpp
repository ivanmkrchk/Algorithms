#include <iostream>
#include <vector>

using namespace std;

//час роботи O(n), алгоритм стійкий
void sort1(vector<int> &A)
{
	vector<int> B(A.size());
	int x = -1; //підраховує кількість нулів в масиві
	for (int i = 0; i < A.size(); ++i)
	{
		if (A[i] == 0) x++;
	}
	int y = (int)A.size() - 1;
	for (int i = (int)A.size() - 1; i >= 0; --i)
	{
		if (A[i] == 0)
		{
			B[x] = A[i];
			x--;
		}
		else
		{
			B[y] = A[i];
			y--;
		}
	}
	A = B;
}

//Час роботи O(n), сортування проводиться на місці
void sort2(vector<int> &A)
{
	int c = 0;
	for (int i = 0; i < A.size(); ++i)
	{
		if (A[i] == 0)
		{
			swap(A[i], A[c]);
			c++;
		}
	}
}

//алгоритм стійкий, сортування на місці
void sort3(vector<int> &A)
{
	int i = -1; //індекс останнього нуля у вже відсортованій послідовності
	for (int j = 0; j < A.size(); ++j)
	{
		if (A[j] == 0)
		{
			for (int k = j; (k - i - 1) > 0; k--)
			{
				swap(A[k], A[k - 1]);
			}
			i++;
		}
	}
}

void show(vector<int> A)
{
	for (int i = 0; i < A.size(); ++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

int main()
{
	vector<int> A = { 0,0,0,0,1,1,0,0,1,0,1 };

	cout << "Array A before sort1" << endl;
	show(A);
	cout << "Sort1: ";
	sort1(A);
	show(A);

	vector<int> B = { 1,1,1,1,1,1,0,0,0,0,0,0,1,1, };
	cout << "Array B before sort2" << endl;
	show(B);
	cout << "Sort2: ";
	sort2(B);
	show(B);

	vector<int> C = { 1,0,1,0,1,0,1 };
	cout << "Array C before sort2" << endl;
	show(C);
	cout << "Sort3: ";
	sort1(C);
	show(C);

	system("pause");
	return 0;
}
