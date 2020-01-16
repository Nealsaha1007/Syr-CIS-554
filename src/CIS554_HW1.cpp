//HW1 by Tianjian Xia
//SU Net ID: txia09  SUID: 350385039
//CIS554 HW1
//Due: 11:59PM, Friday ( September 13)
//Do not modify main funaiton.
//Do not introduce new functions
//In-place implementation is required.

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
	void makeRandomList(int m, int n);
	void printForward();
	void printBackward();

	//inplement the following member functions:

	void sort();//sort all values based on frequency in ascending order.
				//In case of ties, the smaller values will appear earlier
				//Example:  for list with values  7 6 12 4 33 12 6 6 7
				//sorted results: 4 33 7 7 12 12 6 6 6


				//If your algorithm is inefficient, you might lose points.
				//You will not modify L.

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

int main() {
	DoublyLinkedList d1;
	d1.makeRandomList(50, 20);
	d1.printForward();
	d1.printBackward();

	d1.sort();
	d1.printForward();
	d1.printBackward();


	getchar();
	getchar();
	return 0;
}
