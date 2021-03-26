#include "BookOfLore.hpp"
#include "../Player/Player.hpp"
#include "../Battle/Battle.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include "Map.hpp"
using namespace std;

class Game
{
private:
	vector<vector<Engimon>> ensiklopediaEngimon;
	vector<vector<Skill>> ensiklopediaSkill;
	vector<Element> listKosong;
	Player player;
	Map map;

public:
	Game() : player(listKosong), map("../Map/map.txt")
	{
		BookOfLore book;
		ensiklopediaEngimon = book.allEngimon();
		ensiklopediaSkill = book.allSkill();
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
		// cout << "Welcome to Engimon Emerald!" << endl;
		cout << " __      __       .__                                ___________     " << endl;
		cout << "/  \\    /  \\ ____ |  |   ____  ____   _____   ____   \\__    ___/___  " << endl;
		cout << "\\   \\/\\/   // __ \\|  | _/ ___\\/  _ \\ /     \\_/ __ \\    |    | /  _ \\ " << endl;
		cout << " \\        /\\  ___/|  |_\\  \\__(  <_> )  Y Y  \\  ___/    |    |(  <_> )" << endl;
		cout << "  \\__/\\  /  \\___  >____/\\___  >____/|__|_|  /\\___  >   |____| \\____/ " << endl;
		cout << "       \\/       \\/          \\/            \\/     \\/                  " << endl;

		cout << "___________              .__                       " << endl;
		cout << "\\_   _____/ ____    ____ |__| _____   ____   ____  " << endl;
		cout << " |    __)_ /    \\  / ___\\|  |/     \\ /  _ \\ /    \\ " << endl;
		cout << "/_______  /___|  /\\___  /|__|__|_|  /\\____/|___|  /" << endl;
		cout << "        \\/     \\//_____/          \\/            \\/ " << endl;

		cout << "___________              __                       " << endl;
		cout << "\\_   _____/____    _____/  |_  ___________ ___.__." << endl;
		cout << " |    __) \\__  \\ _/ ___\\   __\\/  _ \\_  __ <   |  |" << endl;
		cout << " |     \\   / __ \\  \\___|  | (  <_> )  | \\/\\___  |" << endl;
		cout << " \\___  /  (____  /\\___  >__|  \\____/|__|   / ____|" << endl;
		cout << "     \\/        \\/     \\/                   \\/     " << endl;
	}

	void printLogoEnd()
	{
		cout << endl;
		cout << "__________                         " << endl;
		cout << "\\______   \\___.__. ____            " << endl;
		cout << " |    |  _<   |  |/ __ \\           " << endl;
		cout << " |    |   \\___  \\  ___/           " << endl;
		cout << " |______  // ____|\\___  >  /\\ /\\ /\\" << endl;
		cout << "        \\/ \\/         \\/   \\/ \\/ \\/" << endl;
	}

