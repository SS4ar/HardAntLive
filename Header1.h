#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
class Colony;
class Worker;
using namespace std;
class Pile
{
public:
	int branch_cnt;
	int leaf_cnt;
	int rock_cnt;
	int dewdrop_cnt;
	Pile() {};
	Pile(int branch_cnt, int leaf_cnt, int rock_cnt, int dewdrop_cnt)
	{
		this->branch_cnt = branch_cnt;
		this->rock_cnt = rock_cnt;
		this->leaf_cnt = leaf_cnt;
		this->dewdrop_cnt = dewdrop_cnt;
	};
	void info() {
		if (branch_cnt == 0 and leaf_cnt == 0 and rock_cnt == 0 and dewdrop_cnt == 0) cout << "истощена" << endl;
		else cout << "к= " << rock_cnt << ", л=" << leaf_cnt << ", в=" << branch_cnt << ", р=" << dewdrop_cnt << endl;
	};
};



class Ant
{
public:
	friend Worker;
	friend Colony;
	string prefix;
	string type;
	int hp;
	int armor;
	int damage;
	Ant() {
		
	}
	Ant(string type, int hp, int armor, int damage)
	{
		this->prefix = prefix;
		this->type = type;
		this->hp = hp;
		this->armor = armor;
		this->damage = damage;
	}
	void info()
	{
		cout << "Я " << prefix << type << " cейчас у меня " << hp << " единиц здоровья" << endl;
	}
	void info_queen() {

	}
	int beat(Ant& attacked1)
	{
		if (attacked1.type == "Рабочий") attacked1.hp = 0;
		else if (attacked1.armor < this->damage) attacked1.hp = attacked1.hp + attacked1.armor - this->damage;

		return attacked1.hp;
	}
	
};


class Queen :
	public Ant
{
private:
	string name;
	int min_grow_days;
	int max_grow_days;
	int min_crt_queens;
	int max_crt_queens;
public:
	friend Colony;
	Queen() {
	}
	Queen(string name, int min_grow_days, int max_grow_days, int min_crt_queens, int max_crt_queens, int hp, int armor, int damage)
	{
		this->name = name;
		this->max_crt_queens = max_crt_queens;
		this->min_crt_queens = min_crt_queens;
		this->max_grow_days = max_grow_days;
		this->min_grow_days = min_grow_days;
		this->hp = hp;
		this->armor = armor;
		this->damage = damage;
	}
};


class Warrior :
	public Ant
{
public:
	Warrior() {
		type = "Воин";
		int a = rand() % 5 + 1;
		switch (a)
		{
		case 1:
			this->prefix = "элитный худой";
			break;
		case 2:
			this->prefix = "продвинутый неряшливый";
			break;
		case 3:
			this->prefix = "продвинутый";
			break;
		case 4:
			this->prefix = "элитный";
			break;
		case 5:
			this->prefix = "продвинутый неряшливый";
			break;
		}
		if (!prefix.find("элитный")) { hp = 8; armor = 4; damage = 5; }
		if (!prefix.find("продвинутый")) {hp = 6; armor = 2; damage = 3;}
		if (!prefix.find("легендарный")) { hp = 10*2; armor = 6*2; damage = 4; }
		if (!prefix.find("продвинутый неряшливый")) { hp = 6; armor = 2/2; damage = 3; }

	}
	int beat_two_obj(Ant& attacked1, Ant& attacked2)
	{
	
		if (attacked1.type == "Рабочий" and attacked2.type == "Рабочий") attacked1.hp = attacked2.hp = 0;
		if (attacked1.type == "Рабочий" and attacked2.type != "Рабочий") {
			attacked1.hp = 0;
			attacked2.hp = attacked2.hp + attacked2.armor - this->damage;
		}
		if (attacked1.type != "Рабочий" and attacked2.type == "Рабочий") {
			attacked2.hp = 0;
			attacked1.hp = attacked1.hp + attacked1.armor - this->damage;
		}
		if (attacked1.type != "Рабочий" and attacked2.type != "Рабочий") {
			attacked1.hp = attacked1.hp + attacked1.armor - this->damage;
			attacked2.hp = attacked2.hp + attacked2.armor - this->damage;
		}
		return attacked1.hp, attacked2.hp;
	}
	int beat_two_obj_dd(Ant& attacked1, Ant& attacked2) {
		{
			
			if (attacked1.type == "Рабочий" and attacked2.type == "Рабочий") attacked1.hp = attacked2.hp = 0;
			if (attacked1.type == "Рабочий" and attacked2.type != "Рабочий") {
				attacked1.hp = 0;
				attacked2.hp = attacked2.hp + attacked2.armor - this->damage * 2;
			}
			if (attacked1.type != "Рабочий" and attacked2.type == "Рабочий") {
				attacked2.hp = 0;
				attacked1.hp = attacked1.hp + attacked1.armor - this->damage * 2;
			}
			if (attacked1.type != "Рабочий" and attacked2.type != "Рабочий") {
				attacked1.hp = attacked1.hp + attacked1.armor - this->damage * 2;
				attacked2.hp = attacked2.hp + attacked2.armor - this->damage * 2;
			}
			return attacked1.hp, attacked2.hp;
		}
	}
	int beat_three_obj(Ant& attacked1, Ant& attacked2, Ant& attacked3) {
		
			if (attacked1.type == "Рабочий" and attacked2.type == "Рабочий" and attacked3.type == "Рабочий") attacked1.hp = attacked2.hp = attacked3.hp = 0;
			if (attacked1.type == "Рабочий" and attacked2.type == "Рабочий" and attacked3.type != "Рабочий") {
				attacked1.hp = attacked2.hp = 0;
				attacked3.hp = attacked3.hp + attacked3.hp - this->damage;
			}
			if (attacked1.type == "Рабочий" and attacked2.type != "Рабочий" and attacked3.type == "Рабочий") {
				attacked1.hp = attacked3.hp = 0;
				attacked2.hp = attacked2.hp + attacked2.hp - this->damage;
			}
			if (attacked1.type != "Рабочий" and attacked2.type == "Рабочий" and attacked3.type == "Рабочий") {
				attacked3.hp = attacked2.hp = 0;
				attacked1.hp = attacked1.hp + attacked1.hp - this->damage;
			}
			if (attacked1.type == "Рабочий" and attacked2.type != "Рабочий" and attacked3.type != "Рабочий") {
				attacked1.hp = 0;
				attacked3.hp = attacked3.hp + attacked3.hp - this->damage;
				attacked2.hp = attacked2.hp + attacked2.hp - this->damage;
			}
			if (attacked1.type != "Рабочий" and attacked2.type == "Рабочий" and attacked3.type != "Рабочий") {
				attacked2.hp = 0;
				attacked1.hp = attacked1.hp + attacked1.hp - this->damage;
				attacked3.hp = attacked3.hp + attacked3.hp - this->damage;
			}
			if (attacked1.type != "Рабочий" and attacked2.type != "Рабочий" and attacked3.type == "Рабочий") {
				attacked3.hp = 0;
				attacked1.hp = attacked1.hp + attacked1.hp - this->damage;
				attacked2.hp = attacked2.hp + attacked2.hp - this->damage;
			}
			if (attacked1.type != "Рабочий" and attacked2.type != "Рабочий" and attacked3.type == "Рабочий") {
				attacked1.hp = attacked1.hp + attacked1.hp - this->damage;
				attacked2.hp = attacked2.hp + attacked2.hp - this->damage;
				attacked3.hp = attacked3.hp + attacked3.hp - this->damage;
			}
		
		return attacked1.hp, attacked2.hp, attacked3.hp;
	}
};



