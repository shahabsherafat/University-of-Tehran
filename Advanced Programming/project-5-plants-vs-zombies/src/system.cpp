#include "../includes/system.hpp"

vector<string> System::split(string s, string delimiter){
    int start = 0, end = 0;
    vector <string> result;

    while (end != -1) {
        end = s.find(delimiter, start);
        string segment = s.substr(start, end - start);

        if(segment != EMPTY){
            result.push_back(segment);
        }

        start = end + delimiter.size();
    }

    return result;
}

System::System(int width, int height)
{
    window.create(VideoMode(width, height), "UT PVZ", Style::Close);
    window.setFramerateLimit(FRAME_RATE);
    state = MAIN_MENU;

    if (!backgroundTexture.loadFromFile(PICS_PATH + "background.png"))
    {
        debug("failed to load image");
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!music.openFromFile(AUDIO_PATH + "bg.ogg"))
    {
        debug("failed to load music");
    }
    music.setLoop(true);

    get_zombies_settings();
    get_attacks_settings();
    get_plants_settings();
    get_suns_settings();
    
    load_buttons();
    load_menus();
    load_gameResults();
}

void System::load_buttons(){
    if(!playButtonTexture.loadFromFile(PLAYBUTTON_PIC_PATH)){
        debug("unable to load key pics");
    }

    playButtonSprite.setTexture(playButtonTexture);
    playButtonSprite.setScale(0.40, 0.40);
    playButtonSprite.setPosition(1070, 350);

    if(!quitButtonTexture.loadFromFile(QUITBUTTON_PIC_PATH)){
        debug("unable to load key pics");
    }

    quitButtonSprite.setTexture(quitButtonTexture);
    quitButtonSprite.setScale(0.40, 0.40);
    quitButtonSprite.setPosition(1070, 650);
    
    if(!resumeButtonTexture.loadFromFile(RESUMEBUTTTON_PIC_PATH)){
        debug("unable to load key pics");
    }

    resumeButtonSprite.setTexture(resumeButtonTexture);
    resumeButtonSprite.setScale(0.30, 0.30);
    resumeButtonSprite.setPosition(740, 480);

    if(!getBackToMainMenuButtonTexture.loadFromFile(MAINMENUBUTTON_PIC_PATH)){
        debug("unable to load key pics");
    }

    getBackToMainMenuButtonSprite.setTexture(getBackToMainMenuButtonTexture);
    getBackToMainMenuButtonSprite.setScale(0.30, 0.30);
    getBackToMainMenuButtonSprite.setPosition(740, 680);

    if(!pauseButtonTexture.loadFromFile(PAUSEBUTTON_PIC_PATH)){
        debug("Failed to load pause button picture");
    }
    pauseButton.setTexture(pauseButtonTexture);
    pauseButton.setScale(0.15, 0.15);
    pauseButton.setPosition(1690, 15);
}

void System::load_menus(){
    if(!mainMenuTexture.loadFromFile(MIANMENUSCREEN_PIC_PATH)){
        debug("unable to load menu pics");
    }

    mainMenuSprite.setTexture(mainMenuTexture);
    mainMenuSprite.setScale(0.45, 0.45);
    mainMenuSprite.setPosition(0, 0);

    if(!pauseMenuTexture.loadFromFile(PAUSESCREEN_PIC_PATH)){
        debug("unable to load menu pics");
    }

    pauseMenuSprite.setTexture(pauseMenuTexture);
    pauseMenuSprite.setScale(0.45, 0.45);
    pauseMenuSprite.setPosition(0, 0);

}

void System::load_gameResults(){
    if(!font.loadFromFile(FONT_PATH)) {
        debug("failed to load inactive texture");
    }

    victoryText.setFont(font);
    victoryText.setString("YOU WON!");
    victoryText.setCharacterSize(300);
    victoryText.setFillColor(RESULTS_TEXTS_COLOR);
    victoryText.setStyle(Text::Bold);
    victoryText.setPosition(450, 300);

    gameOverText.setFont(font);
    gameOverText.setString("THE ZOMBIES\n  ATE YOUR\n   BRAINS!");
    gameOverText.setCharacterSize(250);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setStyle(Text::Bold);
    gameOverText.setPosition(450, 50);
}


void System::get_zombies_settings(){
    ifstream settingsFile(ZOMBIES_SETTINGS_FILE_PATH);
    string line;
    vector<string> lineVec;
    
    while(getline(settingsFile, line)){
        lineVec = split(line, COMMA);

        for(string temp : lineVec){
            vector<string> data = split(temp, FIELD_SEPARATOR);
            zombieData z;
            z.id = data[0];//Be carefull to not leave a space at the first of zombie id in the csv file!
            z.damage = stof(data[1]);
            z.health = stof(data[2]);
            z.eatingRate = stof(data[3]);
            z.speed = stof(data[4]);
            
            zombiesSettings.push_back(z);
        }
    }
}

