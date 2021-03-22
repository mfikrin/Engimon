#include "Map.hpp"
#include "Player.hpp"
#include "BookOfLore.hpp"
//#include "EngimonUser.hpp"
#include <iostream>
using namespace std;

int main(){
	BookOfLore ensiklopedia;
	vector<vector<Engimon>> ensiklopediaEngimon = ensiklopedia.allEngimon();
	vector<vector<Skill>> ensiklopediaSkill = ensiklopedia.allSkill();


	int indexElementEngimon = rand() % ensiklopediaEngimon.size();
	int indexEngimon = rand() % ensiklopediaEngimon[indexElementEngimon].size();


	Engimon dapet = ensiklopediaEngimon[indexElementEngimon][indexEngimon];

	Map peta("map.txt");

	Player pemain("Randy" , dapet);

	peta.BacaFile();
	peta.Render(pemain);
	char command;
	do{
		cin >> command;
		pemain.Move(command);
		peta.Render(pemain);
	}while(command != 'q');
	return 0;
}