	void printCommandList(){
		cout << "\n=--COMMAND LIST--=" << endl;
		cout << " Move: w a s d" << endl;
		cout << " Inventory: i" << endl;
		cout << " Change Active Engimon: c / C / change" << endl;
		cout << " Show Active Engimon: show / sae" << endl;
		cout << " Interact: talk / int" << endl;
		cout << " quit: q / quit / exit" << endl;
		cout << " >> "; 
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
				cout << "Choose between 1-5 !" << endl;
			}
		} while (pil < 1 || pil > 5);
		Engimon chosen = ensiklopediaEngimon[pil - 1][0];
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
		cout << "Hello " << name << "!" << endl;
		Engimon chosen = chooseEngimon();
		player = Player(name, chosen);
	}

	void renderMap(vector<EngimonEnemy> listEngimonLiar)
	{
		map.Render(player, listEngimonLiar);
	}

	void inputCommand()
	{
		printCommandList();
 		string command;
		cin >> command;
		player.command(command);
	}
	vector<EngimonEnemy> spawnEngimon(vector<EngimonEnemy> listEngimonLiar, bool spawn)
	{
		listEngimonLiar = map.MoveListEngimonEnemy(listEngimonLiar, player);
		if (spawn)
		{
			return map.addEngimonEnemy(listEngimonLiar, player);
		}
		else
		{
			return listEngimonLiar;
		}
	}

	void battleEngimon(vector<EngimonEnemy> listEngimonLiar)
	{
		char command;
		if (map.EnemyNear(player, listEngimonLiar) != 999)
		{

			cout << "A Wild " << listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getName() << "(level " <<listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getLevel() << ") " <<  "Appears!" << endl;
			cout << "*Press y to proceed battle and other key to run" << endl;
			cin >> command;
			if (command == 'y')
			{
				//vector<Element> elements;
				//EngimonUser e1(Position(0, 0), "s", "d", 1, elements);
				//EngimonUser e2;
				//EngimonUser e3;
				//EngimonUser e4;

				//player.Add_inv_engimon(e1);
				// player.get_inv_engimon().add_item(e2);
				// player.get_inv_engimon().add_item(e3);
				// player.get_inv_engimon().add_item(e4);

				// cout << player.get_inv_engimon().get_nItem() << endl;

				// player.get_inv_engimon().show_bag();
				int a = Battle::battleEngimon(player, listEngimonLiar[map.EnemyNear(player, listEngimonLiar)]);
				if (a == 1)
				{
					cout << "You Win!" << endl;
					cout << "You retrieve " << listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getName() << "(level " << listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getLevel() << ")!" << endl;
					//cout << player.getActiveEngimon().getExp() << endl;
					int inc_exp;
					if (player.getActiveEngimon().getLevel() >= listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getLevel()){
						inc_exp = 10;
					}else{
						inc_exp = ((abs(player.getActiveEngimon().getLevel() - listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getLevel())) + 1) * 10;
					}
					//int inc_exps = 100;
					//cout << "inc : " << inc_exp << endl;
					int new_exp = player.getActiveEngimon().getExp() + inc_exp;
					//cout << "exp : " << new_exp << endl;
					player.Add_exp(inc_exp);
					//cout << player.getActiveEngimon().getExp() << endl;
					vector<Element> element_active = player.getActiveEngimon().getElements();							   // semua elemen dari engimon aktif
					vector<Element> element_enemy = listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getElements(); // semua elemen dari engimon element

					// get random skill item (sesuai elemen musuh)
					BookOfLore ensiklopedia;
					vector<vector<Skill>> ensiklopediaSkill = ensiklopedia.allSkill();
					vector<vector<Skill>> Skill_enemy;
					for (int i = 0; i < element_enemy.size(); i++)
					{
						// ambil index yang memuat element enemy
						int idx = ensiklopedia.get_idx_skill(element_enemy[i]);
						for (int j = 0; j < ensiklopediaSkill.size(); j++)
						{
							if (idx == j)
							{
								Skill_enemy.push_back(ensiklopediaSkill[j]);
							}
						}
					}
					int idxElement = rand() % Skill_enemy.size();
					int idxSkill = rand() % Skill_enemy[idxElement].size();

					Skill get_skill = Skill_enemy[idxElement][idxSkill];
					Skill skill(get_skill.getSkillId(), get_skill.getMasteryLevel(), get_skill.getBasePower(), get_skill.getSkillName(), get_skill.getElement());

					SkillItem skill_item(skill);

					player.Add_inv_skill(skill_item);

					EngimonUser newEnemy(listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getPosition(), listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getName(), listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getSpecies(), listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getId(), listEngimonLiar[map.EnemyNear(player, listEngimonLiar)].getElements());

					player.Add_inv_engimon(newEnemy);

					listEngimonLiar.erase(listEngimonLiar.begin() + map.EnemyNear(player, listEngimonLiar));
				}
				else
				{
					cout << "Your Engimon is Fainted!" << endl;
					player.changeActiveEngimon();
				}
				
			}
			else
			{
				cout << "okay bubayy" << endl;
				//map.Render(player, listEngimonLiar);
			}
		}
	}
};

int main()
{
	Game g;
	g.printLogo();
	g.initialNameAndEngimon();

	vector<EngimonEnemy> listEngimonLiar;
	int jumlahIterasi = 0;
	while (1)
	{
		try
		{
			g.renderMap(listEngimonLiar);
			g.inputCommand();
			if (jumlahIterasi % 3 == 0 && listEngimonLiar.size() < 5) // tambahin engimon setiap 3 move
			{
				listEngimonLiar = g.spawnEngimon(listEngimonLiar, true);
			}
			else
			{
				listEngimonLiar = g.spawnEngimon(listEngimonLiar, false);
			}
			g.battleEngimon(listEngimonLiar);
			jumlahIterasi++;
		}
		catch (OutOfBoundException &e)
		{
			cout << e.what() << endl;
		}
	}
	return 0;
}