# V1.1.1.1 - 20.10.2024 - Hubert Gonera

## Welcome

Welcome to snake.
This is a simple game. You need to get the biggest snake possible, by eating fruit.

## Controls:

Right arrow to set direction to the right. Left to set to the left, etc.

If you hit a wall, or yourself, you lose.

In the main menu you can also use SPACE or ENTER to start a game, or Q to quit.

## Update notes:

**Patches:**
* Small changes in README.

## Versioning:

Version format: COMPATIBILITY.MAJOR.MINOR.PATCH

* COMPATIBILITY - Wheter or not this version savefiles etc. will work with another version. Some parts may still work with previous versions.
* MAJOR - Incermented if added new feature systems, heavily reworked existing ones, or added large features.
* MINOR - Incremented if added small to medium features in existing systems, or if they were reworked slightly. NOT INCREMENTED if new feature systems were added. Then MAJOR is incremented.
* PATCH - No new features, just bug fixes.

Each README has its build version in the beginning, and build date in dd/mm/yyyy.

## Credits
Thanks to everyone who created and manages SFML.
https://www.sfml-dev.org/

Big thanks to Miros�aw Zelent and Damian Stelmach for giving me an easy introduction to c++ in the first place, many years ago.
https://www.youtube.com/channel/UCzn6vAfspIcagLax1fck_jw

## Building the game yourself

### SFML
This version was made using SFML 2.6.1 for VS2022 32-bit.
https://www.sfml-dev.org/files/SFML-2.6.1-windows-vc17-32-bit.zip

Remember to download it and link it properly to your IDE.

The game uses dynamic linking, and the requiered .dll files are already in the repo.

# Previous update notes:

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