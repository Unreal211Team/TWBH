#pragma once
#include "Character.h"

class BuffCheck
{
private:
	bool useCheck;
	int useCount;

public:
	//생성자 하나는 기본생성자 하나는 다른용도
	BuffCheck():useCheck(false), useCount(0){}
	BuffCheck(string use): useCheck(false), useCount(3) {}

	//중복체크
	void dupliCheck() {

	}

	//버프 카운팅
	void buffCounting(Character* player) {
		if (useCheck)
		{
			useCount--;
			if (useCount > 0)
			{
				cout << "버프 남은 턴 : " << useCount << endl;
			}
			else {
				player->endBuff();
				cout << "버프가 종료되었습니다!" << useCount << endl;
			}
		}
	}

	//값 리셋
	void resetBuff(Character* player) {
		useCheck = false;
		useCount = 0;

		player->endBuff();
		cout << "버프가 종료되었습니다!" << useCount << endl;
	}
};