void System::get_plants_settings(){
    ifstream settingsFile(PLANTS_SETTINGS_FILE_PATH);
    string line;
    vector<string> lineVec;

    while(getline(settingsFile, line)){
        lineVec = split(line, COMMA);

        for(string temp : lineVec){
            vector<string> data = split(temp, FIELD_SEPARATOR);
            plantData p;
            p.id = data[0];//Be carefull to not leave a space at the first of zombie id in the csv file!
            p.damage = stof(data[1]);
            p.health = stof(data[2]);
            p.coolDown = stof(data[3]);
            p.hitRate = stof(data[4]);
            p.speed = stof(data[5]);
            p.price = stof(data[6]);
            
            plantsSettings.push_back(p);
        }
    }
}

void System::get_suns_settings(){
    ifstream settingsFile(SUNS_SETTINGS_FILE_PATH);
    string line;
    getline(settingsFile, line);
    vector<string> lineVec;
    lineVec = split(line, FIELD_SEPARATOR);

    for(string s : lineVec){
        sunsSettings.push_back(stof(s));
    }
}

void System::get_attacks_settings(){
    ifstream settingsFile(ATTACKS_SETTINGS_FILE_PATH);
    string line;
    getline(settingsFile, line);
    vector<string> lineVec;
    lineVec = split(line, FIELD_SEPARATOR);

    for(string s : lineVec){
        attacksSettings.push_back(stof(s));
    }
}

void System::start()
{
    while (window.isOpen() and state != EXIT)
    {
        update();
        render();
        handle_events();
    }
    exit(0);
}

void System::render()
{
    switch (state){
        case (IN_GAME):
            window.clear();
            window.draw(backgroundSprite);
            gamePlay->render(window);
            window.draw(pauseButton);
            break;
        case (PAUSE_MENU):
            window.draw(pauseMenuSprite);
            window.draw(getBackToMainMenuButtonSprite);
            window.draw(resumeButtonSprite);
            break;
        case (MAIN_MENU):
            window.draw(mainMenuSprite);
            window.draw(playButtonSprite);
            window.draw(quitButtonSprite);
            break;
        case (VICTORY_SCREEN):
            window.draw(backgroundSprite);
            gamePlay->render(window);
            window.draw(victoryText);
            break;
        case (GAMEOVER_SCREEN):
            window.draw(backgroundSprite);
            gamePlay->render(window);
            window.draw(gameOverText);
            break;
    }
    window.display();
}

void System::handle_events()
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type){
            case (Event::Closed):
                window.close();
                state = EXIT;
                break;
            case (Event::MouseButtonPressed):
                handle_mouse_press(event);
                break;
            case (Event::MouseButtonReleased):
                handle_mouse_release(event);
                break;
            default:
                break;
        }
    }
}

void System::handle_mouse_press(Event ev)
{
    if (ev.mouseButton.button == Mouse::Right)
        return;
    Vector2i mouse_pos = {ev.mouseButton.x, ev.mouseButton.y};
    switch (state){
        case (IN_GAME):
            gamePlay->handle_mouse_press(mouse_pos, state);
            break;
        case (PAUSE_MENU):
            break;
        case (MAIN_MENU):
            break;
        case (VICTORY_SCREEN):
            break;
        case (GAMEOVER_SCREEN):
            break;
    }
}

void System::handle_mouse_release(Event ev)
{
    if (ev.mouseButton.button == Mouse::Right)
        return;
    Vector2i mouse_pos = {ev.mouseButton.x, ev.mouseButton.y};
    switch (state)
    {
    case (IN_GAME):
        if(pauseButton.getGlobalBounds().contains((Vector2f)mouse_pos)){
            music.pause();
            state = PAUSE_MENU;
            break;
        }
        gamePlay->handle_mouse_release(mouse_pos);
        break;
    case (PAUSE_MENU):
        if(resumeButtonSprite.getGlobalBounds().contains(static_cast<Vector2f>(mouse_pos))){
            music.play();
            state = IN_GAME;
        }

        else if(getBackToMainMenuButtonSprite.getGlobalBounds().contains(static_cast<Vector2f>(mouse_pos))){

            state = MAIN_MENU;
        }
        break;
    case (MAIN_MENU):
        if(playButtonSprite.getGlobalBounds().contains(static_cast<Vector2f>(mouse_pos))){
            gamePlay = new Controller(zombiesSettings, plantsSettings, attacksSettings, sunsSettings);
            state = IN_GAME;
            music.play();
        }

        else if(quitButtonSprite.getGlobalBounds().contains(static_cast<Vector2f>(mouse_pos))){
            state = EXIT;
        }
        break;
    case (VICTORY_SCREEN):
        state = EXIT;
        break;
    case (GAMEOVER_SCREEN):
        state = EXIT;
        break;
    }
}

void System::update(){
    switch (state) {
        case (IN_GAME):
            gamePlay->update(window, state);
            break;
        case (PAUSE_MENU):
        // pause the clocks
            break;
        case (MAIN_MENU):
            break;
        case (VICTORY_SCREEN):
            break;
        case (GAMEOVER_SCREEN):
            break;
        case (EXIT):
            gamePlay->~Controller();
            delete(gamePlay);
            abort();
            break;
    }
}