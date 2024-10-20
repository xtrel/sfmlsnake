# Previous update notes:

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