class Worker :
	public Ant
{
private:

public:
	friend Colony;
	int branchtake;
	int leaftake;
	int dewdroptake;
	int rocktake;
	Worker() {
		type = "Рабочий";
		damage = 0;
		branchtake = 0;
		leaftake = 0;
		dewdroptake = 0;
		rocktake = 0;
		int a = rand() % 6 + 1;
		switch (a)
		{
		case 1:
			this->prefix = "легендарный сильный";
			break;
		case 2:
			this->prefix = "старший";
			break;
		case 3:
			this->prefix = "продвинутый";
			break;
		case 4:
			this->prefix = "старший забывчивый";
			break;
		case 5:
			this->prefix = "обычный";
			break;
		case 6:
			this->prefix = "старший капризный";
			break;
		}
		if (!prefix.find("старший")) { 
			hp = 2; armor = 1; 
		}		
		if (!prefix.find("продвинутый")) {
			hp = 6; armor = 2; 
		}
		if (!prefix.find("обычный")) { 
			hp = 1; armor = 0; 
		}
		if (!prefix.find("легендарный")) {
			hp = 10; armor = 6; 
		}
	}

	void prefix_check_worker(Ant& check) {
		int a = rand() % 2;
		if (!check.prefix.find("сильный")) {
			dewdroptake = 2;
			leaftake = 4;
		}
		if (!check.prefix.find("продвинутый")) {
			switch (a){
			case 1:
				leaftake = 2;
			case 2:
				branchtake = 2;
			}
		}
		if (!check.prefix.find("забывчивый")) {
			switch (a){
			case 1:
				dewdroptake = 2;
			}
		}
		if (!check.prefix.find("старший")) {
			switch (a){
			case 1:
				dewdroptake = 1;
			case 2:
				leaftake = 1;
			}
			if (!check.prefix.find("обычный")) dewdroptake = 1;
				
		}
	}
	
};
class Death : public Ant
{
public:
	Death() {
		type = "муравей";
		hp = armor = damage = 1;
		prefix = "Легендарный мифический";

	}
private:

};


class Special : public Ant
{
public:

