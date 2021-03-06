#pragma once

#include "State.h"
#include "Entity.h"
#include "Grid.h"
#include "Water.h"
#include "BitmapText.h"
#include "WaterBar.h"
#include "ButtonManager.h"
#include <SFML/Audio.hpp>
#include <map>

// The minor version of the game
const int VERSION = 1;

const int GRID_LEFT = 70;
const float SUBMIT_INTERVAL = 0.1;
const float SUBMIT_INTERVAL_ITEM = 0.3;
const float SUBMIT_INTERVAL_BREAK = 1;
const float PALETTE_SELECT_TOP = 82;
const float PALETTE_BUTTONS_TOP = PALETTE_SELECT_TOP + 25;

const bool PALETTE_SELECT_ENABLED = true;

const bool NEW_MODE = true;

const bool DEBUG_ENABLED = false;
const bool PALETTE_SELECT_DEBUG_ENABLED = false;
const bool DEBUG_MUSIC_DISABLED = false;

class PlayState : public State {
public:
	virtual void init() override;
	virtual void gotEvent(sf::Event event) override;
	virtual void update(sf::Time elapsed) override;
	virtual void render(sf::RenderWindow &window) override;

	void initEntity(Entity &entity);

	void save();
	void load();

	enum {
		menu,
		playing,
		submitting,
		results,
		loss,
	} phase = menu;

private:
	void adjustMusicVolume(sf::Music &music, float desiredVolume, float factor);
	void playDigSound();

	void loadLevel(int level);
	// Do the effect of digging up an item, unless flagged is true
	void findItem(std::string item, bool flagged = false);
	void submit();

	float cameraY = -25;
	float menuPaneY = 0;

	float flashTime = 0;
	float flagFlashTime = 0;
	float scoreFlashTime = 0;
	float bestFlashTime = 0;
	float shellFlashTime = 0;

	float submitTime = 0;
	bool poppingFlags = false;

	// Level stats
	int level = -1;
	int jellies = 0;
	int flags = 0;
	std::string levelName = "";

	// Player stats
	int score = 0;
	int shells = 0;

	// Saved data
	std::map<std::string, int> saveData;
	// The high score
	const std::string best = "best";
	// The selected palette (-1 is the code to link the palette to the current level)
	const std::string selectedPalette = "palette";
	// The number of palettes that have been unlocked
	const std::string unlockedPalettes = "unlocked";
	const std::string muted = "muted";

	ButtonManager buttons;

	std::shared_ptr<Button> buttonStart;
	std::shared_ptr<Button> buttonExit;
	std::shared_ptr<Button> buttonSubmit;
	std::shared_ptr<Button> buttonShell;
	std::shared_ptr<Button> buttonMenu;
	std::shared_ptr<Button> buttonPaletteLeft;
	std::shared_ptr<Button> buttonPaletteLink;
	std::shared_ptr<Button> buttonPaletteRight;
	std::shared_ptr<Button> buttonMute;

	Grid grid;
	Water water;

	sf::Sprite leftPane;
	sf::Sprite rightPane;
	sf::Sprite paletteSelect;
	WaterBar waterBar;
	
	sf::Sprite title;
	sf::Sprite sun;
	sf::Sprite clouds;
	sf::Sprite dunes;

	sf::Sound soundDig;
	sf::Sound soundFlag;
	sf::Sound soundUnflag;
	sf::Sound soundShellFind;
	sf::Sound soundShellUse;
	sf::Sound soundSelect;
	sf::Sound soundError;
	sf::Sound soundJelly;
	sf::Sound soundScore;
	sf::Sound soundStart;

	sf::Music musicBase;
	sf::Music musicActive;
	sf::Music musicBeat;
	sf::Music musicWarning;
};

