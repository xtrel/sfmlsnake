# Previous update notes:

## V1.3.0.0-alpha-2
*29.10.2024*

**Patches:**
* Fixed "Game not opening for certain data.txt files" bug.
* Fixed saving and reloading of highscores.

## V1.3.0.0-alpha-1
*29.10.2024*

**Major:**
* Added the set.txt file to gamedata folder (or it will be generated on first run). It contains three lines, first is resolution width,
second is height, and the third contains either 0 for window mode or 1 for fullscreen.
In the future a proper settings GUI will be implemented. This is the main reason as for the alpha suffix.

**Minor:**
* You can now close the game during a round using Q.
* Background of the game is now a very dark gray, so that during fullscreen play in an aspect ratio different from the monitor, you can see the
worlds edges.
* Highscore saving and loading system now reloades and resaves the highscores after each run. Normally this wouldn't be needed, but in the case that
many people will be playing on the same .exe file, this should prevent overwriting highscore data. (And yes, I am surprised that such people exist,
but oh well, the cost to add this redundancy is bascially zero, so I might as well.)
* Uncapped the amount of saved highscores.

**Patches:**
* Changes to versioning.
* Backend optimizations and code restructuring.

## V1.2.4.1
*29.10.2024*

**Patches:**
* Updated game icon.

## V1.2.4.0
*29.10.2024*

**Minor:**
* Reworked snake graphics.

## V1.2.3.0
*26.10.2024*

**Minor:**
* Changed snake graphics.
* Added wasd controlls.
* Changed game icon.

## V1.2.2.1
*25.10.2024*

**Patches:**
* Fixed typos in README.

## V1.2.2.0
*25.10.2024*

**Minor:**
* Changed font and game icon.

**Patches:**
* Small changes to saving mechanisms - added capability to give a version tag to each highscore. Ensured backward compatibilty with previous saves, now if the game detects a highscore without a versiontag, it adds the "before V1.2.2.0" tag into it.
* Small changes to README.

## V1.2.1.0
*22.10.2024*

**Minor:**
* Added color grading to the snake's body, so it is easier to see which part is moving where.
* Increased TPS to 256Hz
* Lose and win screen now stays for 5 seconds, however you can press enter or space to exit to main menu instantly.

**Patch:**
* Small changes to README.

## V1.2.0.3
*20.10.2024*

**Patches:**
* Fixed in-game version tag.
* Hid console window.

## V1.2.0.2
*20.10.2024*

**Patches:**
* Fixed updatelogs.md

## V1.2.0.1
*20.10.2024*

**Patches:**
* Small changes to README, as well as project architecture.

## V1.2.0.0
*20.10.2024*

**Major:**
* Fully implemented highscore saving and loading, but as of now only the highest score is displayed, with no name.
	* -> In the future, it will be easy to add names to each highscore, as well as displaying any amount of them.

**Patches:**
* Optimizations.
* Changes to README.
* Moved previous update logs to a seperate file.

## V1.1.1.1
*20.10.2024*

**Patches:**
* Small changes in README.
	* -> Added credits.
	* -> Added info on how to build the game yourself.
* Added functions for reading and saving data, as well as writing logs.

## V1.1.1.0
*16.10.2024*

**Minor:**
* Pressing space and enter now also start the game, and Q closes it. (This is so the game can also be played without a mouse.)

**Patch:**
* Refined speed formula.

## V1.1.0.0
*14.10.2024*

**Major:**
* Added main menu.
* Added lose screen.
* Added basic button class for creating simple buttons.

**Minor:**
* Moved keyboard events over to the simulation part of the gameloop. As a result, controls feel way more immidiate now.

**Patch:**
* Various small optimizations.
* Increased text size during gameplay.

## V1.0.2.0
*13.10.2024*

**Minor:**
* Reworked the speed function. It is now not incremental, but instead follows something akin to a very flattened parabola.
* Moved from .txt README format over to .mb. Changed the versioning section a bit, as well as moved previous patchnotes to the current standard.

**Patches:**
* Added seed randomization for varying the location of fruit between runs. Previously, the fruit spawned in consistant locations in each run.

## V1.0.1.2
*10.10.2024*

**Patches:**
* Corrected game window name.
* Corrected in-game version tag display.
* Fixed "passing by yourself" bug.

## V1.0.1.1
*10.10.2024*

**Patches:**
* Made VS2022 automatically add neccessesary files to build directory. (Such as .dlls and README)
* Small formatting changes to README

## V1.0.1.0
*10.10.2024*

**Minor:**
* Increased TPS from 60 to 120

**Patches:**
* Added README:
	* -> Defined Versioning
	* -> Added content

## V1.0.0
*09.10.2024*

No README in this version. This update note was added in V1.0.1.0.
First functional version with minimal features, and some bugs.

#
Hubert Gonera