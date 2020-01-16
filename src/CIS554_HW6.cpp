//HW6 by Tianjian Xia
//SU Net ID: txia09  SUID: 350385039
//CIS554 HW6
//CIS554 HW6   Due: 11:59PM, Friday, Nov. 8.
#include <iostream>
#include <memory>
#include <vector>
#include <math.h>

using namespace std;

class node {
public:
	int value;
	shared_ptr<node> right;
	shared_ptr<node> l_child;
	shared_ptr<node> r_child;
	node() {}
	node(int i) { value = i; }
};

class tree {
public:
	shared_ptr<node> root;
	int level;
	tree() { level = 0; }

	//Implement all member functions below
	tree(int n)//constructor for n-level tree
	//and initilize values as shown in the diagram; 0, 1, 2, ...
	//Note that root node is at level 1 and its value will be initialized to 0
	{
		level = n;
		if (n == 0) return;
		root = make_shared<node>(0);
		int i = 1, num = pow(2, n) - 1;
		shared_ptr<node> cur = root;
		while (i != num) {
			cur->right = make_shared<node>(i);
			cur = cur->right;
			if (i == num - 1) cur->right = root;
			i++;
		}
		cur.reset();
		for (int i = 0; i < num / 2; i++) {
			shared_ptr<node> cur = root;
			for (int move = 0; move < i; move++) cur = cur->right;
			int L = (i + 1) * 2, R = L + 1;
			shared_ptr<node> _L = root, _R = root;
			for (int move = 1; move < L; move++) _L = _L->right;
			for (int move = 1; move < R; move++) _R = _R->right;
			cur->l_child = _L;
			cur->r_child = _R;
			cur.reset();
			_L.reset();
			_R.reset();
		}
	};

	tree(const tree& T)//copy constructor
	{
		level = T.level;
		if (level == 1) {
			shared_ptr<node> cur = make_shared<node>(T.root->value);
			root = cur;
			root->right = root;
			cur.reset();
		}
		else {
			shared_ptr<node> cur = T.root->right;
			shared_ptr<node> _cur = make_shared<node>(T.root->value);
			root = _cur;
			while (cur != T.root) {
				_cur->right = make_shared<node>(cur->value);
				if (cur->right == T.root) _cur->right->right = root;
				_cur = _cur->right;
				cur = cur->right;
			}
			cur.reset();
			_cur.reset();
			int num = pow(2, level) - 1;
			for (int i = 0; i < num / 2; i++) {
				shared_ptr<node> cur = root;
				for (int move = 0; move < i; move++) cur = cur->right;
				int L = (i + 1) * 2, R = L + 1;
				shared_ptr<node> _L = root, _R = root;
				for (int move = 1; move < L; move++) _L = _L->right;
				for (int move = 1; move < R; move++) _R = _R->right;
				cur->l_child = _L;
				cur->r_child = _R;
				cur.reset();
				_L.reset();
				_R.reset();
			}
		}
	};

	~tree()//destructor
	{
		if (level == 0) { return; }
		else {
			root->right.reset();
			root->l_child.reset();
			root->r_child.reset();
			root.reset();
			level = 0;
		}
	};

	tree(tree&& T)//move constructor
	{
		level = T.level;
		root = T.root;
		(T.root).reset();
		T.level = 0;
	};

	tree(const initializer_list<int>& V)//The first number in V is tree level;
	//the rest are values from top to bottom and from left to right
	//For example, to create the tree with n=3 in the diagram,
	//tree T1 = {3, 0,1,2,3,4,5,6}; //where the first 3 is tree level, and the rest are values
	{
		level = *V.begin();
		root = make_shared<node>(*(V.begin() + 1));
		auto it = V.begin() + 2;
		shared_ptr<node> cur = root;
		while (it != V.end()) {
			cur->right = make_shared<node>(*it);
			cur = cur->right;
			if (it == V.end() - 1) cur->right = root;
			it++;
		}
		cur.reset();
		for (int i = 0; i < (pow(2, level) - 1) / 2; i++) {
			shared_ptr<node> cur = root;
			for (int move = 0; move < i; move++) cur = cur->right;
			int L = (i + 1) * 2, R = L + 1;
			shared_ptr<node> _L = root, _R = root;
			for (int move = 1; move < L; move++) _L = _L->right;
			for (int move = 1; move < R; move++) _R = _R->right;
			cur->l_child = _L;
			cur->r_child = _R;
			cur.reset();
			_L.reset();
			_R.reset();
		}
	};

	void operator= (const tree& R)//L-value operator=
	{
		if(level != 0) {
			root->right.reset();
			root->l_child.reset();
			root->r_child.reset();
			root.reset();
			level = 0;
		}


		level = R.level;
		if (level == 1) {
			root = make_shared<node>(R.root->value);
		}
		else {
			shared_ptr<node> cur = R.root->right;
			shared_ptr<node> _cur = make_shared<node>(R.root->value);
			root = _cur;
			while (cur != R.root) {
				_cur->right = make_shared<node>(cur->value);
				if (cur->right == R.root) _cur->right->right = root;
				_cur = _cur->right;
				cur = cur->right;
			}
			cur.reset();
			_cur.reset();
			int num = pow(2, level) - 1;
			for (int i = 0; i < num / 2; i++) {
				shared_ptr<node> cur = root;
				for (int move = 0; move < i; move++) cur = cur->right;
				int L = (i + 1) * 2, R = L + 1;
				shared_ptr<node> _L = root, _R = root;
				for (int move = 1; move < L; move++) _L = _L->right;
				for (int move = 1; move < R; move++) _R = _R->right;
				cur->l_child = _L;
				cur->r_child = _R;
				cur.reset();
				_L.reset();
				_R.reset();
			}
		}
	};

