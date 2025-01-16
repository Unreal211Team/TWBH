#include "BuffUi.h"
#include "BuffManager.h"
#include <iostream>

void BuffUi::printMessege()
{
	BuffManager* manager = BuffManager::getInstance();
	
	// 버프가 있으면
	if (manager->ActiveBuffsCheck())
	{
		//버프 목록을 가져와서
		vector<Buff*> buffs = manager->getBuffList();

		cout << "Active Buffs:\n";
		for (const auto& buff : buffs) {
			cout << "- " << buff->name << " (" << buff->remainingTurns << " 턴 남았습니다.): "
				<< "\n";
		}
		cout << " --- ----- ---\n\n";
	}
}
