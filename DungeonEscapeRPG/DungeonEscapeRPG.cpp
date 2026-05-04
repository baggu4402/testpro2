#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int SIZE = 4;

class Player
{
protected:
    string name;
    string job;
    int level;
    int hp;
    int mp;
    int power;
    int defence;

public:
    Player(string name, int hp, int mp, int power, int defence)
    {
        this->name = name;
        this->job = "None";
        this->level = 1;
        this->hp = hp;
        this->mp = mp;
        this->power = power;
        this->defence = defence;
    }

    virtual ~Player()
    {
    }

    virtual void attack() = 0;

    string getName() 
    {
        return name;
    }

    string getJob()
    {
        return job;
    }

    int getLevel()
    {
        return level;
    }

    int getHP()
    {
        return hp;
    }

    int getMP()
    {
        return mp;
    }

    int getPower()
    {
        return power;
    }

    int getDefence()
    {
        return defence;
    }

    void setHP(int hp)
    {
        this->hp = hp;
    }

    void setMP(int mp)
    {
        this->mp = mp;
    }

    void printPlayerStatus()
    {
        cout << "------------------------------------" << endl;
        cout << "닉네임: " << name << " | 직업: " << job << " | Lv." << level << endl;
        cout << "HP: " << hp << " | MP: " << mp << " | 공격력: " << power << " | 방어력: " << defence << endl;
        cout << "------------------------------------" << endl;
    }
};

class Warrior : public Player
{
public:
    Warrior(string name, int hp, int mp, int power, int defence)
        : Player(name, hp, mp, power, defence)
    {
        job = "전사";
        this->hp += 30;
    }

    void attack() override
    {
        cout << "* 검을 휘둘렀다!" << endl;
    }
};

class Magician : public Player
{
public:
    Magician(string name, int hp, int mp, int power, int defence)
        : Player(name, hp, mp, power, defence)
    {
        job = "마법사";
        this->mp += 30;
    }

    void attack() override
    {
        cout << "* 파이어볼을 발사한다!" << endl;
    }
};

class Thief : public Player
{
public:
    Thief(string name, int hp, int mp, int power, int defence)
        : Player(name, hp, mp, power, defence)
    {
        job = "도적";
        this->power += 30;
    }

    void attack() override
    {
        cout << "* 빠르게 단검을 찔렀다!" << endl;
    }
};

class Archer : public Player
{
public:
    Archer(string name, int hp, int mp, int power, int defence)
        : Player(name, hp, mp, power, defence)
    {
        job = "궁수";
        this->defence += 30;
    }

    void attack() override
    {
        cout << "* 화살을 발사했다!" << endl;
    }
};

class Monster
{
private:
    string name;
    int hp;
    int power;
    int defence;
    string dropItemName;
    int dropItemPrice;

public:
    Monster(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice)
    {
        this->name = name;
        this->hp = hp;
        this->power = power;
        this->defence = defence;
        this->dropItemName = dropItemName;
        this->dropItemPrice = dropItemPrice;
    }

    string getName()
    {
        return name;
    }

    int getHP()
    {
        return hp;
    }

    int getPower()
    {
        return power;
    }

    int getDefence()
    {
        return defence;
    }

    string getDropItemName()
    {
        return dropItemName;
    }

    int getDropItemPrice()
    {
        return dropItemPrice;
    }

    void setHP(int hp)
    {
        this->hp = hp;
    }

    void attack(Player* player)
    {
        cout << name << "의 공격!" << endl;
        int damage = power - player->getDefence();

        if (damage <= 0)
        {
            damage = 1;
        }

        int newHP = player->getHP() - damage;

        cout << player->getName() << "에게" << damage << " 데미지!" << endl;
        cout << player->getName() << "HP:" << player->getHP() << " -> " << newHP;

        if (newHP <= 0)
        {
            cout << " (사망)";
        }

        cout << endl;

        player->setHP(newHP);
    }
};

struct Item
{
    string name;
    int price;

    void PrintInfo() const
    {
        cout << name << " (" << price << "G)" << endl;
    }
};

struct PotionRecipe
{
    string potionName;
    string ingredient1;
    string ingredient2;

    void PrintRecipe() const
    {
        cout << potionName << ": " << ingredient1 << " x1, " << ingredient2 << " x1" << endl;
    }
};

void printStatus(string name, int stat[])
{
    cout << "====================================" << endl;
    cout << "     " << name << " 의 현재 능력치" << endl;
    cout << "====================================" << endl;
    cout << "HP: " << stat[0] << "     MP: " << stat[1] << endl;
    cout << "공격력: " << stat[2] << "     방어력: " << stat[3] << endl;
    cout << "====================================" << endl;
}

void ShowAllRecipes(const vector<PotionRecipe>& recipes)
{
    cout << "=== 전체 레시피 ===" << endl;

    for (const PotionRecipe& recipe : recipes)
    {
        cout << "-> ";
        recipe.PrintRecipe();
    }
}

