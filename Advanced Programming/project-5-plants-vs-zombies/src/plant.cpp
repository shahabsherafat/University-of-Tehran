#include "../includes/plant.hpp"

Plant::Plant(Vector2f init_pos, int init_health, int numOfLine){
    pos = init_pos;
    health = init_health;
    lineNumber = numOfLine;
}

Plant::~Plant(){

}

Vector2f Plant::get_pos(){
    return pos;
}

int Plant::get_line_number(){
    return lineNumber;
}

void Plant::update(){

}

void Plant::render(RenderWindow& window){
    window.draw(sprite);
}

string Plant::get_id(){
    return id;
}

FloatRect Plant::get_rect(){
    return sprite.getGlobalBounds();
}

int Plant::get_health(){return health;}

void Plant::reduce_health(int eatDamage){
    health-=eatDamage;
}

bool Plant::is_dead(){
    return health<=0;
}


SunFlower::SunFlower(Vector2f init_pos, int init_health, int numOfLine) : Plant(init_pos, init_health, numOfLine){
    id = SUN_FLOWER_ID;

    if(!texture.loadFromFile(PICS_PATH + id + "/1.png")) {
        debug("failed to load sunflower texture");
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(0.22, 0.22);
    
    sprite.setPosition(Vector2f(pos.x+10, pos.y+5));
}

SunFlower::~SunFlower(){

}

bool SunFlower::should_produce_sun(){
    Time elapsed = produceClock.getElapsedTime();

    if(elapsed.asSeconds() >= produceRate){
        produceClock.restart();
        return true;
    }

    return false;
}

void SunFlower::update(){

}

PeaShooter::PeaShooter(Vector2f init_pos, int init_health, int init_hitRate, int numOfLine) : 
                       Plant(init_pos, init_health, numOfLine){
    id = PEA_SHOOTER_ID;
    hitRate = init_hitRate;

    if(!texture.loadFromFile(PICS_PATH + id + "/1.png")) {
        debug("failed to load peashooter texture");
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(0.25, 0.25);
    
    sprite.setPosition(Vector2f(pos.x+5, pos.y));
}

PeaShooter::~PeaShooter(){

}

bool PeaShooter::should_shoot(){
    Time elapsed = shootClock.getElapsedTime();

    if(elapsed.asSeconds() >= hitRate){
        shootClock.restart();
        return true;
    }

    return false;
}

void PeaShooter::update(){

}

IcePeaShooter::IcePeaShooter(Vector2f init_pos, int init_health, int init_hitRate, int numOfLine) : 
                       Plant(init_pos, init_health, numOfLine){
    id = ICE_PEA_SHOOTER_ID;
    hitRate = init_hitRate;
    if(!texture.loadFromFile(PICS_PATH + id + "/1.png")) {
        debug("failed to load IcePeaShooter texture");
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(0.32, 0.32);
    
    sprite.setPosition(Vector2f(pos.x-20, pos.y-15));
}

IcePeaShooter::~IcePeaShooter(){

}

bool IcePeaShooter::should_shoot(){
    Time elapsed = shootClock.getElapsedTime();

    if(elapsed.asSeconds() >= hitRate){
        shootClock.restart();
        return true;
    }

    return false;
}

void IcePeaShooter::update(){

}

Walnut::Walnut(Vector2f init_pos, int init_health, int numOfLine) : Plant(init_pos, init_health, numOfLine){
    id = WALNUT_ID;

    if(!texture.loadFromFile(PICS_PATH + id + "/1.png")) {
        debug("failed to load Walnut texture");
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(0.35, 0.35);
    
    sprite.setPosition(Vector2f(pos.x - 30, pos.y - 15));
}

Walnut::~Walnut(){

}

void Walnut::update(){

}

MelonPult::MelonPult(Vector2f init_pos, int init_health, int init_hitRate, int numOfLine) : 
                     Plant(init_pos, init_health, numOfLine){
    id = MELONPULT_ID;
    hitRate = init_hitRate;
    if(!texture.loadFromFile(PICS_PATH + id + "/1.png")) {
        debug("failed to load MelonPult texture");
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(0.3, 0.3);
    
    sprite.setPosition(pos);
}

MelonPult::~MelonPult(){

}

bool MelonPult::should_shoot(){
    Time elapsed = shootClock.getElapsedTime();

    if(elapsed.asSeconds() >= hitRate){
        shootClock.restart();
        return true;
    }
    
    return false;
}

void MelonPult::update(){

}
