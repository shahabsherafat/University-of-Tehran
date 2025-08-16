#include "../includes/controller.hpp"

Controller::Controller(const vector<zombieData> &z,
                       const vector<plantData> &p,
                       const vector<int> &a,
                       const vector<int> &s)
{
    zombiesSettings = z;
    plantsSettings = p;
    attacksSettings = a;
    sunsSettings = s;

    add_cards();

    addingZombiesRate = attacksSettings[2];
    addingZombiesInterval = (float)attacksSettings[1] / addingZombiesRate;

    initialize_blocks();
    should_draw_currentBlock = false;

    load_credit_border_and_text();
}

void Controller::add_cards()
{
    float heightDif = 740 / plantsSettings.size(), cards_x = 380;
    int counter = 0;

    for (plantData p : plantsSettings)
    {
        Card *c = new Card(Vector2f(cards_x, 140 + counter * heightDif), p.price, p.id, p.coolDown);
        cards.push_back(c);
        counter++;
    }
}

Controller::~Controller()
{
    for (auto s : shots)
    {
        delete s;
    }
    for (auto z : zombies)
    {
        delete z;
    }
    for (auto sun : suns)
    {
        delete sun;
    }
    for (auto p : plants)
    {
        delete p;
    }
}

void Controller::load_credit_border_and_text()
{
    font.loadFromFile(FONT_PATH);

    totalCreditBorderTexture.loadFromFile(PICS_PATH + "border.png");
    totalCreditBorderTexture.setSmooth(true);
    totalCreditBorder.setTexture(totalCreditBorderTexture);
    totalCreditBorder.setScale(0.4, 0.4);
    totalCreditBorder.setPosition(Vector2f(800, 0));

    totalCreditText.setFont(font);
    totalCreditText.setCharacterSize(45);
    totalCreditText.setFillColor(Color::Black);
    totalCreditText.setStyle(Text::Bold);
    totalCreditText.setPosition(935, 10);
}

void Controller::initialize_blocks()
{
    for (int y = 215; y < 966; y += 150)
    {
        for (int x = 595; x < 1730; x += 126)
        {
            RectangleShape block;
            block.setPosition(Vector2f(x, y));
            block.setSize(Vector2f(126, 150));
            block.setFillColor(WHITE_BLOCKS_LOW_TRANSPARENCY);
            blocks.push_back(block);
        }
    }
}

void Controller::handle_mouse_press(Vector2i mousePos, State &state)
{
    for (Sun *s : suns)
    {
        s->check_if_is_touched(mousePos);

        if (s->get_shoud_be_removed())
        {
            totalCredit += SUN_CREDIT;
            return;
        }
    }

    for (Card *c : cards)
    {
        c->handle_mouse_press(mousePos);

        if (c->is_dragging())
        {
            return;
        }
    }
}

plantData Controller::get_plant_data_by_id(string plantId)
{
    for (plantData p : plantsSettings)
    {
        if (p.id == plantId)
        {
            return p;
        }
    }
}

void Controller::handle_mouse_release(Vector2i mousePos)
{
    for (Card *c : cards)
    {
        if (c->is_dragging())
        {
            bool is_seeded = false;

            if (should_draw_currentBlock and c->can_seed())
            {
                should_draw_currentBlock = false;

                if (blocks[currentBlockIndex].getFillColor() != RED_BLOCKS_LOW_TRANSPARENCY)
                {
                    is_seeded = true;
                    Vector2f seed_pos = {blocks[currentBlockIndex].getGlobalBounds().left, blocks[currentBlockIndex].getGlobalBounds().top}; // will change
                    string plantId = c->get_plant_id();
                    totalCredit -= c->get_price();
                    seed(seed_pos, get_plant_data_by_id(plantId));

                    blocks[currentBlockIndex].setFillColor(RED_BLOCKS_LOW_TRANSPARENCY);
                }
            }

            c->handle_mouse_release(mousePos, is_seeded);
            break;
        }
    }
}

void Controller::add_sun_random()
{
    DynamicSun *s = new DynamicSun(Vector2f(rng() % WIDTH, -100), sunsSettings[2]);
    suns.push_back(s);
}

