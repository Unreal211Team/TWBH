#include <string>
#include <vector>
#include <algorithm>
#include "Character.h"

using namespace std;

// 버프 구조체 정의
struct Buff {
    string name;
    int remainingTurns;

    Buff(const string& name, int turns)
        : name(name), remainingTurns(turns) {
    }
};

// 버프 관리 클래스
class BuffManager {
private:
    static BuffManager* instance;

    vector<Buff*> buffs; // Buff 포인터를 저장하는 벡터
    //생성자 소멸자
    BuffManager() = default;
    ~BuffManager() = default;

    // 복사 생성자와 복사 대입 연산자 삭제
    BuffManager(const BuffManager&) = delete;
    BuffManager& operator=(const BuffManager&) = delete;

public:
    // BuffManager의 인스턴스를 가져오는 함수
    static BuffManager* getInstance();
    // 버프 추가
    void addBuff(const std::string& name, int turns);

    //버프 중복체크
    bool dupliBuffCheck(string& name) const;

    // 턴 업데이트
    void updateBuffs(Character* player);

    //버프 목록 Get
    vector<Buff*> getBuffList();

    // 활성 버프 유무 출력
    bool ActiveBuffsCheck() const;

};