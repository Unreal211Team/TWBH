#include "BuffUi.h"
#include "BuffManager.h"
#include <iostream>

void BuffUi::printMessege()
{
	BuffManager* manager = BuffManager::getInstance();
	
	// ������ ������
	if (manager->ActiveBuffsCheck())
	{
		//���� ����� �����ͼ�
		vector<Buff*> buffs = manager->getBuffList();

		cout << "Active Buffs:\n";
		for (const auto& buff : buffs) {
			cout << "- " << buff->name << " (" << buff->remainingTurns << " �� ���ҽ��ϴ�.): "
				<< "\n";
		}
		cout << " --- ----- ---\n\n";
	}
}
