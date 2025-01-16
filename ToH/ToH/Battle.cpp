#include "Battle.h"
#include "Report.h"

using namespace std;

Battle::Battle()
{
	this->actingMonster = ActingMonster();
	battleUi = BattleUi();
	this->manager = BuffManager::getInstance();
}

bool Battle::doBattle()
{
	randomGold = randomInt(200, 300);

	// ���� ����
	Monster& monster = this->actingMonster.getMonster();
	REPORT->OnMonsterEvent(monster.getName(), "spawn");

	battleUi.spawnMonster(monster);

	if (player.getLevel() >= 10)
	{
		this->experience = 0;
	}
	return doFight(monster);
}

bool Battle::doFight(Monster& monster)
{
	battleUi.displayClear();
	while (true)
	{
		battleUi.selectBattleOptions(monster);
		int choiceAction = battleUi.getValidatedInput("�Է����ּ��� :", 0, 3);

		switch (choiceAction)
		{
			// 1. ���� ���� 
		case 1:
		{

			bool isAttack = attackChoice(monster);
			if (!isAttack)
			{
				continue;
			}

			// �÷��̾��� ���ݿ� ���Ͱ� �׾��� ��
			if (monster.getHealth() == 0)
			{
				REPORT->OnMonsterEvent(monster.getName(), "kill");
				PlayReport::GetInstance()->OnMonsterEvent(monster.getName(), "Kill");
				// ������ �����ϴ� ����
				getReward(monster);

				// ĳ���� ������ Ȯ���ϴ� ����
				if (player.IsLevelUp())
				{
					player.levelUp();
				}

				if (manager->ActiveBuffsCheck())
				{
					manager->updateBuffs(&player);
				}

				return false;
			}

			// ������ ����
			actingMonster.doAttack();
			player.takeDamage(actingMonster.getDamage());
			battleUi.displayHitMessage(monster);


			// ������ ���ݿ� �÷��̾ ����ߴ��� Ȯ���ϴ� ����
			if (player.getHealth() == 0)
			{
				player.isDead();
				return true;
			}

			if (manager->ActiveBuffsCheck())
			{
				manager->updateBuffs(&player);
			}

			break;
		}


		// 2. �κ��丮 ����
		case 2:
		{
			displayInventory(&player);
			useItemFromInventory(&player);
			break;
		}


		// 3. ����â ����
		case 3:
		{
			string str;
			player.displayStatus();
			cout << "����â�� �����÷��� �ƹ�Ű�� ��������";
			cin >> str;
			break;
		}
		default:
		{
			battleUi.displayWrongInput();
			break;
		}

		}
	}
	

}

int Battle::getValidatedInput(const string& prompt, int minValue, int maxValue)
{
	int input;
	while (true) {
		cout << prompt;
		cin >> input;

		if (cin.fail() || input < minValue || input > maxValue) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			battleUi.displayWrongInput();
		}
		else {
			break;
		}
	}
	return input;
}

void Battle::displayInventory(Character* player)
{
	vector<Item*> inventory = player->getInventory();

	cout << "\n";
	cout << " --- Inventory ---" << endl;

	cout << " ��� : " << player->getGold() << " gold\n";
	if (inventory.empty())
	{
		cout << " ������ : ����\n" << endl;

		cout << " --- --------- ---\n\n";
		return;
	}

	for (int i = 0; i < inventory.size(); i++)
	{
		cout << i + 1 << ". " << inventory[i]->getName() << " ( " << inventory[i]->getPrice() << " gold ) \n";
	}

	cout << " --- --------- ---\n\n";


}

void Battle::useItemFromInventory(Character* player)
{
	vector<Item*> inventory = player->getInventory();

	cout << "��ȣ�� �Է��Ͽ� ������ ����� �����մϴ�.\n";
	cout << "0. �κ��丮 �ݱ�\n";

	int itemIndex = getValidatedInput("����� ������ ��ȣ�� �Է��ϼ���: ", 0, inventory.size());

	if (itemIndex == 0)
	{
		cout << "�κ��丮�� �ݽ��ϴ�.\n";
		return;
	}

	player->useItem(itemIndex - 1);
}

int Battle::randomInt(int start, int end)
{
	random_device rd;
	uniform_int_distribution<int> random(start, end);

	return random(rd);
}

bool Battle::attackChoice(Monster& monster)
{
	int attackChoice;

	while (true)
	{
		battleUi.showCurrentManaAndAttack(monster);
		cout << "�Է� : ";
		cin >> attackChoice;

		switch (attackChoice)
		{
		case 1:
			// �⺻ ���� ���� ����Ʈ
			REPORT->OnBattleEvent("�Ϲݰ���", "BasicAttack", player.getAttack());

			monster.takeDamage(player.getAttack());
			battleUi.displayAttackMessage(monster);
			return true;
		case 2:
		{
			PowerStrike powerStrike;
			if (player.getMana() < powerStrike.getMana())
			{
				battleUi.manaAlert();
				continue;
			}
			else
			{
				// ��ų ���� ���� ����Ʈ -> ��ų Ŭ���� use �ȿ� �ֱ�, why? ��ų ���� �������� ��ų �̸��� �������� �Լ��� ����
				powerStrike.use(&player, &monster);
			}
			return true;
		}
		case 3:
		{
			MagicClaw magicClaw;
			if (player.getMana() < magicClaw.getMana())
			{
				battleUi.manaAlert();
				continue;
			}
			else
			{
				// ��ų ���� ���� ����Ʈ -> ��ų Ŭ���� use �ȿ� �ֱ�
				magicClaw.use(&player, &monster);
			}
			return true;
		}
		case 4:
		{
			return false;
		}
		default:
			battleUi.displayWrongInput();
			continue;
		}
	}
	
}

void Battle::getReward(Monster& monster)
{


	Item* drop = monster.dropItem();
	if (randomInt(1, 100) <= itemDropRate)
	{
		battleUi.displayRewardMessage(monster, experience, randomGold, drop->getName());
		REPORT->OnItemEvent(drop->getName(), "Acquire");
	}
	else
	{
		battleUi.displayRewardMessage(monster, experience, randomGold);
	}
}
