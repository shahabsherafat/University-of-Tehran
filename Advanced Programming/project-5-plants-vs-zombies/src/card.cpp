#include "../includes/card.hpp"

Card::Card(Vector2f init_pos, int init_price, string plant_id, int coolDownTime){
    pos = init_pos;
    price = init_price;
    plantId = plant_id;
    coolDown = coolDownTime;
    dragging_situation = false;

    if(!plant_texture.loadFromFile(PICS_PATH + plantId + "/1.png")) {
        debug("failed to load plant texture");
    }
    plant_sprite.setTexture(plant_texture);
    set_scale_for_plant_sprite();
    plant_sprite.setColor(DRAGGING_LOW_TRANSPARENCY);
    plant_sprite.setPosition((Vector2f)init_pos);


    if(!active_texture.loadFromFile(PICS_PATH + "cards/" + plant_id + "active.png")) {
        debug("failed to load active texture");
    }
    if(!inactive_texture.loadFromFile(PICS_PATH + "cards/" + plant_id + "inactive.png")) {
        debug("failed to load inactive texture");
    }
    active_texture.setSmooth(true);
    inactive_texture.setSmooth(true);
    sprite.setTexture(inactive_texture);
    sprite.setScale(0.7, 0.7);

    sprite.setPosition((Vector2f)init_pos);

    if(!font.loadFromFile(FONT_PATH)) {
        debug("failed to load inactive texture");
    }
    priceText.setFont(font);
    priceText.setString(to_string(price));
    priceText.setCharacterSize(30);
    priceText.setFillColor(Color::Black);
    priceText.setStyle(Text::Bold);
    priceText.setPosition(pos.x + 33, pos.y + 80);
}

void Card::set_scale_for_plant_sprite(){
    if(plantId == PEA_SHOOTER_ID){
        plant_sprite.setScale(0.25, 0.25);
    }

    else if(plantId == ICE_PEA_SHOOTER_ID){
        plant_sprite.setScale(0.32, 0.32);
    }

    else if(plantId == WALNUT_ID){
        plant_sprite.setScale(0.35, 0.35);
    }

    else if(plantId == SUN_FLOWER_ID){
        plant_sprite.setScale(0.22, 0.22);
    }

    else if(plantId == MELONPULT_ID){
        plant_sprite.setScale(0.3, 0.3);
    }
}

void Card::render(RenderWindow& window){
    window.draw(sprite);
    window.draw(priceText);
    

    if(dragging_situation){
        window.draw(plant_sprite);
    }
}

void Card::update(int totalCredit, Vector2i mouse_pos){
    if(dragging_situation){
        Vector2f target((float)(mouse_pos.x) - plant_sprite.getGlobalBounds().width/2,
         (float)(mouse_pos.y) - plant_sprite.getGlobalBounds().height/2);
        plant_sprite.setPosition((Vector2f)target);
        fix_position();
    }

    Time elapsed_from_last_seed = coolDownClock.getElapsedTime();

    if(totalCredit >= price and elapsed_from_last_seed.asMilliseconds() >= coolDown * 1000){
        sprite.setTexture(active_texture);
        is_active = true;
    }

    else{
        sprite.setTexture(inactive_texture);
        is_active = false;
    }
}

void Card::handle_mouse_press(Vector2i mousePos){
    if(dragging_situation){
        if(plant_sprite.getGlobalBounds().contains((Vector2f)mousePos)){
            return;
        }
    }

    if(sprite.getGlobalBounds().contains((Vector2f)mousePos) and is_active){
        dragging_situation = true;
    }
}

void Card::handle_mouse_release(Vector2i mousePos, bool is_seeded){
    if(dragging_situation){
        dragging_situation = false;
        plant_sprite.setPosition((Vector2f)pos);

        if(is_seeded){
            coolDownClock.restart();
        }
    }
}

void Card::fix_position(){
    FloatRect rect = plant_sprite.getGlobalBounds();
    rect.top = max(0.f, rect.top);
    rect.top = min(rect.top, HEIGHT - rect.height);
    rect.left = max(0.f, rect.left);
    rect.left = min(rect.left, WIDTH - rect.width);
    plant_sprite.setPosition(rect.left, rect.top);
}

bool Card::is_dragging(){
    return dragging_situation;
}

string Card::get_plant_id(){
    return plantId;
}

bool Card::can_seed(){
    return is_active;
}

int Card::get_price(){
    return price;
}