	int branchtake;
	int leaftake;
	int dewdroptake;
	int rocktake;
	Special() {
		damage = 0;
		branchtake = 0;
		leaftake = 0;
		dewdroptake = 0;
		rocktake = 0;
		int a = rand() % 3 + 1;
		switch (a)
		{
		case 1:
			type = "пчела";
			prefix = "ленивый неуязвимый мирный вежливый";
		case 2:
			type = "стрекоза";
			prefix = "трудолюбивый обычный мирный талантливый";
		case 3:
			type = "толстоножка";
			prefix = "трудолюбивый неуязвимый мирный невезучий";
		}
		if (!type.find("пчела")) { hp = 29; armor = 8; }
		if (!type.find("стрекоза")) { hp = 20; armor = 7; }
		if (!type.find("толстоножка")) { hp = 29; armor = 9; }

	}
private:
};

class Colony :
	public Pile
{
private:

public:
	friend Queen;
	friend Ant;
	vector<Ant>* population = new vector<Ant>;
	vector<Ant>* squad = new vector<Ant>;
	string colony_name;
	int worker_unit_cnt;
	int warrior_unit_cnt;
	int special_unit_cnt;
	
	Colony() {
		worker_unit_cnt = 0;
		warrior_unit_cnt = 0;
		special_unit_cnt = 0;
		branch_cnt = 0;
		leaf_cnt = 0;
		rock_cnt = 0;
		dewdrop_cnt = 0;
		}
	Colony(string colony_name, int worker_unit_cnt, int warrior_unit_cnt, int special_unit_cnt) {
		this->colony_name = colony_name;
		this->worker_unit_cnt = worker_unit_cnt;
		this->warrior_unit_cnt = warrior_unit_cnt;
		this->special_unit_cnt = special_unit_cnt;

		for (int i = 0; i < worker_unit_cnt; i++)
		{
			population->push_back(Worker());
		}
		for (int i = 0; i < warrior_unit_cnt; i++)
		{
			population->push_back(Warrior());
		}
		for (int i = 0; i < special_unit_cnt; i++)
		{
			population->push_back(Special());
		}
	}
	~Colony() {
		delete population;
	}
	void info_population() {
		for (int i = 0; i < population->size(); i++)
		{
			cout << "\n";
			cout << (*population)[i].prefix << " ";
			cout << (*population)[i].type << " ";
			cout << (*population)[i].hp << " ";
			cout << (*population)[i].armor << " ";
			cout << (*population)[i].damage << " ";
		}
	}
	void info_squad() {
		for (int i = 0; i < squad->size(); i++)
		{
			cout << "\n";
			cout << (*squad)[i].prefix << " ";
			cout << (*squad)[i].type << " ";
			cout << (*squad)[i].hp << " ";
			cout << (*squad)[i].armor << " ";
			cout << (*squad)[i].damage << " ";
		}
	}
	void info_colony() {
		int workcnt, warcnt, specnt;
		workcnt = warcnt = specnt = 0;
		cout << "Колония  " << colony_name << ":" << endl;
		if (colony_name == "красные") cout << "---Королева<Изабелла>" << endl;
		if (colony_name == "черные" or colony_name == "зеленые") cout << "---Королева<Нефертити>"  << endl;
		cout << "---Ресурсы: к=" << rock_cnt << ", л=" << leaf_cnt << ", в=" << branch_cnt << ", р="  << dewdrop_cnt << endl;
		for (int i = 0; i < population->size(); i++)
		{
			if ((*population)[i].type == "Рабочий") workcnt++;
			if ((*population)[i].type == "Воин") warcnt++;
			if ((*population)[i].type == "пчела" or (*population)[i].type == "стрекоза" or (*population)[i].type == "толстоножка") specnt++;
		}
		cout << "---Популяция  " << population->size() << ": р=" << workcnt << ", в=" << warcnt << ", o=" << specnt << endl;
	}
	void hike_squad() {
		int cnt_squad = (warrior_unit_cnt + worker_unit_cnt + special_unit_cnt) / 2;
		int a = rand() % cnt_squad + 1;
		for (int i = 0; i < a; i++)
		{
			int rnd1 = a;
			int rnd = rand() % rnd1 + i;
			if ((*population)[i].type != "Королева") squad->push_back((*population)[rnd]);
				
		}
	}
	void grow() {
		int a = rand() % 3 + 1;
		switch (a)
		{
		case 1:
			population->push_back(Warrior());
			break;
		case 2:
			population->push_back(Worker());
			break;
		case 3:
			population->push_back(Special());
			break;
		}
	}
	void mine(Pile& takehere);

};

void Colony::mine(Pile& takehere) {

	for (int i = 0; i < squad->size()/2; i++)
	{
			branch_cnt += rand() % 2;
			takehere.branch_cnt -= rand() % 2;
			dewdrop_cnt += rand() % 2;
			takehere.dewdrop_cnt -= rand() % 2;
			rock_cnt += rand() % 2;
			takehere.rock_cnt -= rand() % 2;
			leaf_cnt += rand() % 2;
			takehere.leaf_cnt -= rand() % 2;
			if (takehere.dewdrop_cnt <= 0) takehere.dewdrop_cnt = 0;
			if (takehere.rock_cnt <= 0) takehere.rock_cnt = 0;
			if (takehere.leaf_cnt <= 0) takehere.leaf_cnt = 0;
			if (takehere.branch_cnt <= 0) takehere.branch_cnt = 0;
	}
	
}




