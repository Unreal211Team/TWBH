#include <iostream>
#include "GameManager.h"
#include "Shop.h"
#include "BossMonster.h"

using namespace std;

int main()
{
	GameManager* gameManager = GameManager::getInstance();
	Shop* shop = Shop::getInstance();
	
	string heroName = "";

	cout << "   ☆★ Game Start ★☆\n";
	cout << "==================================================\n" << endl;
	cout << "캐릭터 이름을 입력하세요: ";

	// 이름 입력 받기
	cin >> heroName;

	Character* character = Character::getInstance(heroName);
	Monster* monster = nullptr;
	
	system("cls");

	cout << "생성 완료! \n";

	character->displayStatus();

	string action = "";

	bool isDigit = false;	//입력값이 숫자인지 아닌지 판단할 때 쓰임
	int act = 0;

	while (character->getLevel() < 10 && character->getHealth() > 0)
	{

		// 배틀
		cout << "\n==================================================" << endl;
		monster = gameManager->generateMonster(character->getLevel());
		
		// 전투
		gameManager->battle(character, monster);

		// 사망
		if (character->getHealth() == 0)
		{
			break;
		}


		// 상점
		cout << "\n==================================================\n" << endl;	// 추후 상점 로직은 main에서 분리가 필요 할지도?
		cout << "상점을 방문하시겠습니까?" << endl;
		cout << "Y)한다 그외)안한다: ";
		cin >> action;


		if (action.compare("y") == 0 || action.compare("Y") == 0)
		{
			while (true)
			{
				cout << "\n골드: " << character->getGold() << endl;
				cout << "1)사기 2)팔기 3)겜블 Q)나가기: ";
				cin >> action;

				if (action.compare("Q") == 0 || action.compare("q") == 0)
				{
					break;
				}

				// 상점. 아이템 사기
				if (action.compare("1") == 0)
				{
					cout << endl;
					shop->displayItems();
					cout << "구매 번호 Q)돌아가기: ";
					cin >> action;

					if (action.compare("Q") == 0 || action.compare("q") == 0)
					{
						continue;
					}

					// 입력 값이 숫자인지 판별
					isDigit = true;

					for (char actionChar : action)
					{
						if (!isdigit(actionChar))
						{
							isDigit = false;
							break;
						}
					}

					// 입력 값이 숫자가 아니라면
					if (!isDigit)
					{
						cout << "잘못된 입력입니다." << endl;
						continue;
					}

					act = stoi(action);

					if (act <= 0 || act > 2)	// shop에서 판매하는 아이템 개수가 2개임. 하드 코딩 개선 필요**
					{
						cout << "잘못된 입력입니다." << endl;
						continue;
					}

					shop->buyItem(act - 1, character);
					cout << endl;
				}

				// 상점. 아이템 팔기
				else if (action.compare("2") == 0)
				{
					cout << endl;
					gameManager->displayInventory(character);

					if (character->getInventory().size() == 0)
					{
						cout << "판매 가능한 아이템이 없습니다." << endl;
						continue;
					}

					cout << "원가의 60% 가격으로 판매합니다." << endl;

					cout << "판매 번호 Q)돌아가기: ";
					cin >> action;

					if (action.compare("Q") == 0 || action.compare("q") == 0)
					{
						continue;
					}

					// 입력 값이 숫자인지 판별
					isDigit = true;

					for (char actionChar : action)
					{
						if (!isdigit(actionChar))
						{
							isDigit = false;
							break;
						}
					}

					// 입력 값이 숫자가 아니라면
					if (!isDigit)
					{
						cout << "잘못된 입력입니다.1" << endl;
						continue;
					}

					act = stoi(action);

					if (act > character->getInventory().size() || act <= 0)
					{
						cout << "잘못된 입력입니다.2" << endl;
						continue;
					}

					shop->sellItem(act - 1, character);
					cout << endl;
				}

				// 상점. 겜블
				else if (action.compare("3") == 0)
				{
					shop->playGamble(character);
				}

				else // 1, 2, 3, Q 외에 다른 값 입력
				{
					cout << "잘못된 입력입니다." << endl;
				}
			}
		}
	}

	if (character->getLevel() < 10)
	{
		return 0;
	}

	cout << "\n" << endl;

	// 레벨이 10이면 보스전, 추후에 main에서 분리 필요할지도?

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << "Warning! ";
		}
		cout << endl;
	}

	cout << "\n --- Boss 출현! ---\n" << endl;

	monster = new BossMonster();

	gameManager->battle(character, monster);

	delete shop;
	delete character;
	delete gameManager;

	return 0;
}