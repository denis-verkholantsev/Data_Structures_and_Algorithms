#include <iostream>
#include <fstream>
#include "queue.h"

class Card {
private:
	unsigned int _value;
public:
	Card(unsigned int value) : _value(value) {};
	Card() : _value(0) {};
	unsigned int get_value() const {
		return _value;
	};
};

void pointer_to_new_string(std::ifstream& inFile) {
	int ch;
	while ((ch = inFile.get()) != '\n' && ch != EOF) {}
}

int convert_to_int(std::ifstream& inFile) {
	int ch = inFile.get();
	switch (inFile.peek()) {
	case ' ':
		pointer_to_new_string(inFile);
		if (ch < int('9') + 1) {
			return int(ch - '0');
		}
		if (ch == 'J') {
			return 11;
		}
		if (ch == 'Q') {
			return 12;
		}
		if (ch == 'K') {
			return 13;
		}
		if (ch == 'A') {
			return 14;
		}
	default:
		pointer_to_new_string(inFile);
		return 10;
	}
}

int rules(unsigned int value_1, unsigned int value_2) {
	if (value_1 > value_2) {
		if (value_1 == 14 && value_2 == 2) {
			return 2;
		}
		return 1;
	}
	if (value_1 < value_2) {
		if (value_1 == 2 && value_2 == 14) {
			return 1;
		}
		return 2;
	}
	return 3;
}

void fillingOfDeck(my::queue<Card>& instance, std::ifstream& inFile) {
	for (size_t i = 0; i < 26; ++i) {
		instance.push(Card(convert_to_int(inFile)));
	}
}

void put(my::queue<Card>& play, my::queue<Card>& player) {
	while (!play.empty()) {
		player.push(play.pop());
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Not enough arguments";
	}
	else {
		std::ifstream inFile(argv[1]);
		my::queue<Card> player_1;
		my::queue<Card> player_2;
		fillingOfDeck(player_1, inFile);
		fillingOfDeck(player_2, inFile);
		size_t i = 0;
		my::queue<Card> play;
		do {
			Card card_1(player_1.pop());
			Card card_2(player_2.pop());
			int result = rules(card_1.get_value(), card_2.get_value());
			play.push(card_1);
			play.push(card_2);
			switch (result) {
			case 1: {
				put(play, player_1);
				break;
			}
			case 2: {
				put(play, player_2);
				break;
			}
			}
		} while (!player_1.empty() && !player_2.empty() && ++i < 1000000);
		if (i == 1000000) {
			std::cout << "unknown";
		}
		else if (player_1.empty() && player_2.empty()) {
			std::cout << "draw";
		}
		else if (player_1.empty()) {
			std::cout << "second";
		}
		else {
			std::cout << "first";
		}
	}
}
