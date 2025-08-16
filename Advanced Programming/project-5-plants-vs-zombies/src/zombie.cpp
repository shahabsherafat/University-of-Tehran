#include "../includes/zombie.hpp"

Zombie::Zombie(Vector2f init_pos, string init_id,
               int damage, int init_health, int init_hitRate, float init_speed, int numofLine)
{
    pos = init_pos;
    eatDamage = damage;
    health = init_health;
    hitRate = init_hitRate;
    speed = init_speed;
    lineNumber = numofLine;
    id = init_id;
    isEating = false;
    isFrozen = false;
    mainSpeed = init_speed;
}

Zombie::~Zombie()
{
}

void Zombie::render(RenderWindow &window)
{
    window.draw(sprite);
}

void Zombie::update()
{
    if (!isEating)
    {
        pos.x -= speed;
        sprite.setPosition(pos);
    }

    if (frozenClock.getElapsedTime().asSeconds() >= 4)
    {
        recovery_speed();
    }
}

FloatRect Zombie::get_rect()
{
    return sprite.getGlobalBounds();
}

int Zombie::get_line_number()
{
    return lineNumber;
}

int Zombie::get_x()
{
    return pos.x;
}

int Zombie::get_speed()
{
    return speed;
}

void Zombie::reduce_health(int damage)
{
    health -= damage;
}

bool Zombie::is_dead()
{
    return health <= 0;
}

bool Zombie::is_gone_in_the_house()
{
    return pos.x <= 590;
}

void Zombie::stand()
{
    isEating = true;
}

void Zombie::start_moving(){
    isEating = false;
}

bool Zombie::should_eat(){
    if(hitClock.getElapsedTime().asSeconds() >= hitRate){
        hitClock.restart();
        return true;
    }

    return false;
}

void Zombie::reduce_speed(int slowingAmount)
{
    frozenClock.restart();
    if(isFrozen){
        return;
    }
    speed -= slowingAmount;
    isFrozen = true;
    sprite.setColor(FROZEN_COLOR);
}

void Zombie::recovery_speed()
{
    isFrozen = false;
    speed = mainSpeed;
    sprite.setColor(ORIGINAL_COLOR);
}

int Zombie::get_eatDamage() { return eatDamage; }

int Zombie::get_hitRate() { return hitRate; }

void Zombie::restart_zombie_clock()
{
    frozenClock.restart();
}

OrdZombie::OrdZombie(Vector2f init_pos, string init_id, int damage, int init_health, int init_hitRate, float init_speed, int numofLine) : Zombie(init_pos, init_id, damage, init_health, init_hitRate, init_speed, numofLine)
{
    pos = init_pos;

    if (!texture.loadFromFile(PICS_PATH + id + "/walking/1.png"))
    {
        debug("failed to load zombie texture");
    }

    sprite.setTexture(texture);
    sprite.setScale(0.2, 0.2);
    sprite.setPosition(init_pos);
}

HugeZombie::HugeZombie(Vector2f init_pos, string init_id, int damage, int init_health, int init_hitRate, float init_speed, int numofLine) : Zombie(init_pos, init_id, damage, init_health, init_hitRate, init_speed, numofLine)
{
    pos = init_pos;

    if (!texture.loadFromFile(PICS_PATH + "Gargantuar.png"))
    {
        debug("failed to load zombie texture");
    }

    sprite.setTexture(texture);
    sprite.setScale(0.4, 0.4);
    sprite.setPosition(init_pos);
}
