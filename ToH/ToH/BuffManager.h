#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Character.h"

using namespace std;

// ���� ����ü ����
struct Buff {
    string name;
    int remainingTurns;

    Buff(const string& name, int turns)
        : name(name), remainingTurns(turns) {
    }
};

// ���� ���� Ŭ����
class BuffManager {
private:
    static BuffManager* instance;

    vector<Buff*> buffs; // Buff �����͸� �����ϴ� ����
    //������ �Ҹ���
    BuffManager() = default;
    ~BuffManager() = default;

    // ���� �����ڿ� ���� ���� ������ ����
    BuffManager(const BuffManager&) = delete;
    BuffManager& operator=(const BuffManager&) = delete;

public:
    // BuffManager�� �ν��Ͻ��� �������� �Լ�
    static BuffManager* getInstance();
    // ���� �߰�
    void addBuff(const std::string& name, int turns);

    //���� �ߺ�üũ
    bool dupliBuffCheck(string& name) const;

    // �� ������Ʈ
    void updateBuffs(Character* player);

    // Ȱ�� ���� ���
    void displayBuffs() const;

    // Ȱ�� ���� ���� ���
    bool ActiveBuffsCheck() const;

};

