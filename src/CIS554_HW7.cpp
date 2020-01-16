//HW5 by Tianjian Xia
//SU Net ID: txia09  SUID: 350385039
#include<vector>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

typedef vector<vector<char>> Pri;

int width(int n) {
	if (n == 3)return 5;
	if (n % 2 == 0) return width(n - 1);
	else if (n % 2 != 0) return 2 * width(n - 1) + 1;
}

int height(int n) {
	if (n == 3) return 5;
	if (n % 2 == 0) return 2 * height(n - 1) + 1;
	else if (n % 2 != 0) return height(n - 1);
}

void BinaryTree(int n, Pri& _P) {
	if (n <= 3) return;
	if (_P.size() == _P[0].size()) {
		int x = _P.size() / 2, y = _P[0].size() / 2;
		vector<char> V;
		for (int i = 1; i <= _P.size(); i++) {
			V.push_back(' ');
		}
		V[_P.size() / 2] = 'o';
		Pri M = _P;
		_P.push_back(V);
		for (auto it : M) {
			_P.push_back(it);
		}
		int _x = _P.size() - x;
		for (int i = x, j = y; i < _x; i++) if (_P[i][j] == ' ') _P[i][j] = '|';
	}
	else if (_P.size() != _P[0].size()) {
		int x = _P.size() / 2, y = _P[0].size() / 2;
		for (auto& it : _P) {
			vector<char> _T = it;
			it.push_back(' ');
			for (auto _it : _T) {
				it.push_back(_it);
			}
		}
		_P[_P.size() / 2][_P.size() / 2] = 'o';
		int _y = _P[0].size() - y;
		for (int i = x, j = y; j < _y; j++) if (_P[i][j] == ' ') _P[i][j] = '-';
	}
	BinaryTree(n - 1, _P);
}

void print(Pri _P) {
	for (auto it1 : _P) {
		for (char it2 : it1) {
			cout << it2;
		}
		cout << endl;
	}
}

void print_f(Pri _P) {
	ofstream outfile("BinaryTree.txt");
	for (auto it1 : _P) {
		string s = "";
		for (char it2 : it1) {
			s += it2;
		}
		s += 10;
		outfile << s;
		s = "";
	}
	outfile.close();
}

int main() {
	Pri P = { {'o',' ',' ',' ','o'},{'|',' ',' ',' ','|'},{'o','-','o','-','o'},{'|',' ',' ',' ','|'},{'o',' ',' ',' ','o'} };
	BinaryTree(8, P);
	print(P);
	print_f(P);

	system("pause");
	return 0;
}