	void operator= (tree&& R)//R-value operator=
	{
		if (level != 1) 
		{
			root->right.reset();
			root->l_child.reset();
			root->r_child.reset();
			root.reset();
			level = 0;
		}
		level = R.level;
		root = R.root;
		(R.root).reset();
		R.level = 0;
	};


	tree ThreeTimes()//return a tree with all node value being three times
	{
		tree New_Tree = *this;
		shared_ptr<node> cur = New_Tree.root;
		while (true) {
			cur->value *= 3;
			cur = cur->right;
			if (cur == New_Tree.root) { cur.reset(); return New_Tree; }
		}
		return New_Tree;
	};

	friend ostream& operator<<(ostream& str, const tree& T)
	{
		if (T.level == 0) { return str; }
		else {
			shared_ptr<node> cur = T.root;
			while (true) {
				str << cur->value << " ";
				cur = cur->right;
				if (cur == T.root) { cur.reset(); return str; }
			}
		}
		return str;
	};

	int sum(shared_ptr<node> p)//sum of node values in sub-tree rooted at p
	{
		int _sum = 0;
		if (p == nullptr) return 0;
		_sum = p->value + sum(p->l_child) + sum(p->r_child);
		return _sum;
	};

	void delete_level(int i)// Delete nodes at level i. Some nodes at level(s) higher
	//than i will also be deleted accordingly. As described in class.  (Also see the
	//example in the main function.)
	{
		if (i == 0) return;
		if (i > level) return;
		shared_ptr<node> cur = root;
		while (true) {
			cur->l_child.reset();
			cur->r_child.reset();
			cur = cur->right;
			if (cur == root) break;
		}
		shared_ptr<node> _cur = root;
		if(i == 1){
			for (int k = 1; k <= pow(2, level) - 2; k++) cur = cur->right;
			_cur = _cur->right;
			cur->right = _cur;
			cur = _cur;
			root = cur;
		}
		else {
			for (int k = 1; k <= pow(2, i - 1) - 2; k++) cur = cur->right;
			for (int k = 1; k <= pow(2, i) - 1; k++) _cur = _cur->right;
			cur->right = _cur;
			cur = _cur;
		}
		int _step = 0;
		while (i + _step < level) {
			for (int j = 1; j <= pow(2, i - 1) - 1; j++) {
				for (int k = 1; k <= pow(2, _step) - 1; k++) cur = cur->right;
				_cur = cur;
				for (int k = 1; k <= pow(2, _step) + 1; k++) _cur = _cur->right;
				cur->right = _cur;
				cur = cur->right;
			}
			for (int k = 1; k <= pow(2, _step) - 1; k++) cur = cur->right;
			_cur = cur;
			for (int k = 1; k <= pow(2, _step) + 1; k++) _cur = _cur->right;
			cur->right = _cur;
			cur = _cur;
			_step++;
		}

		cur.reset();
		_cur.reset();

		level--;
		int num = pow(2, level) - 1;
		for (int i = 0; i < num / 2; i++) {
			shared_ptr<node> cur = root;
			for (int move = 0; move < i; move++) cur = cur->right;
			int L = (i + 1) * 2, R = L + 1;
			shared_ptr<node> _L = root, _R = root;
			for (int move = 1; move < L; move++) _L = _L->right;
			for (int move = 1; move < R; move++) _R = _R->right;
			cur->l_child = _L;
			cur->r_child = _R;
			cur.reset();
			_L.reset();
			_R.reset();
		}
	};

	shared_ptr<node> find(int i)//find the first node with value i and return
	//its address; if not found, return nullptr;
	{
		if (level == 0) return nullptr;
		if (level == 1) {
			if (root->value == i) return root;
			else return nullptr;
		}
		else {
			shared_ptr<node> f = root;
			while (true) {
				if (f->value == i) return f;
				f = f->right;
				if (f == root) { f.reset(); return nullptr; }
			}

		}
		return nullptr;
	};

};




int main() {
	tree T1(3);

	cout << T1 << endl; //will print 0 1 2 3 4 5 6

	tree T2 = { 4, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };

	cout << T2 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24

	tree T3(T2);
	cout << T3 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24

	tree T4;
	T4 = T3;
	cout << T4 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24


	T4 = T3.ThreeTimes();
	cout << T4 << endl;//will print 30 33 36 39 42 45 48 51 54 57 60 63 66 69 72


	T4.delete_level(3);
	cout << T4 << endl;//will print 30 33 36 51 57 63 67


	cout << T3.sum(T3.find(12)) << endl; //will print 133

	getchar();
	getchar();
	return 0;
}
