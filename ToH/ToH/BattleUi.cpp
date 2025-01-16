#include "BattleUi.h"

void BattleUi::spawnMonster(const Monster& monster) const
{
	Character& player = Character::getInstance();
	if (monster.getName() == "Dragon")
	{
		cout << "�� �� �� �� �� ���� ";
		cout << "���� Lv." << player.getLevel() << " " << monster.getName() << " ����!�� �� �� �� �� " << endl;
		monster.displayArt();
	}
	else if (monster.getName().find("Elite") != string::npos) {	//find ��� ã�� ���ڰ� ������ npos��ȯ�ϹǷ� !=
		cout << "�� �� �� ����Ʈ ";
		cout << "���� Lv." << player.getLevel() << " " << monster.getName() << " ����! �� �� �� " << endl;
		monster.displayArt();
	}
	else {
		cout << "���� Lv." << player.getLevel() << " " << monster.getName() << " ����! " << endl;

		monster.displayArt();
	}
		cout << "\n-- Monster status --" << endl;
		cout << "ü��: " << monster.getHealth();
		cout << "\n���ݷ�: " << monster.getAttack() << "\n";
		cout << "----- ------ -----\n\n";

		cout << "\n--------������ �غ��ϼ���!----------\n\n�غ� �Ǽ����� �ƹ�Ű�� ��������";
		string str;
		cin >> str;
		displayClear();
	
}

void BattleUi::displayMonsterStats(const Monster& monster) const
{
	monsterDisplay(monster);
	stringstream ss;
	ss << "\n-- Monster status --\nü��: " << monster.getHealth() << "\n���ݷ�: " << monster.getAttack() << "\n----- ------ -----\n\n";
	cout << ss.str();
}

void BattleUi::selectBattleOptions(const Monster& monster) const
{
	displayMonsterStats(monster);
	displayShortStatus();

	stringstream ss;
	ss << "------------------------------\n1. ����   2. �κ��丮   3. ����â\n------------------------------\n\n";
	cout << ss.str();
}

void BattleUi::showCurrentManaAndAttack(const Monster& monster) const
{
	Character& character = Character::getInstance();
	stringstream ss;
	ss << "\n\n-----------------------------------------------------------\n1. �Ϲݰ��� 2. �Ŀ���Ʈ����ũ(30) 3. ����Ŭ��(60) 4. ������ ���\n-----------------------------------------------------------\n\n";
	cout << ss.str();
}

void BattleUi::displayAttackMessage(const Monster& monster) const
{
	stringstream ss;
	Character& character = Character::getInstance();
	ss << endl << character.getName() << "��(��) " << monster.getName() << "�� �����մϴ� !\n" << monster.getName() << "�� ü��: " << monster.getHealth() << endl;
	cout << ss.str();
}

void BattleUi::displayHitMessage(const Monster& monster) const
{
	Character& character = Character::getInstance();
	stringstream ss;
	ss << endl << monster.getName() << "��(��) " << character.getName() << "�� �����մϴ� !\n" << character.getName() << "�� ü��: " << character.getHealth() << endl;
	
}

void BattleUi::displayRewardMessage(const Monster& monster, const int exp, const int gold, Item* item) const
{
	stringstream ss;
	Character& character = Character::getInstance(); 
	ss << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" << monster.getName() << " óġ!\n" << endl;
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
	cout << "\n�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���.\n\n";
}

void BattleUi::manaAlert() const
{
	cout << "\n������ �����մϴ�!\n\n" << endl;
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