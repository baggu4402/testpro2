#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Item
{
    string name;
    int price;

    void PrintInfo() const
    {
        cout << name << " (" << price << "G)" << endl;
    }
};

template<typename T>
class Inventory
{
private:
    T* pItems;
    int capacity_;
    int size_;

public:
    Inventory(int capacity = 10)
    {
        capacity_ = capacity;
        size_ = 0;
        pItems = new T[capacity_];
    }

    ~Inventory()
    {
        delete[] pItems;
    }

    Inventory(const Inventory& other)
    {
        capacity_ = other.capacity_;
        size_ = other.size_;
        pItems = new T[capacity_];

        for (int i = 0; i < size_; i++)
        {
            pItems[i] = other.pItems[i];
        }
    }

    void AddItem(const T& item)
    {
        if (size_ >= capacity_)
        {
            cout << "-> 인벤토리 자동 확장! (" << capacity_ << " -> " << capacity_ * 2 << ")" << endl;
            Resize(capacity_ * 2);
        }

        pItems[size_] = item;
        size_++;

        cout << "-> 아이템 추가 완료" << endl;
    }

    void RemoveLastItem()
    {
        if (size_ <= 0)
        {
            cout << "삭제할 아이템이 없습니다." << endl;
            return;
        }

        size_--;
    }

    void RemoveAt(int index)
    {
        if (index < 0 || index >= size_)
        {
            cout << "잘못된 인덱스입니다." << endl;
            return;
        }

        for (int i = index; i < size_ - 1; i++)
        {
            pItems[i] = pItems[i + 1];
        }

        size_--;
    }

    void PrintAllItems() const
    {
        if (size_ == 0)
        {
            cout << "인벤토리가 비어 있습니다." << endl;
            return;
        }

        for (int i = 0; i < size_; i++)
        {
            cout << i + 1 << ". ";
            pItems[i].PrintInfo();
        }
    }

    void Resize(int newCapacity)
    {
        T* newItems = new T[newCapacity];

        for (int i = 0; i < size_; i++)
        {
            newItems[i] = pItems[i];
        }

        delete[] pItems;
        pItems = newItems;
        capacity_ = newCapacity;
    }

    int GetSize() const
    {
        return size_;
    }

    int GetCapacity() const
    {
        return capacity_;
    }

    T GetItem(int index) const
    {
        return pItems[index];
    }

    void SortItems()
    {
        sort(pItems, pItems + size_, [](const T& a, const T& b)
            {
                return a.price < b.price;
            });
    }

};

bool compareByPrice(const Item& a, const Item& b)
{
    return a.price < b.price;
}

const int SIZE = 4;

class Monster;