void SearchByName(const vector<PotionRecipe>& recipes, string name)
{
    bool found = false;

    for (const PotionRecipe& recipe : recipes)
    {
        if (recipe.potionName == name)
        {
            cout << "-> ";
            recipe.PrintRecipe();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "찾을 수 없습니다!" << endl;
    }
}

void SearchByIngredient(const vector<PotionRecipe>& recipes, string ingredient)
{
    int count = 0;

    for (const PotionRecipe& recipe : recipes)
    {
        if (recipe.ingredient1 == ingredient || recipe.ingredient2 == ingredient)
        {
            cout << "-> ";
            cout << recipe.potionName << " (" << recipe.ingredient1 << " x1, " << recipe.ingredient2 << " x1)" << endl;
            count++;
        }
    }

    if (count == 0)
    {
        cout << "찾을 수 없습니다!" << endl;
    }
    else
    {
        cout << "총 " << count << "개의 레시피를 찾았습니다." << endl;
    }
}

int main()
{
    string name;
    int stat[SIZE] = { 0 };
    vector<Item> inventory;
    vector<PotionRecipe> recipes;

    recipes.push_back({ "HP포션", "허브", "맑은물" });
    recipes.push_back({ "MP포션", "마나잎", "맑은물" });
    recipes.push_back({ "스태미나포션", "허브", "베리" });

    cout << "============================================" << endl;
    cout << "        [ 던전 탈출 텍스트 RPG ]" << endl;
    cout << "============================================" << endl;

    cout << "용사의 이름을 입력해주세요: ";
    cin >> name;

    cout << endl;

    while (true)
    {
        cout << "HP와 MP를 입력해주세요: ";
        cin >> stat[0] >> stat[1];

        if (stat[0] >= 50 && stat[1] >= 50)
        {
            break;
        }

        cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요." << endl;
    }

    while (true)
    {
        cout << "공격력과 방어력을 입력해주세요: ";
        cin >> stat[2] >> stat[3];

        if (stat[2] >= 0 && stat[3] >= 0)
        {
            break;
        }

        cout << "공격력이나 방어력이 너무 작습니다. 다시 입력해주세요." << endl;
    }

    cout << endl;

    printStatus(name, stat);

    int hpPotion = 5;
    int mpPotion = 5;
    bool isGameStart = false;
    int choice;

    cout << endl;
    cout << "* HP 포션 5개, MP 포션 5개가 기본 지급되었습니다." << endl;

    while (!isGameStart)
    {
        cout << "====================================" << endl;
        cout << "< 캐릭터 강화 >" << endl;
        cout << "1. HP UP    2. MP UP    3. 공격력 2배" << endl;
        cout << "4. 방어력 2배    5. 현재 능력치    0. 게임 시작" << endl;
        cout << "====================================" << endl;
        cout << "번호를 선택해주세요: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (hpPotion > 0)
            {
                stat[0] += 20;
                hpPotion--;
                cout << "* HP가 20 증가했습니다. ";
                cout << "(HP 포션 차감: 남은 포션 " << hpPotion << "개)" << endl;
            }
            else
            {
                cout << "* HP 포션이 부족합니다." << endl;
            }
            break;

        case 2:
            if (mpPotion > 0)
            {
                stat[1] += 20;
                mpPotion--;
                cout << "* MP가 20 증가했습니다. ";
                cout << "(MP 포션 차감: 남은 포션 " << mpPotion << "개)" << endl;
            }
            else
            {
                cout << "* MP 포션이 부족합니다." << endl;
            }
            break;

        case 3:
            stat[2] *= 2;
            cout << "* 공격력이 2배 증가했습니다." << endl;
            break;

        case 4:
            stat[3] *= 2;
            cout << "* 방어력이 2배 증가했습니다." << endl;
            break;

        case 5:
            printStatus(name, stat);
            break;

        case 0:
            cout << "게임을 시작합니다!" << endl;
            isGameStart = true;
            break;

        default:
            cout << "* 잘못된 번호입니다. 다시 선택해주세요." << endl;
            break;
        }

        cout << endl;
    }

    Player* player = nullptr;
    int jobChoice;

    cout << endl;
    cout << "< 전직 시스템 >" << endl;
    cout << name << "님, 직업을 선택해주세요!" << endl;
    cout << "1. 전사    2. 마법사    3. 도적    4. 궁수" << endl;
    cout << "선택: ";
    cin >> jobChoice;

    switch (jobChoice)
    {
    case 1:
        player = new Warrior(name, stat[0], stat[1], stat[2], stat[3]);
        cout << "* 전사로 전직하였습니다. (HP +30)" << endl;
        break;

    case 2:
        player = new Magician(name, stat[0], stat[1], stat[2], stat[3]);
        cout << "* 마법사로 전직하였습니다. (MP +30)" << endl;
        break;

    case 3:
        player = new Thief(name, stat[0], stat[1], stat[2], stat[3]);
        cout << "* 도적으로 전직하였습니다. (공격력 +30)" << endl;
        break;

    case 4:
        player = new Archer(name, stat[0], stat[1], stat[2], stat[3]);
        cout << "* 궁수로 전직하였습니다. (방어력 +30)" << endl;
        break;

    default:
        player = new Warrior(name, stat[0], stat[1], stat[2], stat[3]);
        cout << "* 잘못된 선택입니다. 기본 직업인 전사로 전직합니다. (HP +30)" << endl;
        break;
    }

    int menuChoice;

    while (true)
    {
        cout << endl;
        cout << "=== 메인 메뉴 ===" << endl;
        cout << "1. 던전 입장" << endl;
        cout << "2. 인벤토리 확인" << endl;
        cout << "3. 포션 제작소" << endl;
        cout << "0. 게임 종료" << endl;
        cout << endl;
        cout << "선택: ";
        cin >> menuChoice;

        if (menuChoice == 1)
        {
            int dungeonChoice;

            cout << endl;
            cout << "=== 던전 입장 ===" << endl;
            cout << "1. 슬라임 숲" << endl;
            cout << "2. 고블린 동굴" << endl;
            cout << "선택: ";
            cin >> dungeonChoice;

            Monster monster("슬라임", 30, 20, 10, "슬라임의 끈적한 젤리", 30);

            if (dungeonChoice == 1)
            {
                monster = Monster("슬라임", 30, 20, 10, "슬라임의 끈적한 젤리", 30);
            }
            else if (dungeonChoice == 2)
            {
                monster = Monster("고블린", 50, 25, 15, "고블린의 이빨", 50);
            }
            else
            {
                cout << "잘못된 번호입니다." << endl;
                continue;
            }

            cout << endl;
            cout << "[ 전투 시작! ] " << player->getName() << "(" << player->getJob() << ") vs " << monster.getName() << endl;
            cout << endl;

            while (player->getHP() > 0 && monster.getHP() > 0)
            {
                cout << "--- 플레이어 턴 ---" << endl;
                player->attack();

                int damage = player->getPower() - monster.getDefence();

                if (damage <= 0)
                {
                    damage = 1;
                }

                int newMonsterHP = monster.getHP() - damage;

                cout << monster.getName() << "에게 " << damage << " 데미지!" << endl;
                cout << monster.getName() << " HP: " << monster.getHP() << " -> " << newMonsterHP;

                if (newMonsterHP <= 0)
                {
                    cout << " (사망)";
                }

                cout << endl;

                monster.setHP(newMonsterHP);
                cout << endl;

                if (monster.getHP() <= 0)
                {
                    break;
                }

                cout << "--- 몬스터 턴 ---" << endl;
                monster.attack(player);
                cout << endl;
            }

            if (player->getHP() > 0)
            {
                Item droppedItem;
                droppedItem.name = monster.getDropItemName();
                droppedItem.price = monster.getDropItemPrice();

                inventory.push_back(droppedItem);

                cout << "★ 전투 승리!" << endl;
                cout << "-> " << droppedItem.name << " 획득!" << endl;
                cout << "-> 인벤토리에 저장되었습니다." << endl;
            }
            else
            {
                cout << "패배했습니다..." << endl;
                cout << "게임을 종료합니다." << endl;
                delete player;
                return 0;
            }
        }
        else if (menuChoice == 2)
        {
            cout << "[ 인벤토리 (" << inventory.size() << "/10) ]" << endl;

            if (inventory.empty())
            {
                cout << "인벤토리가 비어 있습니다." << endl;
            }
            else
            {
                int index = 1;
                for (const Item& item : inventory)
                {
                    cout << index << ". ";
                    item.PrintInfo();
                    index++;
                }
            }
        }
        else if (menuChoice == 3)
        {
            int potionChoice;
            string searchName;
            string searchIngredient;

            while (true)
            {
                cout << endl;
                cout << "=== 포션 제작소 ===" << endl;
                cout << "1. 전체 레시피 보기" << endl;
                cout << "2. 포션 이름으로 검색" << endl;
                cout << "3. 재료로 검색" << endl;
                cout << "0. 돌아가기" << endl;
                cout << endl;
                cout << "선택: ";
                cin >> potionChoice;

                if (potionChoice == 1)
                {
                    ShowAllRecipes(recipes);
                }
                else if (potionChoice == 2)
                {
                    cout << "검색할 포션 이름: ";
                    cin >> searchName;
                    SearchByName(recipes, searchName);
                }
                else if (potionChoice == 3)
                {
                    cout << "검색할 재료: ";
                    cin >> searchIngredient;
                    SearchByIngredient(recipes, searchIngredient);
                }
                else if (potionChoice == 0)
                {
                    break;
                }
                else
                {
                    cout << "잘못된 번호입니다." << endl;
                }
            }
        }
        else if (menuChoice == 0)
        {
            cout << "게임을 종료합니다." << endl;
            break;
        }
        else
        {
            cout << "잘못된 번호입니다." << endl;
        }
    }

    delete player;
    return 0;
}