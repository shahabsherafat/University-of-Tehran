#pragma once

#include "consts.hpp"

class Shot
{
protected:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    Vector2f pos;
    int damage;
    int speed;
    int lineNumber;

public:
    Shot(Vector2f init_pos, int init_damage, int init_speed, int numOfLine);
    ~Shot();
    FloatRect get_rect();
    virtual void update();
    void render(RenderWindow &window);
    bool is_out();
    int get_line_number();
    int get_damage();
};

class OrdShot : public Shot
{
private:
public:
    OrdShot(Vector2f init_pos, int init_damage, int init_speed, int numOfLine);
    ~OrdShot();
    void update();
};

class IceShot : public Shot
{
private:
    int slowingAmount = 1;
    
public:
    IceShot(Vector2f init_pos, int init_damage, int init_speed, int numOfLine);
    ~IceShot();
    void update();
    int get_slowing_amount();
};

class MelonShot : public Shot
{
private:
    int verticalSpeed = 0;
    int plant_x;
    int plant_y;
    int distance;
    int zombieSpeed;

public:
    MelonShot(Vector2f init_pos, int init_damage, int init_speed, int numOfLine, int init_distance, int init_zombieSpeed);
    ~MelonShot();
    void update();
};