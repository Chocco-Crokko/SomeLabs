#include <thread>
#include "InfInt.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

InfInt **readMatrix(int n, int m, ifstream &in) {
	InfInt **p = new InfInt*[n];
	for (int i = 0; i < n; ++i) {
		p[i] = new InfInt[m];
		for (int j = 0; j < m; ++j) {
			in >> p[i][j];
		}
	}
	return p;
}

void deleteMatrix(InfInt **matr, int n) {
	for (int i = 0; i < n; ++i)
		delete[] matr[i];
	delete[] matr;
}

void multiplyMatrix(InfInt **matr1, int n1, int m1, InfInt **matr2, int n2, int m2, InfInt **res, int piece, int startedValue) {
	if (m1 != n2)
		throw logic_error("Invalid matrix sizes");
	for (int i = startedValue; i < n1*m2; i += piece) {
		int a = i / m2, b = i % m2;
		res[a][b] = 0;
		for (int j = 0; j < m1; ++j)
			res[a][b] += matr1[a][j] * matr2[j][b];
	}
}


int main() {
	InfInt **matr1 = nullptr,  **matr2 = nullptr;
	int n1 = 0, m1 = 0, n2 = 0, m2 = 0, N = 0;
	string path1, path2;
	cout << "Amount of threads is ";
	cin >> N;
	cout << "*****Matrix 1*****\nFile: ";
	cin >> path1;
	cout << "Size(n, m): ";
	cin >> n1 >> m1;
	cout << "*****Matrix 2*****\nFile: ";
	cin >> path2;
	cout << "Size(n, m): ";
	cin >> n2 >> m2;
	ifstream fl1(path1), fl2(path2);
	if (fl1.is_open() && fl2.is_open()) {
		matr1 = readMatrix(n1, m1, fl1);
		matr2 = readMatrix(n2, m2, fl2);
		InfInt **p = new InfInt*[n1]; // results for threads
		for (int i = 0; i < n1; ++i)
			p[i] = new InfInt[m2];
		auto time1 = clock();
		thread *pthr = new thread[N];
		for (int i = 0; i < N; ++i) {
			pthr[i] = thread(multiplyMatrix, matr1, n1, m1, matr2, n2, m2, p, N, i);
		}
		for (int i = 0; i < N; ++i) {
			pthr[i].join();
		}
		auto time2 = clock();
		cout << "time: " << time2 - time1 << endl; 
		deleteMatrix(matr1, n1);
		deleteMatrix(matr2, n2);
		deleteMatrix(p, n1);
	}


	fl1.close();
	fl2.close();
	system("pause");
	return 0;
}