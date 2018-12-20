#include <iostream>
using namespace std;

//префікс-функція(в масив f записати скільки символів збігається для цього масиву і циклічно зсунутого цього масиву із закінченням в поточній позиції)
void prefix_function(char* line, int f[])
{
	int m = strlen(line), k;
	f[0] = -1;
	for (int i = 1; i < m; i++)
	{
		k = f[i - 1];
		while (k >= 0)
		{
			if (line[k] == line[i - 1])
				break;
			else
				k = f[k];
		}
		f[i] = k + 1;
	}
}

//перевіряємо чи є line елементом line2
int KMP(char* line, char* line2)
{
	int size_line = strlen(line);
	int n = strlen(line2);
	int* prefix = new int[size_line];
	prefix_function(line, prefix);
	int i = 0;
	int k = 0;
	while (i < n)
	{
		if (k == -1)
		{
			i++;
			k = 0;
		}
		else if (line2[i] == line[k])
		{
			i++;
			k++;
			if (k == size_line)
				return (i - size_line + 1);
		}
		else
			k = prefix[k];
	}
	return -1;
}

int main()
{
	//приклад з habr
	char pat[] = "abaabb";
	char tar[] = "abbaba";
	char *tar2 = new char[strlen(tar) * 2 - 1];
	int size = strlen(tar);
	for (int i = 0; i < 2*size; i++)
		tar2[i] = tar[i%size];

	if (KMP(pat, tar2)!=-1)
		cout << pat << " found in string " << tar << endl;	
	else
		cout<< pat <<  " not found in string " << tar << endl;

	system("pause");
	return 0;
}