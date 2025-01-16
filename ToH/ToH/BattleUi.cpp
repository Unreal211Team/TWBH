#include "BattleUi.h"

void BattleUi::spawnMonster(const Monster& monster) const
{
	Character& player = Character::getInstance();
	if (monster.getName() == "Dragon")
	{
		cout << "☆ ★ ☆ ★ ☆ 보스 ";
		cout << "몬스터 Lv." << player.getLevel() << " " << monster.getName() << " 등장!☆ ★ ☆ ★ ☆ " << endl;
		monster.displayArt();
	}
	else if (monster.getName().find("Elite") != string::npos) {	//find 사용 찾는 문자가 있으면 npos반환하므로 !=
		cout << "☆ ★ ☆ 엘리트 ";
		cout << "몬스터 Lv." << player.getLevel() << " " << monster.getName() << " 등장! ☆ ★ ☆ " << endl;
		monster.displayArt();
	}
	else {
		cout << "몬스터 Lv." << player.getLevel() << " " << monster.getName() << " 등장! " << endl;

		monster.displayArt();
	}
		cout << "\n-- Monster status --" << endl;
		cout << "체력: " << monster.getHealth();
		cout << "\n공격력: " << monster.getAttack() << "\n";
		cout << "----- ------ -----\n\n";

		cout << "\n--------전투를 준비하세요!----------\n\n준비가 되셨으면 아무키나 누르세요(space bar제외)";
		string str;
		cin >> str;
		displayClear();
	
}

void BattleUi::displayMonsterStats(const Monster& monster) const
{
	monsterDisplay(monster);
	stringstream ss;
	ss << "\n-- Monster status --\n체력: " << monster.getHealth() << "\n공격력: " << monster.getAttack() << "\n----- ------ -----\n\n";
	cout << ss.str();
}

void BattleUi::selectBattleOptions(const Monster& monster) const
{
	displayMonsterStats(monster);
	displayShortStatus();

	stringstream ss;
	ss << "------------------------------\n1. 공격   2. 인벤토리   3. 상태창\n------------------------------\n\n";
	cout << ss.str();
}

void BattleUi::showCurrentManaAndAttack(const Monster& monster) const
{
	Character& character = Character::getInstance();
	stringstream ss;
	ss << "\n\n-----------------------------------------------------------\n1. 일반공격 2. 파워스트라이크(30) 3. 매직클로(60) 0. 공격을 취소\n-----------------------------------------------------------\n\n";
	cout << ss.str();
}

void BattleUi::displayAttackMessage(const Monster& monster) const
{
	stringstream ss;
	Character& character = Character::getInstance();
	ss << endl << character.getName() << "이(가) " << monster.getName() << "을 공격합니다 !\n" << monster.getName() << "의 체력: " << monster.getHealth() << endl;
	cout << ss.str();
}

void BattleUi::displayHitMessage(const Monster& monster) const
{
	Character& character = Character::getInstance();
	stringstream ss;
	ss << endl << monster.getName() << "이(가) " << character.getName() << "을 공격합니다 !\n" << character.getName() << "의 체력: " << character.getHealth() << endl;
	
}

void BattleUi::displayRewardMessage(const Monster& monster, const int exp, const int gold, Item* item) const
{
	stringstream ss;
	Character& character = Character::getInstance(); 
	ss << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" << monster.getName() << " 처치!\n" << endl;
	cout << ss.str();
	character.addExperience(exp);
	character.addGold(gold);

	if (item != nullptr)
	{
		character.addItem(item);
	}
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n";
}

void BattleUi::monsterDisplay(const Monster& monster) const
{
	monster.displayArt();
}

int BattleUi::getValidatedInput(const string& prompt, int minValue, int maxValue)
{
	int input;
	while (true) {
		cout << prompt;
		cin >> input;

		if (cin.fail() || input < minValue || input > maxValue) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			displayWrongInput();
		}
		else {
			break;
		}
	}
	return input;
}

void BattleUi::displayWrongInput() const
{
	cout << "\n잘못된 입력입니다. 다시 시도해주세요.\n\n";
}

void BattleUi::manaAlert() const
{
	cout << "\n마나가 부족합니다!\n\n" << endl;
}

void BattleUi::displayShortStatus() const
{
	Character& player = Character::getInstance();
	stringstream ss;

	ss << "\nHP: " << player.getHealth() << "/" << player.getMaxHealth();
	ss << "  MP: " << player.getMana() << "/" << player.getMaxMana();
	ss << "  EXP: " << player.getExperience() << "/" << player.getMaxExperience();
	ss << "\n\n";

	cout << ss.str();
}

void BattleUi::displayClear() const
{
	cout << system("cls");
}

void BattleUi::exitmenu() const
{
	cout << "나가시려면 0을 누르세요" << endl;
}