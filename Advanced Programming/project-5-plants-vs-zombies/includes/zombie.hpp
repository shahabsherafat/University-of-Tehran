#pragma once

#include "consts.hpp"

class Zombie
{
protected:
    int health;
    float speed;
    float mainSpeed;
    int lineNumber;
    int hitRate;
    int eatDamage;
    bool isFrozen;
    bool isEating;
    Texture texture;
    string id;
    Sprite sprite;
    IntRect rect;
    Vector2f pos;
    Clock clock;
    Clock frozenClock, hitClock;

public:
    Zombie(Vector2f init_pos, string init_id, int damage, int init_health, int init_hitRate, float init_speed, int numofLine);
    ~Zombie();
    void update();
    bool is_dead();
    void render(RenderWindow &window);
    FloatRect get_rect();
    int get_line_number();
    void reduce_health(int damage);
    bool is_gone_in_the_house();
    int get_x();
    int get_speed();

    void reduce_speed(int slowingAmount);
    void recovery_speed();
    int get_eatDamage();
    void stand();
    void start_moving();
    int get_hitRate();
    void restart_zombie_clock();
    bool should_eat();
};

class OrdZombie : public Zombie
{
private:
public:
    OrdZombie(Vector2f init_pos, string init_id, int damage, int init_health, int init_hitRate, float init_speed, int numofLine);
    ~OrdZombie(){};
};

class HugeZombie : public Zombie
{
private:
public:
    HugeZombie(Vector2f init_pos, string init_id, int damage, int init_health, int init_hitRate, float init_speed, int numofLine);
    ~HugeZombie(){};
};