void Controller::add_sun_inposition(Vector2f sunFlowerPos)
{
    StaticSun *s = new StaticSun(sunFlowerPos, sunsSettings[3]);
    suns.push_back(s);
}

void Controller::render(RenderWindow &window)
{
    if (should_draw_currentBlock)
    {
        window.draw(blocks[currentBlockIndex]);
    }

    for (Plant *p : plants)
    {
        p->render(window);
    }

    for (Card *c : cards)
    {
        c->render(window);
    }

    for (Zombie *z : zombies)
    {
        z->render(window);
    }

    for (Shot *s : shots)
    {
        s->render(window);
    }

    for (Sun *s : suns)
    {
        s->render(window);
    }

    window.draw(totalCreditBorder);
    window.draw(totalCreditText);
}

void Controller::remove_touched_and_outside_suns()
{
    vector<Sun *> removed;

    for (Sun *s : suns)
    {
        if (s->get_shoud_be_removed())
        {
            removed.push_back(s);
        }
    }

    for (Sun *s : removed)
    {
        suns.erase(remove(suns.begin(), suns.end(), s), suns.end());
        delete (s);
    }
}

void Controller::add_zombie_random()
{
    int x_position = WIDTH - 20;
    int numOfLine = rng() % 5 + 1;

    int y_position = ((numOfLine - 1) * 150) + 90;
    int randZom = rng() % zombiesSettings.size();
    zombieData tempz = zombiesSettings[randZom];
    Zombie *z;

    if (tempz.id == ORDINARY_ZOMBIE_ID)
    {
        z = new OrdZombie(Vector2f(x_position, y_position + 40), ORDINARY_ZOMBIE_ID, tempz.damage, tempz.health,
                          tempz.eatingRate, tempz.speed, numOfLine);
    }

    else if (tempz.id == HAIRMETALGARGANTUAR_ZOMBIE_ID)
    {
        z = new HugeZombie(Vector2f(x_position, y_position + 10), HAIRMETALGARGANTUAR_ZOMBIE_ID, tempz.damage, tempz.health,
                           tempz.eatingRate, tempz.speed, numOfLine);
    }

    zombies.push_back(z);
}

void Controller::remove_outside_shots()
{
    vector<Shot *> removed_shots;

    for (Shot *s : shots)
    {
        if (s->is_out())
        {
            removed_shots.push_back(s);
        }
    }

    for (Shot *s : removed_shots)
    {
        shots.erase(remove(shots.begin(), shots.end(), s), shots.end());
        delete (s);
    }
}

void Controller::update_cards(RenderWindow &window)
{
    Vector2i mousePos = Mouse::getPosition(window);
    for (Card *c : cards)
    {
        c->update(totalCredit, mousePos);
        if (c->is_dragging())
        {
            for (int i = 0; i < NUM_OF_GAME_BLOCKS; i++)
            {
                if (blocks[i].getGlobalBounds().contains((Vector2f)mousePos))
                {
                    should_draw_currentBlock = true;
                    currentBlockIndex = i;
                    break;
                }
            }
        }
    }
}

void Controller::update_plants()
{
    for (Plant *p : plants)
    {
        p->update();
        string id = p->get_id();
        plantData plant = get_plant_data_by_id(id);

        if (id == SUN_FLOWER_ID)
        {
            SunFlower *s = (SunFlower *)p;

            if (s->should_produce_sun())
            {
                add_sun_inposition(p->get_pos());
            }
        }

        else if (id == PEA_SHOOTER_ID)
        {
            PeaShooter *pea = (PeaShooter *)p;

            if (pea->should_shoot())
            {
                add_shot(pea->get_pos(), plant, pea->get_line_number());
            }
        }

        else if (id == ICE_PEA_SHOOTER_ID)
        {
            IcePeaShooter *ice = (IcePeaShooter *)p;

            if (ice->should_shoot())
            {
                add_shot(ice->get_pos(), plant, ice->get_line_number());
            }
        }

        else if (id == MELONPULT_ID)
        {
            MelonPult *melon = (MelonPult *)p;

            if (melon->should_shoot())
            {
                add_shot(melon->get_pos(), plant, melon->get_line_number());
            }
        }
    }
}

