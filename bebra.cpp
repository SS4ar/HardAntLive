#include <iostream>
#include"Header1.h"


int main() {
	int res1, res2, res3;
	res1 = res2 = res3 = 0;
	int day = 1;
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	Colony red("красные", 17, 9, 1);
	Colony black("черные", 13, 6, 1);
	Colony green("зеленые", 16, 6, 1);
	red.squad->push_back(Queen("Изабелла", 3, 3, 1, 5, 24, 5, 22));
	black.squad->push_back(Queen("Нефертити", 1, 3, 2, 3, 17, 7, 17));
	green.squad->push_back(Queen("Нефертити", 2, 5, 1, 3, 24, 7, 24));
	Pile kucha1(32, 20, 0, 45);
	Pile kucha2(23, 15, 0, 44);
	Pile kucha3(40, 41, 49, 43);
	Pile kucha4(31, 44, 0, 0);
	Pile kucha5(25, 24, 0, 34);
	
	for (int  i = 15; i >= 0; --i)
	{
		cout << "-----------------------------------------------------------------------------------" << endl;
		
		if (red.population->size() < 27) red.grow();
		if (black.population->size() < 20) black.grow();
		if (green.population->size() < 23) green.grow();
		cout << day << " День. ";
		day++;
		cout << i << " Дней до засухи" << endl;
		int a = rand() % 2 + 1;
		switch (a)
		{
		case 1:
			red.hike_squad();
			black.hike_squad();
			green.hike_squad();
			break;
		case 2:
			red.hike_squad();
			black.hike_squad();
			green.hike_squad();
			int b = rand() % 6 + 1;
			switch (b)
			{
			case 1:
				red.mine(kucha2);
				black.mine(kucha3);
				green.mine(kucha2);
				red.squad->pop_back();
				red.population->pop_back();
				green.squad->pop_back();
				green.population->pop_back();
				break;
			case 2:
				red.mine(kucha1);
				black.mine(kucha3);
				green.mine(kucha2);
				red.squad->pop_back();
				red.population->pop_back();
				break;
			case 3:
				red.mine(kucha4);
				black.mine(kucha3);
				green.mine(kucha1);
				red.squad->pop_back();
				red.population->pop_back();
				red.squad->pop_back();
				red.population->pop_back();
				red.squad->pop_back();
				red.population->pop_back();
				break;
			case 4:
				red.mine(kucha2);
				black.mine(kucha1);
				green.mine(kucha5);
				black.squad->pop_back();
				black.population->pop_back();
				black.squad->pop_back();
				black.population->pop_back();
				break;
			case 5:
				red.mine(kucha5);
				black.mine(kucha4);
				green.mine(kucha1);
				green.squad->pop_back();
				green.population->pop_back();
				black.squad->pop_back();
				black.population->pop_back();
				green.squad->pop_back();
				green.population->pop_back();
				break;
			case 6:
				red.mine(kucha2);
				black.mine(kucha1);
				green.mine(kucha4);
				green.squad->pop_back();
				green.population->pop_back();
				black.squad->pop_back();
				black.population->pop_back();
				green.squad->pop_back();
				green.population->pop_back();
				switch (rand()%3+1)
				{
				case 1:
					red.population->push_back(Death());
					for (int i = 0; i < red.population->size(); i++)
					{
						red.population->pop_back();
					}
					break;
				case 2:
					green.population->push_back(Death());
					for (int i = 0; i < green.population->size(); i++)
					{
						green.population->pop_back();
					}
					break;
				case 3:
					black.population->push_back(Death());
					for (int i = 0; i < green.population->size(); i++)
					{
						green.population->pop_back();
					}
					break;
				}
				break;
			}
			break;
		}
		if (red.population->size() > 0) red.info_colony();
		else cout << "Колония красных погибла" << endl;
		if (green.population->size() > 0) green.info_colony();
		else cout << "Колония зеленых погибла" << endl;
		if (black.population->size() > 0) black.info_colony();
		else cout << "Колония черных погибла" << endl;
		cout << "\n\n\n------------------------------------------------------------------------------------------------------------\n\n\n\n";
		cout << "куча 1: ";
		kucha1.info();
		cout << "куча 2: ";
		kucha2.info();
		cout << "куча 3: ";
		kucha3.info();
		cout << "куча 4: ";
		kucha4.info();
		cout << "куча 5: ";
		kucha5.info();
		system("pause");
	}
	
	if (red.population->size() > 0) res1 = red.branch_cnt + red.leaf_cnt + red.rock_cnt + red.dewdrop_cnt;
	if (green.population->size() > 0) res2 = black.branch_cnt + black.leaf_cnt + black.rock_cnt + black.dewdrop_cnt;
	if (black.population->size() > 0) res3 = green.branch_cnt + green.leaf_cnt + green.rock_cnt + green.dewdrop_cnt;
	if (res1 > res2 and res1 > res3) {
		cout << "Засуху пережила колония красных, с запасами: \n" << red.branch_cnt << " веточек\t" << red.dewdrop_cnt << " росинок\t" << red.rock_cnt << " камешков\t" << red.leaf_cnt << " листиков\t";
	}if (res2 > res1 and res2 > res3) {
		cout << "Засуху пережила колония черных, с запасами: \n" << black.branch_cnt << " веточек\t" << black.dewdrop_cnt << " росинок\t" << black.rock_cnt << " камешков\t" << black.leaf_cnt << " листиков\t";
	}if (res3 > res2 and res3 > res1) {
		cout << "Засуху пережила колония зеленых, с запасами: \n" << green.branch_cnt << " веточек\t" << green.dewdrop_cnt << " росинок\t" << green.rock_cnt << " камешков\t" << green.leaf_cnt << " листиков\t";
	}
	system("pause");
}