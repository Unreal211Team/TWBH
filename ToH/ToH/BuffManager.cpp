#include "BuffManager.h"
#include "Character.h"

BuffManager* BuffManager::instance = nullptr;

BuffManager* BuffManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new BuffManager();
    }

    return instance;
}

// 버프 추가
void BuffManager::addBuff(const string& name, int turns) {
    // 이미 존재하는 버프가 있는지 확인 (name을 기준으로)
    for (auto& buff : buffs) {
        if (buff->name == name) {           // 이름이 같은 버프가 있으면
            buff->remainingTurns = turns;   // 기존 버프의 지속시간 초기화
            return;                         // 중복이라 추가할 필요없음
        }
    }
    //버프 만들어서 넣어주기
    Buff* newBuff = new Buff(name, turns);
    // 중복된 버프가 없으면 새로운 버프 추가
    buffs.push_back(newBuff);
}

bool BuffManager::dupliBuffCheck(string& name) const
{
    for (const auto& buff : buffs) {
        if (buff->name == name) {
            return true; // 이름이 같은 버프가 있으면 true 반환
        }
    }
    return false; // 버프가 없으면 false 반환
}

// 턴 업데이트
void BuffManager::updateBuffs(Character* player) {
    for (auto& buff : buffs) {
        --buff->remainingTurns;
    }

    // 남은 턴이 0 이하인 버프 삭제 및 메모리 해제
    auto it = remove_if(buffs.begin(), buffs.end(),
        [player](const Buff* buff) {
            if (buff->remainingTurns <= 0) {
                if (buff->name == "AttackBoost")
                {
                    player->resetAttackBuff();
                }//다른버프 추가시 else if로 추가
                delete buff; // 메모리 해제
                return true; // 벡터에서 제거
            }
            return false;
        });
    buffs.erase(it, buffs.end());
}

//버프목록 리턴
vector<Buff*> BuffManager::getBuffList()
{
    return buffs;
}

//활성 버프 유무 확인
bool BuffManager::ActiveBuffsCheck() const
{
    return !buffs.empty();  // buffs 벡터가 비어 있지 않으면 true 반환
}
