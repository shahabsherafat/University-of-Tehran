#include "../includes/sun.hpp"

Sun::Sun(Vector2f init_pos, int cost){
    pos = init_pos;
    credit = cost;
    should_be_removed = false;

    if(!texture.loadFromFile(PICS_PATH + "sun.png")) {
        debug("failed to load sun texture");
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(0.6, 0.6);

    sprite.setPosition((Vector2f)init_pos);
}

Sun::~Sun(){

}

void Sun::update(){
    
}

void Sun::render(RenderWindow& window){
    window.draw(sprite);
}

void Sun::check_if_is_touched(Vector2i mouse_pos){
    if(sprite.getGlobalBounds().contains((Vector2f)mouse_pos)){
        should_be_removed = true;
    }
}

bool Sun::get_shoud_be_removed(){
    return should_be_removed;
}

DynamicSun::DynamicSun(Vector2f init_pos, int cost) : Sun(init_pos, cost) {
    speed = 1;
}

void DynamicSun::check_if_is_outside(){
    if(pos.y > HEIGHT){
        should_be_removed = true;
    }
}

void DynamicSun::update(){
    pos.y += speed;
    sprite.setPosition((Vector2f)pos);

    check_if_is_outside();
}

StaticSun::StaticSun(Vector2f init_pos, int cost) : Sun(init_pos, cost) {
    place = GOING_UP;
    numOfMoves = 0;
}

void StaticSun::check_if_spawn_time_spent(){
    Time elapsedLife = lifeClock.getElapsedTime();

    if(elapsedLife.asMilliseconds() >= spawnTime * 1000){
        should_be_removed = true;
    }
}

void StaticSun::update(){
    switch (place){
        case GOING_UP:
            pos.y -= 6;
            pos.x += 2;
            sprite.setPosition(pos);
            numOfMoves ++;
            if(numOfMoves == 10){
                numOfMoves = 0;
                place = GOING_DOWN;
            }
            break;
        
        case GOING_DOWN:
            pos.y += 5;
            pos.x += 2;
            sprite.setPosition(pos);
            numOfMoves ++;
            if(numOfMoves == 10){
                place = ON_RIGHT_PLACE;
            }
            break;
            
        case ON_RIGHT_PLACE:
            break;
    }
    check_if_spawn_time_spent();
}