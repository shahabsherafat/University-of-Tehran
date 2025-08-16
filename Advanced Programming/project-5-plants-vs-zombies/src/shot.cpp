#include "../includes/shot.hpp"

Shot::Shot(Vector2f init_pos, int init_damage, int init_speed, int numOfLine)
{
    pos = init_pos;
    damage = init_damage;
    speed = init_speed;
    lineNumber = numOfLine;
}

Shot::~Shot()
{
}

void Shot::render(RenderWindow &window)
{
    window.draw(sprite);
}

void Shot::update()
{
}

bool Shot::is_out()
{
    return sprite.getPosition().x > WIDTH + 50 or sprite.getPosition().y > HEIGHT + 50;
}

FloatRect Shot::get_rect(){
    return sprite.getGlobalBounds();
}

int Shot::get_line_number(){
    return lineNumber;
}

int Shot::get_damage(){
    return damage;
}

OrdShot::OrdShot(Vector2f init_pos, int init_damage, int init_speed, int numOfLine) :
                 Shot(init_pos, init_damage, init_speed, numOfLine)
{
    if (!texture.loadFromFile(PICS_PATH + "shots/" + "pea.png"))
    {
        debug("failed to load pea shot texture");
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(1.25, 1.25);
    sprite.setPosition(pos);
}

OrdShot::~OrdShot()
{
}

void OrdShot::update()
{
    pos.x += speed;
    sprite.setPosition(pos);
}

IceShot::IceShot(Vector2f init_pos, int init_damage, int init_speed, int numOfLine) :
                 Shot(init_pos, init_damage, init_speed, numOfLine)
{
    if (!texture.loadFromFile(PICS_PATH + "shots/" + "icepea.png"))
    {
        debug("failed to load ice pea shot texture");
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(1.2, 1.2);
    sprite.setPosition(pos);
}

IceShot::~IceShot()
{
}

void IceShot::update()
{
    pos.x += speed;
    sprite.setPosition(pos);
}

int IceShot::get_slowing_amount()
{
    return slowingAmount;
}

MelonShot::MelonShot(Vector2f init_pos, int init_damage, int init_speed, int numOfLine, int init_distance, int init_zombieSpeed) :
                     Shot(init_pos, init_damage, init_speed, numOfLine)
{
    plant_x = init_pos.x;
    plant_y = init_pos.y;
    distance = init_distance;
    zombieSpeed = init_zombieSpeed;

    if (!texture.loadFromFile(PICS_PATH + "shots/" + "melon.png"))
    {
        debug("failed to load melon shot texture");
    }
    sprite.setTexture(texture);
    sprite.setScale(1, 1);
    sprite.setPosition(pos);
}

MelonShot::~MelonShot()
{
}

void MelonShot::update()
{
    verticalSpeed = GRAVITY * ((pos.x - plant_x) / speed) - INTEGRAL_CONSTANT * GRAVITY * (distance / (zombieSpeed + speed));
    pos.x += speed;
    pos.y += verticalSpeed;
    sprite.setPosition(pos);
}