void Controller::update_shots()
{
    for (Shot *s : shots)
    {
        s->update();
    }

    remove_outside_shots();
}

void Controller::update_suns()
{
    Time elapsed = sunClock.getElapsedTime();

    if (elapsed.asMilliseconds() >= sunsSettings[1] * 1000)
    {
        sunClock.restart();
        add_sun_random();
    }

    for (Sun *s : suns)
    {
        s->update();
    }

    remove_touched_and_outside_suns();
}

void Controller::update_zombies()
{
    Time zelapsed = addZombieClock.getElapsedTime();

    if (zelapsed.asMilliseconds() >= addingZombiesInterval * 1000)
    {
        add_zombie_random();
        addZombieClock.restart();
    }

    for (Zombie *z : zombies)
    {
        z->update();
    }
}

void Controller::update_adding_zombies_rate()
{
    Time elapsed_from_last_increasement = increaseRateClock.getElapsedTime();

    if (elapsed_from_last_increasement.asMilliseconds() >= attacksSettings[1] * 1000)
    {
        addingZombiesRate += attacksSettings[3];
        addingZombiesInterval = (float)attacksSettings[1] / addingZombiesRate;
        increaseRateClock.restart();
    }
}

void Controller::check_if_is_won(State &state)
{
    if (gameClock.getElapsedTime().asSeconds() >= attacksSettings[0])
    {
        attacksSettings[3] = 0;
        addingZombiesRate = 0;
        addingZombiesInterval = 1000000;

        if (zombies.size() == 0)
        {
            state = VICTORY_SCREEN;
        }
    }
}

void Controller::check_if_is_lost(State &state)
{
    for (Zombie *z : zombies)
    {
        if (z->is_gone_in_the_house())
        {
            state = GAMEOVER_SCREEN;
            return;
        }
    }
}

void Controller::update(RenderWindow &window, State &state)
{
    update_cards(window);
    update_plants();
    update_shots();
    update_suns();
    update_zombies();
    handle_collisions();
    update_adding_zombies_rate();
    handle_eating();
    check_if_is_won(state);
    check_if_is_lost(state);
    totalCreditText.setString(to_string(totalCredit));

    if (gameClock.getElapsedTime().asSeconds() >= attacksSettings[0])
    {
        attacksSettings[3] = 0;
        addingZombiesRate = 0;
        addingZombiesInterval = 1000000;
    }
}


int Controller::get_line_number(int height)
{
    if (height >= 150 and height <= 250)
    {
        return 1;
    }

    else if (height >= 340 and height <= 400)
    {
        return 2;
    }

    else if (height >= 470 and height <= 530)
    {
        return 3;
    }

    else if (height >= 620 and height <= 700)
    {
        return 4;
    }

    else if (height >= 770 and height <= 830)
    {
        return 5;
    }
}

void Controller::seed(Vector2f pos, plantData plant)
{
    int numOfLine = get_line_number(pos.y);

    if (plant.id == SUN_FLOWER_ID)
    {
        SunFlower *s = new SunFlower(pos, plant.health, numOfLine);
        plants.push_back(s);
    }

    else if (plant.id == PEA_SHOOTER_ID)
    {
        PeaShooter *p = new PeaShooter(pos, plant.health, plant.hitRate, numOfLine);
        plants.push_back(p);
    }

    else if (plant.id == ICE_PEA_SHOOTER_ID)
    {
        IcePeaShooter *i = new IcePeaShooter(pos, plant.health, plant.hitRate, numOfLine);
        plants.push_back(i);
    }

    else if (plant.id == WALNUT_ID)
    {
        Walnut *w = new Walnut(pos, plant.health, numOfLine);
        plants.push_back(w);
    }

    else if (plant.id == MELONPULT_ID)
    {
        MelonPult *m = new MelonPult(pos, plant.health, plant.hitRate, numOfLine);
        plants.push_back(m);
    }
}

Zombie *Controller::find_first_zombie_in_line(int numOfLine)
{
    for (Zombie *z : zombies)
    {
        if (z->get_line_number() == numOfLine)
        {
            return z;
        }
    }
    return NULL;
}

