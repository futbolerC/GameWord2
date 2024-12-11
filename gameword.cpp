#include <map>
#include <limits.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int Points(const string& startWord, const string& move, vector <string>& enteredWords)
{
	int points = 0;
	if (find(enteredWords.begin(), enteredWords.end(), move) != enteredWords.end()) // дубликат
	{
		points -= move.size()/2;
	}	
	else
	{
		bool wordIsCorrect = true;
		map <char, int> startWordLettersAmount = {};
		map <char, int> moveLettersAmount = {};
		for (char c : startWord)
		{
			startWordLettersAmount[c]++;
		}

		for (char c : move)
		{
			moveLettersAmount[c]++;
		}

		for (char c : move)
		{			
			if (moveLettersAmount[c] > startWordLettersAmount[c])
			{
				wordIsCorrect = false;
			}
		}

		if (wordIsCorrect)
		{
			points += move.size()/2;
		}
		else
		{
			for (auto it = moveLettersAmount.begin(); it != moveLettersAmount.end(); ++it)
			{
				char c = it->first;
				if (moveLettersAmount[c] > startWordLettersAmount[c])
				{
					points -= (moveLettersAmount[c] - startWordLettersAmount[c]);
				}
			}
		}

	}
	
	return points;
}

void Play(const int& players, const string& startWord)
{
	vector <string> enteredWords = { startWord };
	vector <int> playersScore(5);
	
	int currentPlayer = 1, skipMoveCounter = 0;
	bool onGame = true;
	string move;
	getline(cin, move);

	while (onGame)
	{
		cout << "Ход " << currentPlayer << "-го игрока: ";
		getline(cin, move);
		if (move.empty())
		{
			skipMoveCounter++;
		}
		else
		{
			playersScore[currentPlayer] += Points(startWord, move, enteredWords);		
			enteredWords.push_back(move);
			skipMoveCounter = 0;
		}

		cout << "Баллы " << currentPlayer << "-го игрока = " << playersScore[currentPlayer] << endl;
		if (currentPlayer == players)
		{
			currentPlayer = 1;
		}
		else
		{
			currentPlayer++;
		}
		if (skipMoveCounter == players) onGame = false;
	}

	int maxC = INT_MIN, maxCPlayer;
	for (int i = 1; i <= players; i++)
	{
		if (playersScore[i] > maxC)
		{
			maxC = playersScore[i];
			maxCPlayer = i;
		}
	}

	cout << "ИГРА ОКОНЧЕНА ПОБЕДИЛ " << maxCPlayer;
}

int main()
{
	setlocale(LC_ALL, "Ru");
	
	int players;
	string startWord;
    bool isInvalid;
    
	cout << "Число игроков: ";
	cin >> players;
    if(players < 2 || players > 4) {
        cout << "ошибка, число игроков может быть от 2 до 4, пересмотрите свой выбор: ";
    }
    else {
        cout << "\nИсходное слово: ";
	    cin >> startWord;
	    Play(players, startWord);
    }

	return 0;
}