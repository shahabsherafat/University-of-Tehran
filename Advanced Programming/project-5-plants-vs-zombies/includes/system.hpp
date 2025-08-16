#pragma once

#include "controller.hpp"

class System{
    private:
      State state;
      Controller* gamePlay;
      Texture backgroundTexture;
      Sprite backgroundSprite;
      
      vector<zombieData> zombiesSettings;
      vector<plantData> plantsSettings;
      vector<int> attacksSettings;
      vector<int> sunsSettings;

      Texture getBackToMainMenuButtonTexture;
      Sprite getBackToMainMenuButtonSprite;
      Texture resumeButtonTexture;
      Sprite resumeButtonSprite;
      Texture playButtonTexture;
      Sprite playButtonSprite;
      Texture quitButtonTexture;
      Sprite quitButtonSprite;
      Texture pauseButtonTexture;
      Sprite pauseButton;

      Texture pauseMenuTexture;
      Sprite pauseMenuSprite;
      Texture mainMenuTexture;
      Sprite mainMenuSprite;

      Text victoryText;
      Text gameOverText;
      Font font;

      Music music;
      
    public:
      System(int width, int height);
      vector<string> split(string s, string delimiter);

      RenderWindow window;
      void start();
      void render();
      void update();
      void handle_events();
      void handle_mouse_press(Event ev);
      void handle_mouse_release(Event ev);

      void get_zombies_settings();
      void get_plants_settings();
      void get_suns_settings();
      void get_attacks_settings();

      void load_buttons();
      void load_menus();
      void load_gameResults();
};