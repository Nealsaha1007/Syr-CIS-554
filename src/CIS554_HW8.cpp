//HW8 by Tianjian Xia
//SU Net ID: txia09  SUID: 350385039
//CIS554 HW8
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<fstream>

using namespace std;

class Card {
public:
	int figure;
	int pattern;
	Card() {
		figure = 0;
		pattern = 0;
	}
};

void printCards(vector<Card> c);

class Deck {
public:
	vector<Card> deck{ 52 };
	Deck() {
		for (int i = 0; i < 52; ++i) {
			deck[i].figure = i % 13 + 1;
			deck[i].pattern = i / 13 + 1;
		}
	}

	void Shuffle() {
		random_shuffle(deck.begin(), deck.end());
	}

	Card Deal() {
		Card pop = deck.back();
		deck.pop_back();
		return pop;
	}

	bool IsEmpty() {
		return deck.empty();
	}
};

class BattleField {
public:
	map<int, vector<Card>> players;
	map<int, vector<Card>> tables;

	int getPlayerAmount() {
		return players.size();
	}

	void AddPlayer() {
		int num = getPlayerAmount();
		vector<Card> c{ 0 };
		players[num] = c;
		tables[num] = c;
		return;
	}

	vector<Card> Hand(int index) {
		return players[index];
	}

	vector<Card> Front(int index) {
		return tables[index];
	}

	void playCards(int index, int number) {
		if (players[index].empty())
			return;
		else
			for (int i = 0; i < number; ++i) {
				Card pop = players[index].back();
				players[index].pop_back();
				tables[index].push_back(pop);
			}
		return;
	}

	void getCards(int index, Card c) {
		players[index].push_back(c);
		return;
	}

	int MaxSize() {
		int res = 0;
		for (auto it : tables)
			if ((it.second).size() > res)
				res = it.second.size();

		return res;
	}

	bool IfDuo() {
		int max = MaxSize(), max_f = 0;
		
		for (int i = 0; i < tables.size(); ++i)
			if (tables[i].size() == max)
				if (tables[i].back().figure > max_f)
					max_f = tables[i].back().figure;

		int count = 0;

		for (int i = 0; i < tables.size(); ++i)
			if (tables[i].size() == max)
				if (tables[i].back().figure == max_f)
					count++;
		
		if (count > 1)
			return true;
		
		return false;
	}

	vector<int> DuoIndex() {
		vector<int> res;
		int max = MaxSize();
		int max_f = 0;
		for (auto it : tables)
			if (it.second.size() == max)
				if (it.second.back().figure > max_f)
					max_f = it.second.back().figure;

		for (auto it : tables)
			if (it.second.size() == max)
				if (it.second.back().figure == max_f)
					res.push_back(it.first);

		return res;
	}

	int WinnerIndex() {
		int max = MaxSize();
		int max_f = 0;
		for (auto it : tables)
			if (it.second.size() == max)
				if (it.second.back().figure > max_f)
					max_f = it.second.back().figure;

		for (auto it : tables)
			if (it.second.size() == max)
				if (it.second.back().figure == max_f)
					return it.first;

		return 0;
	}

	void WipeTable() {
		vector<Card> c{ 0 };
		int num = getPlayerAmount();
		for (int i = 0; i < num; ++i)
			tables[i] = c;
		return;
	}

	bool IfLose() {
		for (auto it : players)
			if (it.second.size() < 5)
				return true;
		return false;
	}

	vector<int> LoseIndex() {
		vector<int> res;
		for (auto it : players)
			if (it.second.size() < 5)
				res.push_back(it.first);
		return res;
	}

	int getActivePlayerAmount() {
		int count = 0;
		for (auto it : players)
			if (!it.second.empty())
				count++;

		return count;
	}

	void playerShuffle(int index) {
		random_shuffle(players[index].begin(), players[index].end());
		return;
	}
};


