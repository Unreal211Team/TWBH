#include "Battle.h"

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

	Monster& monster = this->actingMonster.getMonster();
	
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
		int choiceAction = battleUi.getValidatedInput("입력해주세요 :", 0, 3);

		switch (choiceAction)
		{
			// 1. 공격 선택 
		case 1:
		{

			bool isAttack = attackChoice(monster);
			if (!isAttack)
			{
				continue;
			}

			// 플레이어의 공격에 몬스터가 죽었을 때
			if (monster.getHealth() == 0)
			{
				// 보상을 지급하는 로직
				getReward(monster);

				// 캐릭터 레벨업 확인하는 로직
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

			// 몬스터의 공격
			actingMonster.doAttack();
			player.takeDamage(actingMonster.getDamage());
			battleUi.displayHitMessage(monster);


			// 몬스터의 공격에 플레이어가 사망했는지 확인하는 로직
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


		// 2. 인벤토리 선택
		case 2:
		{
			displayInventory(&player);
			useItemFromInventory(&player);
			break;
		}


		// 3. 상태창 선택
		case 3:
		{
			string str;
			player.displayStatus();
			cout << "상태창을 나가시려면 아무키나 누르세요";
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

	cout << " 골드 : " << player->getGold() << " gold\n";
	if (inventory.empty())
	{
		cout << " 아이템 : 없음\n" << endl;

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

	cout << "번호를 입력하여 아이템 사용이 가능합니다.\n";
	cout << "0. 인벤토리 닫기\n";

	int itemIndex = getValidatedInput("사용할 아이템 번호를 입력하세요: ", 0, inventory.size());

	if (itemIndex == 0)
	{
		cout << "인벤토리를 닫습니다.\n";
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
		cout << "입력 : ";
		cin >> attackChoice;

		switch (attackChoice)
		{
		case 1:
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
		battleUi.displayRewardMessage(monster, experience, randomGold, drop);
	}
	else
	{
		battleUi.displayRewardMessage(monster, experience, randomGold);
	}
}