void Controller::add_shot(Vector2f plant_pos, plantData plant, int numOfLine)
{
    Vector2f shot_init_pos;

    if (plant.id == PEA_SHOOTER_ID)
    {
        shot_init_pos = {plant_pos.x + 85, plant_pos.y + 20};
        OrdShot *o = new OrdShot(shot_init_pos, plant.damage, plant.speed, numOfLine);
        shots.push_back(o);
    }

    else if (plant.id == ICE_PEA_SHOOTER_ID)
    {
        shot_init_pos = {plant_pos.x + 85, plant_pos.y + 25};
        IceShot *i = new IceShot(shot_init_pos, plant.damage, plant.speed, numOfLine);
        shots.push_back(i);
    }

    else if (plant.id == MELONPULT_ID)
    {
        shot_init_pos = {plant_pos.x + 5, plant_pos.y + 10};
        Zombie *closestZombie = find_first_zombie_in_line(numOfLine);
        if (closestZombie == NULL)
        {
            return;
        }
        MelonShot *m = new MelonShot(shot_init_pos, plant.damage, plant.speed, numOfLine,
                                     closestZombie->get_x() - shot_init_pos.x, closestZombie->get_speed());
        shots.push_back(m);
    }
}

void Controller::handle_collisions()
{
    vector<Shot *> removed_shots;
    vector<Zombie *> hurt_zombies;
    FloatRect zombie_rect;
    FloatRect shot_rect;

    for (Shot *s : shots)
    {
        shot_rect = s->get_rect();

        for (Zombie *z : zombies)
        {
            zombie_rect = z->get_rect();

            if (zombie_rect.intersects(shot_rect) && s->get_line_number() == z->get_line_number())
            {
                removed_shots.push_back(s);
                z->reduce_health(s->get_damage());

                if (IceShot *iceShot = dynamic_cast<IceShot *>(s))
                {
                        z->reduce_speed(iceShot->get_slowing_amount());
                }

                hurt_zombies.push_back(z);
                break;
            }
        }
    }

    for (Shot *s : removed_shots)
    {
        shots.erase(remove(shots.begin(), shots.end(), s), shots.end());
        delete s;
    }

    remove_dead_zombies(hurt_zombies);
}


void Controller::handle_eating()
{
    FloatRect zombie_rect;
    FloatRect plant_rect;

    for (Zombie *z : zombies)
    {
        bool eatingFlag = false;
        zombie_rect = z->get_rect();

        for (Plant *p : plants)
        {
            plant_rect = p->get_rect();

            if (zombie_rect.intersects(plant_rect) and p->get_line_number() == z->get_line_number())
            {
                z->stand();
                eatingFlag = true;

                if (z->should_eat())
                {
                    p->reduce_health(z->get_eatDamage());
                }
            }
        }

        if(!eatingFlag){
            z->start_moving();
        }
    }

    remove_dead_plants();
}

void Controller::remove_dead_plants()
{
    for (auto it = plants.begin(); it != plants.end();)
    {
        Plant *temp_plant = *it;

        if (temp_plant->is_dead())
        {
            whiten_red_block(temp_plant->get_pos());
            it = plants.erase(it);
            delete temp_plant;
        }
        else
            ++it;
    }
}


void Controller::whiten_red_block(Vector2f pos){
    FloatRect r;
    for(int i = 0;i<blocks.size();i++){
        r = blocks[i].getGlobalBounds();
        if(r.top == pos.y and r.left == pos.x){
            blocks[i].setFillColor(WHITE_BLOCKS_LOW_TRANSPARENCY);
        }
    }
}

void Controller::remove_dead_zombies(vector<Zombie *> &hurt_zombies)
{
    vector<Zombie *> dead_zombies;

    for (Zombie *z : hurt_zombies)
    {
        if (z->is_dead())
        {
            dead_zombies.push_back(z);
        }
    }

    for (Zombie *z : dead_zombies)
    {
        zombies.erase(remove(zombies.begin(), zombies.end(), z), zombies.end());
        delete z;
    }
}