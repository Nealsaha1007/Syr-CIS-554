//HW2 by Tianjian Xia
//SU Net ID: txia09  SUID: 350385039
//CIS554 HW2
#include <iostream>
using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node* previous;
	Node(int i) { value = i; next = previous = nullptr; }
	Node() { next = previous = nullptr; }
};

class DoublyLinkedList {
public:
	Node* head;
	Node* tail;
	DoublyLinkedList() { head = tail = nullptr; }
	void makeRandomList(int m,int n);
	void makeRandomList1();
	void printForward();
	void printBackward();
	void sort();
	void merge(DoublyLinkedList& L);
	void remove(int m, int n);
};

void DoublyLinkedList::makeRandomList(int m, int n) {

	for (int i = 0; i < m; i++) {
		Node* p1 = new Node(rand() % n);
		p1->previous = tail;
		if (tail != nullptr) tail->next = p1;
		tail = p1;
		if (head == nullptr) head = p1;
	}
}
/*
void DoublyLinkedList::makeRandomList1() {

	for (int i = 0; i < 5; i++) {
		Node* p1 = new Node(9);
		p1->previous = tail;
		if (tail != nullptr) tail->next = p1;
		tail = p1;
		if (head == nullptr) head = p1;
	}
	for (int i = 0; i < 5; i++) {
		Node* p1 = new Node(4);
		p1->previous = tail;
		if (tail != nullptr) tail->next = p1;
		tail = p1;
		if (head == nullptr) head = p1;
	}

}
*/

