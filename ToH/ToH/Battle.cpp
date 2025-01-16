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

	// 전투 로직
	while (true)
	{
		// 전투 시작 조건 (몬스터의 체력이 0보다 크다.)
		if (monster.getHealth() <= 0)
		{
			break;
		}

		battleui.selectBattleOptions(monster);
		int choiceAction = battleui.getValidatedInput("입력해주세요 :", 0, 3);

		switch (choiceAction)
		{

			// 1. 공격 선택 
		case 1:
		{
			int attackChoice;
			battleui.showCurrentManaAndAttack(monster);

			cout << "입력 : ";
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

			// 플레이어의 공격에 몬스터가 죽었을 때
			if (monster.getHealth() == 0)
			{
				// 보상을 지급하는 로직
				player.addExperience(experience);
				player.addGold(randomGold);

				battleui.displayRewardMessage(monster, experience, randomGold);

				if (randomI(rd) <= itemDrop)
				{
					Item* drop = monster.dropItem();
					player.addItem(drop);
				}


				// 캐릭터 레벨업 확인하는 로직
				if (player.IsLevelUp())
				{
					player.levelUp();
				}

				// 죽은 몬스터가 보스인지 확인하는 로직
				if (monster.getName() == "Dragon")
				{
					cout << "\n영웅 " << player.getName() << "에 의해 세계의 평화가 지켜졌다." << endl;
					return true;
				}
				return true;
			}
			

			// 몬스터의 공격
			actingMonster.doAttack();
			battleui.displayHitMessage(monster);

			// 몬스터의 공격에 플레이어가 사망했는지 확인하는 로직
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
			player.displayStatus();
			break;
		}
		default:
		{
			cout << "잘못된 입력값입니다. \n";
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
			cout << "잘못된 입력입니다. 다시 시도해주세요.\n";
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
	cout << inventory[itemIndex - 1]->getName() << " 아이템을 사용했습니다.\n";
}