int main() {
	Deck deck;
	BattleField B;

	ofstream File("data1.txt", ios::app);

	File << "Initialize Deck:" << endl;
	printCards(deck.deck);
	File << endl;

	deck.Shuffle();

	File << "Deck Shuffled:" << endl;
	printCards(deck.deck);
	File << endl;

	int playerAmount;
	cout << "Player Amount: ";
	cin >> playerAmount;
	File << endl;
	File << endl;

	File << "Player Amount:" << endl;
	File << playerAmount << endl;
	File << endl;

	for (int i = 0; i < playerAmount; ++i)
		B.AddPlayer();

	int index = 0;
	while (!deck.IsEmpty()) {
		B.getCards(index, deck.Deal());
		if (index == playerAmount - 1)
			index = 0;
		else
			index++;
	}

	File << endl;
	File << endl;
	File << endl;

	for (int i = 0; i < playerAmount; ++i) {
		File << "Hand " << i + 1 << ":" << endl;
		File << endl;
		printCards(B.Hand(i));
		File << endl;
	}

	File << "  ----------------------------------------------------------------------------------------------------  " << endl;

	for (int i = 0; i < playerAmount; ++i) {
		File << "Table " << i + 1 << ":" << endl;
		File << endl;
		printCards(B.Front(i));
		File << endl;
	}

	File << endl;
	File << "  ====================================================================================================  " << endl;
	File << endl;

	while (B.getActivePlayerAmount() != 1) {

		B.WipeTable();

		for (int i = 0; i < playerAmount; ++i)
			B.playCards(i, 1);

		for (int i = 0; i < playerAmount; ++i) {
			File << "Hand " << i + 1 << ":" << endl;
			File << endl;
			printCards(B.Hand(i));
			File << endl;
		}

		File << "  ----------------------------------------------------------------------------------------------------  " << endl;

		for (int i = 0; i < playerAmount; ++i) {
			File << "Table " << i + 1 << ":" << endl;
			File << endl;
			printCards(B.Front(i));
			File << endl;
		}

		File << endl;
		File << "  ====================================================================================================  " << endl;
		File << endl;

		int W_index = -1;
		while (true) {
			if (B.IfDuo()) {
				vector<int> ply = B.DuoIndex();
				for (int i : ply)
					B.playCards(i, 2);

				for (int i = 0; i < playerAmount; ++i) {
					File << "Hand " << i + 1 << ":" << endl;
					File << endl;
					printCards(B.Hand(i));
					File << endl;
				}

				File << "  ----------------------------------------------------------------------------------------------------  " << endl;

				for (int i = 0; i < playerAmount; ++i) {
					File << "Table " << i + 1 << ":" << endl;
					File << endl;
					printCards(B.Front(i));
					File << endl;
				}

				File << endl;
				File << "  ====================================================================================================  " << endl;
				File << endl;
			}
			else {
				W_index = B.WinnerIndex();
				break;
			}
		}

		for (auto it : B.tables)
			for (auto i : it.second)
				B.getCards(W_index, i);

		if (B.IfLose()) {
			vector<int> L_index = B.LoseIndex();
			for (auto it : L_index)
				for (auto i : B.players[it])
					B.getCards(W_index, i);
			vector<Card> c{ 0 };
			for (auto it : L_index)
				B.players[it] = c;
		}

		B.playerShuffle(W_index);
	}

	int Winner = 0;
	for (int i = 0; i < playerAmount; ++i)
		if (B.players[i].size() > 0)
			Winner = i;

	File << "Winner is Player " << Winner + 1 << "." << endl;
	File << endl;
	File << "Hands:" << endl;
	File << endl;
	
	printCards(B.players[Winner]);

	system("pause");
	return 0;
}

void printCards(vector<Card> c) {

	ofstream File("data1.txt", ios::app);
	
	for (Card it : c) {
		if (it.figure == 1)
			File << "A";
		else if (it.figure > 10)
			switch (it.figure) {
			case 11:File << "J";
				break;
			case 12:File << "Q";
				break;
			case 13:File << "K";
			}
		else
			File << it.figure;

		switch (it.pattern) {
		case 1:File << "C";
			break;
		case 2:File << "D";
			break;
		case 3:File << "S";
			break;
		case 4:File << "H";
		}

		File << " ";
	}
	File << endl;
	
	return;
}
