#pragma once

#include "zombie.hpp"
#include "plant.hpp"
#include "shot.hpp"
#include "sun.hpp"
#include "card.hpp"

class Controller
{
private:
    vector<zombieData> zombiesSettings;
    vector<plantData> plantsSettings;
    vector<int> attacksSettings;
    vector<int> sunsSettings;

    mt19937 rng;
    Clock sunClock;
    Clock gameClock, increaseRateClock, addZombieClock;
    int totalCredit = 2000;
    int addingZombiesRate;
    float addingZombiesInterval;

    vector<Zombie *> zombies;
    void update_zombies();
    vector<Shot *> shots;
    void update_shots();
    vector<Plant *> plants;
    void update_plants();
    vector<Sun *> suns;
    void update_suns();
    vector<Card *> cards;
    void update_cards(RenderWindow &window);
    void update_adding_zombies_rate();

    vector<RectangleShape> blocks;
    int currentBlockIndex;
    bool should_draw_currentBlock;

    Text totalCreditText;
    Font font;
    Sprite totalCreditBorder;
    Texture totalCreditBorderTexture;

public:
    Controller(const vector<zombieData> &z,
               const vector<plantData> &p,
               const vector<int> &a,
               const vector<int> &s);

    ~Controller();
    void render(RenderWindow &window);
    void update(RenderWindow &window, State &state);
    void add_sun_random();
    void add_sun_inposition(Vector2f sunFlowerPos);
    void handle_mouse_press(Vector2i mousePos, State &state);
    void handle_mouse_release(Vector2i mousePos);
    void initialize_blocks();

    void remove_touched_and_outside_suns();

    void add_zombie_random();
    void add_cards();
    void load_credit_border_and_text();

    void seed(Vector2f pos, plantData plant);
    void add_shot(Vector2f plant_pos, plantData plant, int numOfLine);
    void remove_outside_shots();
    Zombie *find_first_zombie_in_line(int numOfLine);

    void remove_dead_zombies(vector<Zombie *> &hurt_zombies);
    void handle_collisions();
    int get_line_number(int height);

    void check_if_is_won(State &state);
    void check_if_is_lost(State &state);

    plantData get_plant_data_by_id(string plantId);
    void handle_eating();
    void remove_dead_plants();
    void whiten_red_block(Vector2f pos);
};