#pragma once

#include "consts.hpp"

class Plant{
protected:
    string id;
    int lineNumber;
    int health;
    Texture texture;
    Sprite sprite;
    Vector2f pos;

public:
    Plant(Vector2f init_pos, int health, int numOfLine);
    ~Plant();
    Vector2f get_pos();
    string get_id();
    virtual void update();
    void render(RenderWindow& window);
    int get_line_number();

    FloatRect get_rect();
    int get_health();
    void reduce_health(int eatDamage);
    bool is_dead();
};

class SunFlower : public Plant{
    private:
        Clock produceClock;
        int produceRate = 8;
    public:
        SunFlower(Vector2f init_pos, int init_health, int numOfLine);
        ~SunFlower();
        void update();
        bool should_produce_sun();
};

class PeaShooter : public Plant{
    private:
        Clock shootClock;
        int hitRate;
        int damage;
    public:
        PeaShooter(Vector2f init_pos, int init_health, int init_hitRate, int numOfLine);
        ~PeaShooter();
        void update();
        bool should_shoot();
};
class IcePeaShooter : public Plant{
    private:
        Clock shootClock;
        int hitRate;
        int damage;
    public:
        IcePeaShooter(Vector2f init_pos, int init_health, int init_hitRate, int numOfLine);
        ~IcePeaShooter();
        void update();
        bool should_shoot();
};

class Walnut : public Plant{
    private:
        
    public:
        Walnut(Vector2f init_pos, int init_health, int numOfLine);
        ~Walnut();
        void update();
};

class MelonPult : public Plant{
    private:
        Clock shootClock;
        int hitRate;
        int damage;
    public:
        MelonPult(Vector2f init_pos, int init_health, int init_hitRate, int numOfLine);
        ~MelonPult();
        void update();
        bool should_shoot();
};