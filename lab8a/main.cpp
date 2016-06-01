#include "InfInt.h"
#include <thread>
using namespace std;

void sumFrom0ToN(InfInt N, InfInt &res, int piece, InfInt startedValue) {
	for (InfInt i = startedValue; i <= N; i += piece)
		res += i;
}

void fact(InfInt N, InfInt &res, int piece, InfInt startedValue) {
	if (N < 0)
		throw logic_error("N!, where N < 0");
	if (N == 0) {
		res = 1;
		return;
	}
	for (InfInt i = startedValue; i <= N; i += piece)
		res *= i;
}

int main() {
	InfInt N, result; // initialized by 0
	int n = 0; // number of threads
	cout << "Amount of threads is ";
	cin >> n;
	InfInt *p = new InfInt[n]; // results for threads
	thread *pthr = new thread[n];

	// sum
	cout << "Sum of 0 to N. N: ";
	cin >> N;
	auto time1 = clock();
	for (int i = 0; i < n; ++i) {
		pthr[i] = thread(sumFrom0ToN, N, ref(p[i]), n, i);
	}
	for (int i = 0; i < n; ++i) {
		pthr[i].join();
		result += p[i];
	}
	auto time2 = clock();
	cout << result << "\n" << "time: " << time2 - time1 << endl;

	// fact
	cout << "N!. N: ";
	cin >> N;
	result = 1;
	time1 = clock();
	for (int i = 0; i < n; ++i) {
		p[i] = 1;
		pthr[i] = thread(fact, N, ref(p[i]), n, i + 1);
	}
	for (int i = 0; i < n; ++i) {
		pthr[i].join();
		result *= p[i];
	}
	time2 = clock();
	cout << result << "\n" << "time: " << time2 - time1 << endl;

	// nCk
	InfInt k;
	cout << "nCk. n, k: ";
	cin >> N >> k;
	time1 = clock();
	if (N < k) {
		result = 0;
	}
	else if (N == k) {
		result = 1;
	}
	else {
		result = 1;
		InfInt maxK = (N - k < k ? k : N - k);
		if (n > 1) {
			int i = 0;
			while (i < n) {
				p[i] = 1;
				if (i < n / 2)
					pthr[i] = thread(fact, N - maxK, ref(p[i]), n / 2, i + 1);
				else 
					pthr[i] = thread(fact, N, ref(p[i]), n - n / 2, maxK + (i - n / 2) + 1);
				++i;
			}
			while (i > 0) {
				pthr[--i].join();
				if (i < n / 2)
					result /= p[i];
				else
					result *= p[i];
			}
		}
		else {
			p[0] = 1;
			fact(N, result, 1, maxK + 1);
			fact(N - maxK, p[0], 1, 1);
			result /= p[0];
		}
	}
	time2 = clock();
	cout << result << "\n" << "time: " << time2 - time1 << endl;

	system("pause");
	return 0;
}