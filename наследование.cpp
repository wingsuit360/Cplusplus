#include <iostream>
#include <cmath>

using namespace std;

class Unit {  //Ѕазовый класс
public:
    int damage;
    int health;
    Unit(int damage, int health) : damage(damage), health(health) {} // конструктор
    virtual int get_attack() {return damage;} // виртуальный метод атаки (выводит колько жизни отнимает)
    ~Unit() {}
};

class Soldier : public virtual Unit {  //¬оин
public:
    int extra_damage;
    Soldier(int damage, int health, int extra_damage) : Unit(damage, health), extra_damage(extra_damage) {}
    virtual int get_attack() override {return damage + extra_damage;}  // переопределенный метод атаки
    ~Soldier() {}
};

class Shooter : public virtual Unit {  //—трелок
public:
    int shot_damage;
    int shot_number;
    Shooter(int damage, int health, int shot_damage, int shot_number) : Unit(damage, health), shot_damage(shot_damage), shot_number(shot_number) {}
    virtual int get_attack() override {return damage + shot_number*shot_damage;}  // переопределенный метод атаки
    ~Shooter() {}
};

class Soldier_with_rifle final: public Soldier, public Shooter {  // ёнит с возможностью ближнего бо€ и винтовкой, нельз€ наследовать
public:
    Soldier_with_rifle(int damage, int health, int extra_damage, int shot_damage, int shot_number) : Unit(damage, health), Soldier(damage, health, extra_damage), Shooter(damage, health, shot_damage, shot_number) {}
    int get_attack() override {return Soldier::get_attack() + Shooter::get_attack();}  // переопределенный метод атаки
    ~Soldier_with_rifle() {}
};

class Building : public virtual Unit {  // «дание
public:
    int extra_health;
    Building(int damage, int health, int extra_health): Unit(damage, health), extra_health(extra_health) {}
    ~Building() {}
};

class Tower : public Building {  //Ѕашн€
public:
    int view_range;
    Tower(int damage, int health, int extra_health, int view_range) : Unit(damage, health), Building(damage, health, extra_health), view_range(view_range) {}
    ~Tower() {}
};

class Turret final : public Tower {  //“урель, нельз€ наследовать
public:
    int extra_damage;
    Turret(int damage, int health, int extra_health, int view_range, int extra_damage) : Unit(damage, health), Tower(damage, health, extra_health, view_range), extra_damage(extra_damage) {}
    int get_attack() override {return damage + extra_damage;}  // переопределенный метод атаки
    ~Turret() {}
};

class Medic /*final*/: public virtual Unit {  //ћедик (если раскомментировать final, сломаетс€)
public:
    int heal_speed;
    Medic(int damage, int health, int heal_speed) : Unit(damage, health), heal_speed(heal_speed) {}
    int get_attack() override {return -damage*heal_speed;}  // переопределенный метод атаки (уронь меньше 0 - лечение)
    ~Medic() {}
};

class Healing_Tower final: public Tower, public Medic {  //Ћечаща€ башн€, нельз€ наследовать
public:
    Healing_Tower(int damage, int health, int extra_health, int view_range, int heal_speed) : Unit(damage, health),
        Tower(damage, health, extra_health, view_range), Medic(damage, health, heal_speed) {}
    int get_attack() override {return Medic::get_attack();}  // переопределенный метод атаки (такой же, как у медика)
    ~Healing_Tower() {}
};

int main() {
    Soldier_with_rifle S(10, 50, 5, 5, 20);
    cout << "Soldier with rifle damage: " << S.get_attack() << endl;
    Healing_Tower H(30, 200, 50, 100, 5);
    cout << "Healing Tower heal rate: " << H.get_attack() << endl;
}
