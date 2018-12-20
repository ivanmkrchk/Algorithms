#include <iostream>
#include <vector>

using namespace std;

int d;

//батько і-го вузла
int Parent(int i)
{
	return (i - 1) / d;
}

//к-й син
int Son(int parent, int k)
{
	return parent * d + k;
}

//підтримка властивості незростання піраміди
void Max_Heapify(vector<int> &A, int i)
{
	int largest = i;
	for (int j = 1; j <= d; ++j)
	{
		int child = Son(i, j);
		if (child < A.size() && A[child] > A[largest])
		{
			largest = child;
		}
	}
	if (largest != i)
	{
		swap(A[i], A[largest]);
		Max_Heapify(A, largest);
	}
}

//повертає максимум
int Heap_Extract_Max(vector<int> &A)
{
	if (A.size() < 1)
	{
		cout << "Error" << endl;
		return -1;
	}
	int Max = A[0];
	A[0] = A[A.size() - 1];
	A.pop_back();
	Max_Heapify(A, 0);
	return Max;
}

//збільшує ключ і-го вузла(ставить його рівним key)
void Heap_Increase_Key(vector<int> &A, int i, int key)
{
	if (key < A[i])
	{
		cout << "Key is less then current" << endl;
		return;
	}
	A[i] = key;
	while (i > 0 && A[Parent(i)] < A[i])
	{
		swap(A[i], A[Parent(i)]);
		i = Parent(i);
	}
}

//вставляє елемент key у піраміду
void Max_Heap_Insert(vector<int> &A, int key)
{
	A.push_back(-1000);
	Heap_Increase_Key(A, (int)A.size() - 1, key);

}

int main()
{
	d = 3;
	vector<int> A;
	//A = { 36, 80, 41, 72, 28,10, 15, 40, 37, 11, 10, 18, 63, 13 };
	A = { 10, 29, 28, 27, 26, 25, 20, 19, 17, 15 };
	Max_Heapify(A, 0);
	for (int i = 0; i < A.size(); ++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
	Heap_Increase_Key(A, 6, 42);
	cout << "After Heap_Increase_Key" << endl;
	for (int i = 0; i < A.size(); ++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
	Max_Heap_Insert(A, 31);
	cout << "After Max_Heap_Insert" << endl;
	for (int i = 0; i < A.size(); ++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}
