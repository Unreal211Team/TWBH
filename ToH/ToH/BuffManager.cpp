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

// ���� �߰�
void BuffManager::addBuff(const string& name, int turns) {
    // �̹� �����ϴ� ������ �ִ��� Ȯ�� (name�� ��������)
    for (auto& buff : buffs) {
        if (buff->name == name) {           // �̸��� ���� ������ ������
            buff->remainingTurns = turns;   // ���� ������ ���ӽð� �ʱ�ȭ
            return;                         // �ߺ��̶� �߰��� �ʿ����
        }
    }
    //���� ���� �־��ֱ�
    Buff* newBuff = new Buff(name, turns);
    // �ߺ��� ������ ������ ���ο� ���� �߰�
    buffs.push_back(newBuff);
}

bool BuffManager::dupliBuffCheck(string& name) const
{
    for (const auto& buff : buffs) {
        if (buff->name == name) {
            return true; // �̸��� ���� ������ ������ true ��ȯ
        }
    }
    return false; // ������ ������ false ��ȯ
}

// �� ������Ʈ
void BuffManager::updateBuffs(Character* player) {
    for (auto& buff : buffs) {
        --buff->remainingTurns;
    }

    // ���� ���� 0 ������ ���� ���� �� �޸� ����
    auto it = remove_if(buffs.begin(), buffs.end(),
        [player](const Buff* buff) {
            if (buff->remainingTurns <= 0) {
                switch (buff->name == "AttackBoost")
                {
                    player->resetAttackBuff();
                default:
                    break;
                }
                delete buff; // �޸� ����
                return true; // ���Ϳ��� ����
            }
            return false;
        });
    buffs.erase(it, buffs.end());
}

//������� ����
vector<Buff*> BuffManager::getBuffList()
{
    return buffs;
}

//Ȱ�� ���� ���� Ȯ��
bool BuffManager::ActiveBuffsCheck() const
{
    return !buffs.empty();  // buffs ���Ͱ� ��� ���� ������ true ��ȯ
}