class Player
{
protected:
    string name;
    string job;
    int level;
    int exp;
    int maxExp;
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
        this->exp = 0;
        this->maxExp = 100;
        this->hp = hp;
        this->mp = mp;
        this->power = power;
        this->defence = defence;
    }

    virtual ~Player()
    {
    }

    virtual void attack(Monster* monster) = 0;

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
    int getExp()
    {
        return exp;
    }

    int getMaxExp()
    {
        return maxExp;
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

    void setLevel(int level)
    {
        this->level = level;
    }

    void setExp(int exp)
    {
        this->exp = exp;
    }

    void setMaxExp(int maxExp)
    {
        this->maxExp = maxExp;
    }

    void setPower(int power)
    {
        this->power = power;
    }

    void printPlayerStatus()
    {
        cout << "------------------------------------" << endl;
        cout << "닉네임: " << name << " | 직업: " << job << " | Lv." << level << endl;
        cout << "EXP: " << exp << " / " << maxExp << endl;
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

    void attack(Monster* monster) override;
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

    void attack(Monster* monster) override;
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

    void attack(Monster* monster) override;
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

    void attack(Monster* monster) override;
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
    int expReward;

public:
    Monster(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward)
    {
        this->name = name;
        this->hp = hp;
        this->power = power;
        this->defence = defence;
        this->dropItemName = dropItemName;
        this->dropItemPrice = dropItemPrice;
        this->expReward = expReward;
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

    int getExpReward()
    {
        return expReward;
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

void Warrior::attack(Monster* monster)
{
    int damage = power - monster->getDefence();

    if (damage <= 0)
    {
        damage = 1;
    }

    int newMonsterHP = monster->getHP() - damage;

    cout << "[전사] 장검을 휘두른다! -> "
        << monster->getName() << "에게 " << damage << " 데미지!" << endl;

    monster->setHP(newMonsterHP);
}

void Magician::attack(Monster* monster)
{
    int damage = power - monster->getDefence();

    if (damage <= 0)
    {
        damage = 1;
    }

    int newMonsterHP = monster->getHP() - damage;

    cout << "[마법사] 파이어볼 발사! -> "
        << monster->getName() << "에게 " << damage << " 데미지!" << endl;

    monster->setHP(newMonsterHP);
}

void Archer::attack(Monster* monster)
{
    int damage = (power - monster->getDefence()) / 3;

    if (damage <= 0)
    {
        damage = 1;
    }

    int totalDamage = damage * 3;
    int newMonsterHP = monster->getHP() - totalDamage;

    cout << "[궁수] 화살을 쏜다! -> "
        << monster->getName() << "에게 " << damage
        << " 데미지! (x3)" << endl;

    monster->setHP(newMonsterHP);
}

void Thief::attack(Monster* monster)
{
    int damage = (power - monster->getDefence()) / 5;

    if (damage <= 0)
    {
        damage = 1;
    }

    int totalDamage = damage * 5;
    int newMonsterHP = monster->getHP() - totalDamage;

    cout << "[도적] 단검을 찌른다! -> "
        << monster->getName() << "에게 " << damage
        << " 데미지! (x5)" << endl;

    monster->setHP(newMonsterHP);
}


void setPotion(int count, int* p_HPPotion, int* p_MPPotion)
{
    *p_HPPotion = count;
    *p_MPPotion = count;
}

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

struct DungeonRoom
{
    string monsterName;
    int hp;
    int power;
    int defence;
    string dropItemName;
    int dropItemPrice;
    int expReward;
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

int GetStock(map<string, int>& potionStock, string name)
{
    return potionStock[name];
}

void DispensePotion(map<string, int>& potionStock, string name)
{
    if (potionStock[name] > 0)
    {
        potionStock[name]--;
        cout << "-> " << name << " 지급 (재고: " << potionStock[name] << ")" << endl;
    }
    else
    {
        cout << "-> " << name << " 지급 실패! 재고 없음!" << endl;
    }
}

void ReturnPotion(map<string, int>& potionStock, string name)
{
    const int MAX_STOCK = 3;

    if (potionStock[name] < MAX_STOCK)
    {
        potionStock[name]++;
        cout << "-> 공병 반환 (" << name << " 재고: " << potionStock[name] << ")" << endl;
    }
    else
    {
        cout << "-> " << name << " 재고는 이미 최대치입니다." << endl;
    }
}

int main()
{
    string name;
    int stat[SIZE] = { 0 };
    Inventory<Item> inventory(10);
    vector<PotionRecipe> recipes;
    map<string, int> potionStock;

    recipes.push_back({ "HP포션", "허브", "맑은물" });
    recipes.push_back({ "MP포션", "마나잎", "맑은물" });
    recipes.push_back({ "스태미나포션", "허브", "베리" });

    potionStock["HP 포션"] = 3;
    potionStock["MP 포션"] = 3;
    potionStock["스태미나 포션"] = 3;

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

    setPotion(5, &hpPotion, &mpPotion);
    cout << "HP포션 재고: " << GetStock(potionStock, "HP 포션") << endl;
    cout << "MP포션 재고: " << GetStock(potionStock, "MP 포션") << endl;

    for (int i = 0; i < 3; i++)
    {
        DispensePotion(potionStock, "HP 포션");
        inventory.AddItem({ "HP 포션", 50 });
    }

    for (int i = 0; i < 3; i++)
    {
        DispensePotion(potionStock, "MP 포션");
        inventory.AddItem({ "MP 포션", 50 });
    }

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


    vector<DungeonRoom> dungeonFloor1;

    dungeonFloor1.push_back({ "슬라임", 30, 15, 5, "슬라임 젤리", 30, 30 });
    dungeonFloor1.push_back({ "고블린", 50, 25, 10, "고블린의 이빨", 50, 50 });
    dungeonFloor1.push_back({ "오크", 80, 35, 15, "오크의 도끼 조각", 80, 80 });
    DungeonRoom bossRoom = { "드래곤", 200, 60, 20, "드래곤의 비늘", 200, 150 };


    int menuChoice;

    while (true)
    {
        cout << endl;
        cout << "1. 던전 입장" << endl;
        cout << "2. 인벤토리 확인" << endl;
        cout << "3. 포션 제작소" << endl;
        cout << "4. 플레이어 상태 확인" << endl;
        cout << "6. 포션 재고 확인" << endl;
        cout << "0. 게임 종료" << endl;
        cout << endl;
        cout << "선택: ";
        cin >> menuChoice;

        if (menuChoice == 1)
        {
            cout << endl;
            cout << "[ 던전 1층 ]" << endl;

            bool playerDead = false;

            for (int i = 0; i < dungeonFloor1.size(); i++)
            {
                DungeonRoom room = dungeonFloor1[i];

                cout << i + 1 << "번 방: " << room.monsterName
                    << " (HP " << room.hp
                    << ", 공격력 " << room.power
                    << ", 방어력 " << room.defence << ")" << endl;

                Monster monster(
                    room.monsterName,
                    room.hp,
                    room.power,
                    room.defence,
                    room.dropItemName,
                    room.dropItemPrice,
                    room.expReward
                );

                cout << endl;
                cout << "[ 전투 시작! ] "
                    << player->getName() << "(" << player->getJob() << ") vs "
                    << monster.getName() << endl << endl;

                while (player->getHP() > 0 && monster.getHP() > 0)
                {
                    int battleChoice;

                    cout << "--- 플레이어 턴 ---" << endl;
                    cout << "1. 공격" << endl;
                    cout << "2. 아이템 사용" << endl;
                    cout << "선택: ";
                    cin >> battleChoice;

                    if (battleChoice == 1)
                    {
                        int beforeHP = monster.getHP();

                        player->attack(&monster);

                        int afterHP = monster.getHP();

                        if (afterHP < 0)
                        {
                            afterHP = 0;
                            monster.setHP(0);
                        }

                        cout << monster.getName() << " HP: " << beforeHP << " -> " << afterHP;

                        if (afterHP <= 0)
                        {
                            cout << " (사망)";
                        }

                        cout << endl << endl;
                    }
                    else if (battleChoice == 2)
                    {
                        if (inventory.GetSize() == 0)
                        {
                            cout << "인벤토리가 비어 있습니다." << endl << endl;
                            continue;
                        }

                        cout << "[ 인벤토리 ]" << endl;
                        inventory.PrintAllItems();

                        int itemChoice;
                        cout << "사용할 아이템 번호: ";
                        cin >> itemChoice;

                        if (itemChoice < 1 || itemChoice > inventory.GetSize())
                        {
                            cout << "잘못된 번호입니다." << endl << endl;
                            continue;
                        }

                        Item selectedItem = inventory.GetItem(itemChoice - 1);

                        if (selectedItem.name == "HP 포션")
                        {
                            int oldHP = player->getHP();
                            int newHP = min(player->getHP() + 50, 100);
                            player->setHP(newHP);

                            cout << "* HP 포션 사용! HP 50 회복 ("
                                << oldHP << " -> " << newHP << ")" << endl;

                            inventory.RemoveAt(itemChoice - 1);
                            ReturnPotion(potionStock, "HP 포션");
                        }
                        else if (selectedItem.name == "MP 포션")
                        {
                            int oldMP = player->getMP();
                            int newMP = min(player->getMP() + 50, 100);
                            player->setMP(newMP);

                            cout << "* MP 포션 사용! MP 50 회복 ("
                                << oldMP << " -> " << newMP << ")" << endl;

                            inventory.RemoveAt(itemChoice - 1);
                            ReturnPotion(potionStock, "MP 포션");
                        }
                        else
                        {
                            cout << "전투 중 사용할 수 없는 아이템입니다." << endl << endl;
                            continue;
                        }

                        cout << endl;
                    }
                    else
                    {
                        cout << "잘못된 번호입니다." << endl << endl;
                        continue;
                    }

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
                    droppedItem.name = room.dropItemName;
                    droppedItem.price = room.dropItemPrice;

                    inventory.AddItem(droppedItem);

                    cout << "-> 클리어!" << endl;
                    cout << "★ 전투 승리!" << endl;

                    int newExp = player->getExp() + room.expReward;
                    player->setExp(newExp);

                    cout << "-> 경험치 +" << room.expReward << " 획득! (현재 경험치: "
                        << player->getExp() << "/" << player->getMaxExp() << ")" << endl;

                    if (player->getExp() >= player->getMaxExp())
                    {
                        cout << "... 레벨업 조건 충족" << endl;

                        int oldLevel = player->getLevel();
                        player->setLevel(player->getLevel() + 1);
                        player->setHP(player->getHP() + 10);
                        player->setMP(player->getMP() + 5);
                        player->setPower(player->getPower() + 5);

                        player->setExp(0);
                        player->setMaxExp(player->getMaxExp() + 50);

                        cout << "-> 레벨 업! Lv." << oldLevel
                            << " -> Lv." << player->getLevel() << endl;
                        cout << "-> HP +10, MP +5, 공격력 +5 증가!" << endl;
                    }

                    cout << "-> " << droppedItem.name << " 획득!" << endl;
                    cout << "-> 인벤토리에 저장되었습니다." << endl;
                    cout << endl;
                }
                else
                {
                    cout << "=== 게임 오버! ===" << endl;
                    delete player;
                    return 0;
                }
            }

            cout << "★ 보스방 개방!" << endl;
            cout << "보스 드래곤 등장! (HP 200, 공격력 60, 방어력 20)" << endl << endl;

            Monster boss(
                bossRoom.monsterName,
                bossRoom.hp,
                bossRoom.power,
                bossRoom.defence,
                bossRoom.dropItemName,
                bossRoom.dropItemPrice,
                bossRoom.expReward
            );

            while (player->getHP() > 0 && boss.getHP() > 0)
            {
                int battleChoice;

                cout << "--- 플레이어 턴 ---" << endl;
                cout << "1. 공격" << endl;
                cout << "2. 아이템 사용" << endl;
                cout << "선택: ";
                cin >> battleChoice;

                if (battleChoice == 1)
                {
                    int beforeHP = boss.getHP();

                    player->attack(&boss);

                    int afterHP = boss.getHP();

                    if (afterHP < 0)
                    {
                        afterHP = 0;
                        boss.setHP(0);
                    }

                    cout << boss.getName() << " HP: " << beforeHP << " -> " << afterHP;

                    if (afterHP <= 0)
                    {
                        cout << " (사망)";
                    }

                    cout << endl << endl;
                }
                else if (battleChoice == 2)
                {
                    if (inventory.GetSize() == 0)
                    {
                        cout << "인벤토리가 비어 있습니다." << endl << endl;
                        continue;
                    }

                    cout << "[ 인벤토리 ]" << endl;
                    inventory.PrintAllItems();

                    int itemChoice;
                    cout << "사용할 아이템 번호: ";
                    cin >> itemChoice;

                    if (itemChoice < 1 || itemChoice > inventory.GetSize())
                    {
                        cout << "잘못된 번호입니다." << endl << endl;
                        continue;
                    }

                    Item selectedItem = inventory.GetItem(itemChoice - 1);

                    if (selectedItem.name == "HP 포션")
                    {
                        int oldHP = player->getHP();
                        int newHP = min(player->getHP() + 50, 100);
                        player->setHP(newHP);

                        cout << "* HP 포션 사용! HP 50 회복 ("
                            << oldHP << " -> " << newHP << ")" << endl;

                        inventory.RemoveAt(itemChoice - 1);
                        ReturnPotion(potionStock, "HP 포션");
                    }
                    else if (selectedItem.name == "MP 포션")
                    {
                        int oldMP = player->getMP();
                        int newMP = min(player->getMP() + 50, 100);
                        player->setMP(newMP);

                        cout << "* MP 포션 사용! MP 50 회복 ("
                            << oldMP << " -> " << newMP << ")" << endl;

                        inventory.RemoveAt(itemChoice - 1);
                        ReturnPotion(potionStock, "MP 포션");
                    }
                    else
                    {
                        cout << "전투 중 사용할 수 없는 아이템입니다." << endl << endl;
                        continue;
                    }

                    cout << endl;
                }
                else
                {
                    cout << "잘못된 번호입니다." << endl << endl;
                    continue;
                }

                if (boss.getHP() <= 0)
                {
                    break;
                }

                cout << "--- 보스 턴 ---" << endl;
                boss.attack(player);
                cout << endl;
            }

            if (player->getHP() > 0)
            {
                cout << "드래곤을 처치했습니다!" << endl;
                cout << "=== 게임 클리어! ===" << endl;
                delete player;
                return 0;
            }
            else
            {
                cout << "=== 게임 오버! ===" << endl;
                delete player;
                return 0;
            }
        }
        else if (menuChoice == 2)
        {
            cout << "[ 인벤토리 (" << inventory.GetSize() << "/" << inventory.GetCapacity() << ") ]" << endl;
            inventory.PrintAllItems();
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

        else if (menuChoice == 4)
        {
            player->printPlayerStatus();
        }

        else if (menuChoice == 6)
        {
            cout << "[ 포션 재고 ]" << endl;
            cout << "HP 포션: " << GetStock(potionStock, "HP 포션") << endl;
            cout << "MP 포션: " << GetStock(potionStock, "MP 포션") << endl;
            cout << "스태미나 포션: " << GetStock(potionStock, "스태미나 포션") << endl;
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