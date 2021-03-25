#include "../BookOfLore"
#include "../Player"
#include <iostream>
#include <string>
#include <time.h>
#include "../Map/Map.hpp"
using namespace std;

class Game
{
private:
	vector<vector<Engimon>> ensiklopediaEngimon;
	vector<vector<Skill>> ensiklopediaSkill;
	Player player;
	Map map;

public:
	Game()
	{
		BookOfLore book;
		ensiklopediaEngimon = book.allEngimon();
		ensiklopediaSkill = book.allSkill();
		map = Map("map.txt");
		map.BacaFile();
	}

	string inputPlayerName()
	{
		cout << "Input player's name: " << endl;
		string name;
		cin >> name;
		return name;
	}

	void printLogo()
	{
		cout << "Welcome to Engimon Emerald!" << endl;
	}

	Engimon chooseEngimon()
	{
		cout << "Choose your first Engimon!" << endl;
		for (int i = 0; i < 5; ++i)
		{
			cout << i + 1 << ".";
			ensiklopediaEngimon[i][0].printEngimon();
		}
		string pilihan;
		int pil;
		do
		{
			cin >> pilihan;
			pil = pilihan[0] - '0';
			if (pil < 1 || pil > 5)
			{
				cout << "Choose between 1-5!" << endl;
			}
		} while (pil < 1 || pil > 5);
		Engimon chosen = ensiklopediaEngimon[piln - 1][0];
		srand(time(NULL));
		int randomSkillElement = rand() % ensiklopediaSkill[pil - 1].size();
		int randomBasicElement = rand() % ensiklopediaSkill[5].size();
		chosen.addSkill(ensiklopediaSkill[pil - 1][randomSkillElement]);
		chosen.addSkill(ensiklopediaSkill[5][randomBasicElement]);
		cout << "Do you want to rename " << chosen.getName() << "?" << endl;
		cout << "*type 'yes' or 'no'" << endl;
		string yesOrNo;
		do
		{
			cin >> yesOrNo;
			if (yesOrNo != "yes" && yesOrNo != "no")
			{
				cout << "Type 'yes' or 'no'!" << endl;
			}
		} while (yesOrNo != "yes" && yesOrNo != "no");

		if (yesOrNo == "yes")
		{
			cout << "Type your engimon's name: ";
			string name;
			cin >> name;
			chosen.setName(name);
		}
		cout << "You retrieve " << chosen.getName() << "!" << endl;
		return chosen;
	}

	void initialNameAndEngimon()
	{
		string name = inputPlayerName();
		Engimon chosen = chooseEngimon();
		player = Player(name, chosen);
	}
};

int main()
{
	// Game g;
	// g.printLogo();
	// char command;
	// vector<EngimonEnemy> listEngimonLiar;
	// m.BacaFile();
	// m.Render(p,listEngimonLiar);
	// do{
	// 	cin >> command;
	// 	p.Move(command);
	// 	m.Render(p,listEngimonLiar);
	// }while(command != 'q');
	return 0;
}