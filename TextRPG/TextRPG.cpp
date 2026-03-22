#include <iostream>
using namespace std;
enum PlayerType {PT_None =0, PT_Knight =1, PT_Archer =2, PT_Mage =3};
PlayerType playerType;
struct StateInfo
{
    int hp, attack, defence;
};
StateInfo playerState;
StateInfo monsterState;

enum MonsterType {MT_Slime = 1, MT_Oak = 2, MT_Skeleton = 3 };

void EnterLobby();
void SelectPlayer();
void EnterField();
void CreateRandomMonster();
void EnterBattle();

int main()
{
    while (true) {
        EnterLobby();
    }
}

void EnterLobby()
{
    cout << "---------------------------" << endl;
    cout << "---환영합니다.-로비 입장---" << endl;
    cout << "---------------------------" << endl;
    SelectPlayer();
    cout << "---------------------------" << endl;
    cout << "-(1)필드 입장 (2)게임 종료-" << endl;
    cout << "---------------------------" << endl;
    cout << ">";
    int input;
    cin >> input;
    if (input == 1) {
        EnterField();
    }
    else
    {
        return;
    }
}

void SelectPlayer()
{
    cout << "---캐릭터 선택 해주세요.---" << endl;
    cout << "--(1)기사 (2)공수 (3)법사--" << endl;
    cout << "---------------------------" << endl;
    cout << ">";
    int choice;
    cin >> choice;
    switch ((PlayerType)choice)
    {
    case PT_Knight:
        cout << "기사 생성중..." << endl;
        playerState.hp = 120; playerState.attack = 10; playerState.defence = 10;
        cout << "hp:120, attack:10, defence:10" << endl;
        break;
    case PT_Archer:
        cout << "금수 생성중..." << endl;
        playerState.hp = 80; playerState.attack = 11; playerState.defence = 5;
        cout << "hp:80, attack:11, defence:5" << endl;
        break;
    case PT_Mage:
        cout << "법사 생성중..." << endl;
        playerState.hp = 60; playerState.attack = 15; playerState.defence = 3;
        cout << "hp:60, attack:15, defence:3" << endl;
        break;

    }
}

void EnterField()
{
    while(true)
    {
        cout << "---------------------------" << endl;
        cout << "|   필드에 입장했습니다.  |" << endl;
        cout << "---------------------------" << endl;

        cout << "[PLAYER] Hp: " << playerState.hp  << " ";
        cout << "[PLAYER] Att: " << playerState.attack << " ";
        cout << "[PLAYER] Def: " << playerState.defence << endl;

        CreateRandomMonster();

        cout << "---------------------------" << endl;
        cout << "------(1)전투 (2)도주------" << endl;
        cout << "---------------------------" << endl;
        cout << ">";
        int input;
        cin >> input;
        if (input == 1) {
            EnterBattle();
            if (playerState.hp <= 0)return;
        }
        else
        {
            return;
        }
    }
}

void CreateRandomMonster()
{
    srand(time(0));
    int randMonster = rand() % 3;
    switch ((MonsterType)randMonster)
    {
    case MT_Slime:
        cout << " [슬라임]:(hp:50, attack:10, defence:0)" << endl;
        monsterState.hp = 50; monsterState.attack = 10; monsterState.defence = 0;
        break;
    case MT_Oak:
        cout << "오크:(hp:80, attack:10, defence:5)" << endl;
        monsterState.hp = 80; monsterState.attack = 10; monsterState.defence = 5;
        break;
    case MT_Skeleton:
        cout << "해골:(hp:85, attack:10, defence:0)" << endl;
        monsterState.hp = 85; monsterState.attack = 10; monsterState.defence = 0;
        break;
    }
}

void EnterBattle()
{
    while (true)
    {
        //player attack
        int damage = playerState.attack - monsterState.defence;
        monsterState.hp -= damage;

        if (monsterState.hp < 0) monsterState.hp = 0;
        if (monsterState.hp == 0) {
            cout << "몬스터를 저치했습니다." << endl;
        }
        cout << "몬스터 HP:" << monsterState.hp << endl;

        //enemy attack
        damage -= monsterState.attack - playerState.defence;
        playerState.hp -= damage;
        cout << "Player HP:" << playerState.hp << endl;
        if (playerState.hp <= 0) playerState.hp = 0;
        if (playerState.hp == 0) {
            cout << "Game Over" << endl;
            return;
        }
    }
}
