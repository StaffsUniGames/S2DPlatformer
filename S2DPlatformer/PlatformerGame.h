#pragma once

#include "Level.h"

#include "S2D/S2D.h" //Game is built with a pre-release version of S2D.

using namespace S2D;

class PlatformerGame : public Game
{
private:
    Texture2D* _winOverlay;
    Texture2D* _loseOverlay;
    Texture2D* _diedOverlay;

	SoundEffect* _backgroundMusic;

    // Meta-level game state.
    int _levelIndex;
    Level* _level;
    bool _wasContinuePressed;

    // When the time remaining is less than the warning time, it blinks on the hud
    static const int WarningTime;

    // We store our input states so that we only poll once per frame, 
    // then we use the same input state wherever needed
    Input::KeyboardState* _keyboardState;
        
    // The number of levels in the Levels directory of our content. We assume that
    // levels in our content are 0-based and that all numbers under this constant
    // have a level file present. This allows us to not need to check for the file
    // or handle exceptions, both of which can add unnecessary time to level loading.
    static const int NumberOfLevels;

public:
	PlatformerGame(int argc, char* argv[]);
	virtual ~PlatformerGame(void);

	void virtual LoadContent();
	void virtual Update(int elapsedTime);
	void virtual Draw(int elapsedTime);

	void HandleInput();
	void LoadNextLevel();
	void ReloadCurrentLevel();
	void DrawHud();

	static int TotalTime;
};

