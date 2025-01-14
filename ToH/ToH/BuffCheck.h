#pragma once
#include "Character.h"

class BuffCheck
{
private:
	bool useCheck;
	int useCount;

public:
	//������ �ϳ��� �⺻������ �ϳ��� �ٸ��뵵
	BuffCheck():useCheck(false), useCount(0){}
	BuffCheck(string use): useCheck(false), useCount(3) {}

	//�ߺ�üũ
	void dupliCheck() {

	}

	//���� ī����
	void buffCounting(Character* player) {
		if (useCheck)
		{
			useCount--;
			if (useCount > 0)
			{
				cout << "���� ���� �� : " << useCount << endl;
			}
			else {
				player->endBuff();
				cout << "������ ����Ǿ����ϴ�!" << useCount << endl;
			}
		}
	}

	//�� ����
	void resetBuff(Character* player) {
		useCheck = false;
		useCount = 0;

		player->endBuff();
		cout << "������ ����Ǿ����ϴ�!" << useCount << endl;
	}
};