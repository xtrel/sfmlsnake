# V1.3.0.0-alpha-4 - 30.10.2024
By Hubert Gonera

## Welcome

Welcome to snake.
I have made this game to familiarize myself with SFML in C++, as well as managing a Github repo.

I am sure You know the premise of this game, but in the extremely unlikely event that you do not, here is a rundown:
* You are a snake.
* You want to grow, till you fill the whole map.
* The only way you can grow, is by eating fruit.

## Controls:

Right arrow to set direction to the right. Left to set to the left, etc.
You can also use WASD.

If you hit a wall, or yourself, you lose.

In the main menu you can also use SPACE or ENTER to start a game, or Q to quit.

After winning or losing, the game will display a message for 5 seconds, then quit to main menu. You can skip this by pressing enter or space.

## Update notes:

**Major:**
* Added basic settings menu along with changing and saving of fullscreen option.

**Minor:**
* Changed TPS to 128Hz, because of very small (but annoying) input lag on older machines with higher TPS.

**Patches:**
* Changes to versioning.
* Added tinydialogfiles, not used yet.
* Changes to "Building yourself" section.

## Versioning:

Version format: COMPATIBILITY.MAJOR.MINOR.PATCH(-suffix)

Version flags:

* COMPATIBILITY - Wheter or not this version savefiles etc. will work with another version. Some parts may still work with previous versions.
* MAJOR - Incermented if added new feature systems, heavily reworked existing ones, or added large features.
* MINOR - Incremented if added small to medium features in existing systems, or if they were reworked. NOT INCREMENTED if new feature systems were added. Then MAJOR is incremented.
* PATCH - No new features, just bug fixes.
* suffix - Explained below.

A version that contains the -alpha-n suffix is in development. New systems, features or reworks are underway, but the game itself is also playable
(albeit with bugs and unpolished). The n after alpha stands for the current alpha version. Think of the -alpha suffix as something analogous to 0.y.z
versions in the semantic versioning system (semver.org). Many changes are coming, and when the version is ready, the suffix is deleted and the
version with just the tag is released.

In each "Update notes" there are notes between the current update, and the previous update of that same flag. This means update logs compare for
example between 1.3.0.0 and 1.3.0.1 if the current version is 1.3.0.1. And they compare between 1.3.0.0 and 1.4.0.0 if the current version is 1.4.0.0.
Notably, this means when a version exits alpha, all of the alpha changes get put into the version update notes.
This does not apply to patch notes in updatelogs.md. They only get patch notes for that version.

Each README has its build version in the beginning, and build date in dd/mm/yyyy.

## Credits
Thanks to everyone who created and manages SFML.
www.sfml-dev.org

Thanks to Guillaume Vareille for creating and managing tinyfiledialogs.
www.ysengrin.com

Big thanks to Miroslaw Zelent and Damian Stelmach for giving me an easy introduction to c++ in the first place, many years ago.
www.youtube.com/channel/UCzn6vAfspIcagLax1fck_jw

Thanks to Tymon Drop for designing the snake graphics in V1.2.3.0 and implementing WASD controls.
www.github.com/Kimoworwa

## Building the game yourself

### SFML
This version uses 2.6.1 SFML for Visual Studio 2022, 32-bit.

Link and include it properly in your IDE (or VS).

### tinyfiledialogs
This version uses tinyfiledialogs v3.18.2.
Download it from www.sourceforge.net/projects/tinyfiledialogs.
In your IDE include the tinyfiledialogs.h, and link the tinyfiledialogs.c.

### Notice
Bear in mind I am very much a beginner in terms of installing libraries manually, and I may have got the terminology somewhere wrong.
But since I somehow figured it out, you can too.