void DoublyLinkedList::printForward() {
	cout << endl;
	Node* p1 = head;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void DoublyLinkedList::printBackward() {
	cout << endl;
	Node* p1 = tail;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}

void DoublyLinkedList::sort() {
	Node* q = head, * p = head, * end = tail;

	for (p; p != nullptr; p = p->next)
		for (q = p->next; q != nullptr; q = q->next)
			if ((p->value) > (q->value))
			{
				int s = q->value;
				q->value = p->value;
				p->value = s;
			}


	int len1 = 0, len2 = 0, stamp = 1;
	p = head;
	while (stamp == 1)
	{
		stamp = 0;
		for (q = p->next; q != nullptr; q = q->next)
		{
			++len1;

			if (p->value != q->value) {
				Node* move = q;
				for (move; move != nullptr; move = move->next)
				{
					if (move->value != q->value)
					{
						if (len1 > len2)
						{
							q->previous->next = move;
							if (p == head)head = q;
							else p->previous->next = q;
							move->previous->next = p;

							Node* pre = p->previous;
							p->previous = move->previous;
							move->previous = q->previous;
							q->previous = pre;
							len2 = 1;
							q = move;
							stamp = 1;
						}
						else {
							p = q;
							q = move;
							len1 = len2;
							len2 = 1;
						}
						//printForward();
					}
					else ++len2;
				}
				if (len1 > len2)
				{
					q->previous->next = move;
					if (move == nullptr) {
						tail->next = p;
					}
					else move->previous->next = p;
					if (p == head)head = q;
					else p->previous->next = q;


					if (move == nullptr)
					{
						Node* t = q->previous;
						q->previous = p->previous;
						p->previous = tail;
						tail = t;
					}
					else
					{
						p->previous = move->previous;
						move->previous = q->previous;
						q->previous = p->next;
					}
					stamp = 1;

					break;
				}
			}
		}
		//printForward();
		//printBackward();

		p = head;
		len1 = 0;
		len2 = 0;
	}
}
void DoublyLinkedList::merge(DoublyLinkedList& L) {
	Node* q = L.head, * p = L.head, * end = L.tail, * temp = nullptr;
	int flag;
	{
		for (p; p != nullptr; p = p->next)
			for (q = p->next; q != nullptr; q = q->next)
				if ((p->value) > (q->value))
				{
					int s = q->value;
					q->value = p->value;
					p->value = s;
				}
	}
	//lab:

	{
		p = L.head;
		if (p == nullptr) goto lab0;
		flag = p->value;
		//int  count0 = 0, count1 = 0;

		while (true) {
			if (L.head == nullptr) break;
			for (q = p->next; q != nullptr; q = q->next) {
				//count0++;
				if (q->value != p->value || q->next == nullptr) {
					Node* w = head;
					for (w; w != nullptr; w = w->next) {
						if (w->value == flag) break;
					}
					if (w == nullptr) w = head;
					if (w == head) {
						if (q->next == nullptr) {
							q->next = w;
							w->previous = q->previous;
							L.head = nullptr;
							head = p;
							p = q;
							flag = p->value;
							p = L.head;
							if (p == nullptr)q = p;
							else q = p->next;
							break;

						}
						else {
							q->previous->next = w;
							w->previous = q->previous;
							L.head = q;
							head = p;
							p = q;
							flag = p->value;
							p = L.head;
							if (p == nullptr)q = p;
							else q = p->next;
							//q = p->next;
						}
					}
					else if (w != head && w->value == flag) {
						if (q->next == nullptr) {
							p->previous = w->previous;
							q->next = w;
							w->previous->next = p;
							w->previous = q;
							L.head = nullptr;
							flag = p->value;
							p = L.head;
							if (p == nullptr)q = p;
							else q = p->next;
							break;

						}
						else {
							p->previous = w->previous;
							q->previous->next = w;
							w->previous->next = p;
							w->previous = q->previous;
							L.head = q;
							p = q;
							flag = p->value;
							p = L.head;
							if (p == nullptr)q = p;
							else q = p->next;
						}
					}
				}
			}

		}
	lab0: {}
		
		Node* b = head, * a = head, * end1 = tail;
		for (a; a != nullptr; a = a->next)
			for (b = a->next; b != nullptr; b = b->next)
				if ((a->value) > (b->value))
				{
					int s = b->value;
					b->value = a->value;
					a->value = s;
				}
		int len3 = 0, len4 = 0, fst = 1;
		a = head;
		while (fst == 1)
		{
			fst = 0;
			for (b = a->next; b != nullptr; b = b->next)
			{
				++len3;

				if (a->value != b->value) {
					Node* mov = b;
					for (mov; mov != nullptr; mov = mov->next)
					{
						if (mov->value != b->value)
						{
							if (len3 > len4)
							{
								b->previous->next = mov;
								if (a == head)head = b;
								else a->previous->next = b;
								mov->previous->next = a;

								Node* pre0 = a->previous;
								a->previous = mov->previous;
								mov->previous = b->previous;
								b->previous = pre0;
								len4 = 1;
								b = mov;
								fst = 1;
							}
							else {
								a = b;
								b = mov;
								len3 = len4;
								len4 = 1;
							}
							//printForward();
						}
						else ++len4;
					}
					if (len3 > len4)
					{
						b->previous->next = mov;
						if (mov == nullptr) {
							tail->next = a;
						}
						else mov->previous->next = a;
						if (a == head)head = b;
						else a->previous->next = b;


						if (mov == nullptr)
						{
							Node* t0 = b->previous;
							b->previous = a->previous;
							a->previous = tail;
							tail = t0;
						}
						else
						{
							a->previous = mov->previous;
							mov->previous = b->previous;
							b->previous = a->next;
						}
						fst = 1;

						break;
					}
				}
			}
			//printForward();
			//printBackward();

			a = head;
			len3 = 0;
			len4 = 0;
		}
		
	}

}

void DoublyLinkedList::remove(int m, int n) {
	int num = n, value = m;
	if (num == 0) {}
	else
	{
		Node* v = head;
		for (v; v != nullptr; v = v->next) {
			if (v->value == value) break;
		}
		if (v->next == nullptr) {
			tail = v->previous;
		}
		else {
			Node* u;
			int count = 1;
			for (u = v; u != nullptr; u = u->next) {
				++count;
				if (u->value != v->value) break;
			}
			if (num >= count) {
				if (v == head) {
					if (u == tail) {
						head = nullptr;
					}
					else {
						head = u;
					}
				}
				else {
					if (u == tail) {
						v->previous->next = nullptr;
					}
					else {
						v->previous->next = u->next;
						u->next->previous = v->previous;
					}
				}
			}
			else {
				Node* x = v;
				for (int i = 1; i <= num; i++) {
					x = x->next;
				}
				if (v == head) {
					head = x;
				}
				else {
					v->previous->next = x->next;
					x->next->previous = v->previous;
				}
			}
		}
	}
	Node* b = head, * a = head, * end1 = tail;
	for (a; a != nullptr; a = a->next)
		for (b = a->next; b != nullptr; b = b->next)
			if ((a->value) > (b->value))
			{
				int s = b->value;
				b->value = a->value;
				a->value = s;
			}
	int len3 = 0, len4 = 0, fst = 1;
	a = head;
	while (fst == 1)
	{
		fst = 0;
		for (b = a->next; b != nullptr; b = b->next)
		{
			++len3;

			if (a->value != b->value) {
				Node* mov = b;
				for (mov; mov != nullptr; mov = mov->next)
				{
					if (mov->value != b->value)
					{
						if (len3 > len4)
						{
							b->previous->next = mov;
							if (a == head)head = b;
							else a->previous->next = b;
							mov->previous->next = a;

							Node* pre0 = a->previous;
							a->previous = mov->previous;
							mov->previous = b->previous;
							b->previous = pre0;
							len4 = 1;
							b = mov;
							fst = 1;
						}
						else {
							a = b;
							b = mov;
							len3 = len4;
							len4 = 1;
						}
						//printForward();
					}
					else ++len4;
				}
				if (len3 > len4)
				{
					b->previous->next = mov;
					if (mov == nullptr) {
						tail->next = a;
					}
					else mov->previous->next = a;
					if (a == head)head = b;
					else a->previous->next = b;


					if (mov == nullptr)
					{
						Node* t0 = b->previous;
						b->previous = a->previous;
						a->previous = tail;
						tail = t0;
					}
					else
					{
						a->previous = mov->previous;
						mov->previous = b->previous;
						b->previous = a->next;
					}
					fst = 1;

					break;
				}
			}
		}
		//printForward();
		//printBackward();

		a = head;
		len3 = 0;
		len4 = 0;
	}
}


int main() {
	DoublyLinkedList d1, d2;
	d1.makeRandomList(50,20);
	d1.sort();
	d1.printForward();
	d1.printBackward();
	d2.makeRandomList(50,10);
	d2.printForward();
	d2.printBackward();
	d1.merge(d2);
	d2.printForward();
	d2.printBackward();
	d1.printForward();
	d1.printBackward();

	d1.remove(13, 3);
	d1.printForward();
	d1.printBackward();
	getchar();
	getchar();
	return 0;
}
















