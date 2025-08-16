#pragma once

#include "consts.hpp"

class Card{
private:
    int price;
    int coolDown;
    bool dragging_situation;
    bool is_active;
    Clock coolDownClock;
    string plantId;
    Texture active_texture;
    Texture inactive_texture;
    Texture plant_texture;
    Sprite sprite;
    Sprite plant_sprite;
    Vector2f pos;
    Vector2f plant_pos;
    Font font;
    Text priceText;

    void set_scale_for_plant_sprite();
public:
    Card(Vector2f init_pos, int init_price, string plant_id, int coolDownTime);
    ~Card();
    bool is_dragging();
    bool can_seed();
    string get_plant_id();
    int get_price();
    void render(RenderWindow& window);
    void update(int totalCredit, Vector2i mouse_pos);
    void handle_mouse_press(Vector2i mousePos);
    void handle_mouse_release(Vector2i mousePos, bool is_seeded);
    void fix_position();
};
