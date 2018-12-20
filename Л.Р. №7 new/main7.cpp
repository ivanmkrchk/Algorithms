
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
#include<iostream>
using namespace std;

//bad hash
//#define d 3
//#define q 6
 
//good hash
#define d 99
#define q 100

//вивід на екран
void print(char** matrix) {
	int size = strlen(matrix[0]);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j <= size; j++) {
			cout << matrix[i][j] << ' ';
		}  cout << endl;
	}
}

//порівняння матриць починаючи від заданих індексів для уникнення колізії
bool CompMatrix(char** text, char** pattern, int row, int col, int M) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (text[row + i][col + j] != pattern[i][j]) return false;
		}
	}
	return true;
}

//порівняння рядків починаючи від заданих індексів
bool CompLine(int* s1, int* s2, int del) {
	for (int i = 0; i < sizeof(s2) / sizeof(int); ++i)
		if (s1[i + del] != s2[i]) return false;
	return true;

}

//звичайний метод Рабіна-Карпа
int RabinKarpSearch(char** text, char** pattern, int *txt, int *pat, int row) {
	int N = strlen(text[0]), M = strlen(pattern[0]);
	int i;
	int p = 0;
	int t = 0;
	int h = 1;
	for (i = 0; i < M - 1; i++)
		h = (h * d) % q;

	for (i = 0; i < M; i++) {
		p = (d * p + pat[i]) % q;
		t = (d * t + txt[i]) % q;
	}

	for (i = 0; i <= N - M; i++) {
		if (p == t) {

			if (CompLine(txt, pat, i) )
				if (CompMatrix(text, pattern, row, i, M)) //зайвий раз перевіримо чи матриця є підматрицею з початком і точках (на випадок колізії)
					return i;
			
		}
		if (i < N - M) {
			t = (d * (t - txt[i] * h) + txt[i + M]) % q;
			if (t < 0)
				t = (t + q);
		}
	}
	return -1;
}


//саме хешування
void culcHashes(char **matrix, int* hashes, int width, int height) {
	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			hashes[j] = (d * hashes[j] + matrix[i][j]) % q;
		}
	}
}

//перерахунок хешів
void reculcHash(char **matrix, int* hashes, int width, int height, int row) {
	int h = 1;
	for (int i = 0; i < height - 1; i++)
		h = (h * d) % q;
	for (int j = 0; j < width; j++) {
		hashes[j] = (d * (hashes[j] - matrix[row][j] * h) + matrix[row + height][j]) % q;
		if (hashes[j] < 0)
			hashes[j] = (hashes[j] + q);
	}
}


//узагальнений метод для матриць
void RabinKarpMatrix(char **text, char **pattern) {

	int M = strlen(pattern[0]), 
		N = strlen(text[0]);

	int *hashesText = new int[N] {};
	int *hashesPattern = new int[M] {};

	culcHashes(pattern, hashesPattern, M, M);
	culcHashes(text, hashesText, N, M);

	int column = 0;
	for (int j = 0; j <= N - M; j++) {
		column = RabinKarpSearch(text, pattern, hashesText, hashesPattern, j);
		if (column != -1) {
			cout << "Find at row = " << j + 1 << ", column = " << column + 1 << endl;
			return;
		}
		else if (j != N - M) {
			reculcHash(text, hashesText, N, M, j);
		}
	}

	cout << "Pattern wasn't found" << endl;

}

//демонстрація роботи програми
void demonstration() {
	char t1[5][6] = {	"85152",
						"85812",
						"84851",
						"45858",
						"19842"};//where

	char t2[3][4] = {	"851",
						"858",
						"842" };//what

	int n = 5, m = 3;

	char** text = new char *[n];
	char **pattern = new char *[m];

	for (int i = 0; i < n; i++) {
		text[i] = new char[n + 1];
	}

	for (int i = 0; i < m; i++) {
		pattern[i] = new char[m];
	}

	for (int i = 0; i < n; i++) {
		memcpy(text[i], t1[i], sizeof(t1[i]));
		text[i][n] = '\0';
	}

	for (int i = 0; i < m; i++) {
		memcpy(pattern[i], t2[i], sizeof(pattern[i]));
		pattern[i][m] = '\0';
	}

	cout << "Search for: \n\n";
	print(pattern);
	cout << "\nin matrix \n\n";
	print(text);
	cout << "\n\n";


	RabinKarpMatrix(text, pattern);

}

int main() {
	demonstration();
	system("pause");
	return 1;
}
