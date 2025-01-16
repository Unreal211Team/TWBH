#include "Battle.h"

using namespace std;

Battle::Battle()
{
	this->actingMonster = ActingMonster();
	battleui = BattleUi();
}

bool Battle::doBattle()
{
	BuffManager* manager = BuffManager::getInstance();
	Character& player = Character::getInstance();

	random_device rd;
	uniform_int_distribution<int> randomG(10, 20);
	uniform_int_distribution<int> randomI(1, 100);

	int randomGold = randomG(rd);
	Monster& monster = this->actingMonster.getMonster();
	
	battleui.spawnMonster(monster);

	// ���� ����
	while (true)
	{
		// ���� ���� ���� (������ ü���� 0���� ũ��.)
		if (monster.getHealth() <= 0)
		{
			break;
		}

		battleui.selectBattleOptions(monster);
		int choiceAction = battleui.getValidatedInput("�Է����ּ��� :", 0, 3);

		switch (choiceAction)
		{

			// 1. ���� ���� 
		case 1:
		{
			int attackChoice;
			battleui.showCurrentManaAndAttack(monster);

			cout << "�Է� : ";
			cin >> attackChoice;

			switch (attackChoice)
			{
			case 1:
				monster.takeDamage(player.getAttack());
				battleui.displayAttackMessage(monster);
				break;
			case 2:
			{
				PowerStrike powerStrike;
				if (player.getMana() < powerStrike.getMana())
				{
					battleui.manaAlert();
					continue;
				}
				else
				{
					powerStrike.use(&player, &monster);
				}
				break;
			}
			case 3:
			{
				MagicClaw magicClaw;
				if (player.getMana() < magicClaw.getMana())
				{
					battleui.manaAlert();
					continue;
				}
				else
				{
					magicClaw.use(&player, &monster);
				}
				break;
			}
			default:
				battleui.displayWrongInput();
				continue;
			}

			// �÷��̾��� ���ݿ� ���Ͱ� �׾��� ��
			if (monster.getHealth() == 0)
			{
				// ������ �����ϴ� ����
				player.addExperience(experience);
				player.addGold(randomGold);

				battleui.displayRewardMessage(monster, experience, randomGold);

				if (randomI(rd) <= itemDrop)
				{
					Item* drop = monster.dropItem();
					player.addItem(drop);
				}


				// ĳ���� ������ Ȯ���ϴ� ����
				if (player.IsLevelUp())
				{
					player.levelUp();
				}

				// ���� ���Ͱ� �������� Ȯ���ϴ� ����
				if (monster.getName() == "Dragon")
				{
					cout << "\n���� " << player.getName() << "�� ���� ������ ��ȭ�� ��������." << endl;
					return true;
				}
				return true;
			}
			

			// ������ ����
			actingMonster.doAttack();
			battleui.displayHitMessage(monster);

			// ������ ���ݿ� �÷��̾ ����ߴ��� Ȯ���ϴ� ����
			if (player.getHealth() == 0)
			{
				player.isDead();
				return false;
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
			player.displayStatus();
			break;
		}
		default:
		{
			cout << "�߸��� �Է°��Դϴ�. \n";
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
			cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���.\n";
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
	cout << inventory[itemIndex - 1]->getName() << " �������� ����߽��ϴ�.\n";
}