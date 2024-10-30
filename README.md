# V1.3.0.0-alpha-3 - 30.10.2024
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

**Patches:**
* Changes to versioning.
* Fixed snake reloading.

## Versioning:

Version format: COMPATIBILITY.MAJOR.MINOR.PATCH

* COMPATIBILITY - Wheter or not this version savefiles etc. will work with another version. Some parts may still work with previous versions.
* MAJOR - Incermented if added new feature systems, heavily reworked existing ones, or added large features.
* MINOR - Incremented if added small to medium features in existing systems, or if they were reworked. NOT INCREMENTED if new feature systems were added. Then MAJOR is incremented.
* PATCH - No new features, just bug fixes.

A version that contains the -alpha-n suffix is in development. New systems, features or reworks are underway, but the game itself is also playable
(albeit with bugs and unpolished). The n after alpha stands for the current alpha version. Think of the -alpha suffix as something analogous to 0.y.z
versions in the semantic versioning system (https://semver.org/). Many changes are coming, and when the version is ready, the suffix is deleted and the
version with just the tag is released.

Each README has its build version in the beginning, and build date in dd/mm/yyyy.

## Credits
Thanks to everyone who created and manages SFML.
https://www.sfml-dev.org/

Big thanks to Miroslaw Zelent and Damian Stelmach for giving me an easy introduction to c++ in the first place, many years ago.
https://www.youtube.com/channel/UCzn6vAfspIcagLax1fck_jw

Thanks to Tymon Drop for designing the snake graphics in V1.2.3.0 and implementing WASD controls.
https://github.com/Kimoworwa

## Building the game yourself

### SFML
This version was made using SFML 2.6.1 for VS2022 32-bit.
https://www.sfml-dev.org/files/SFML-2.6.1-windows-vc17-32-bit.zip

Remember to download it and link it properly to your IDE.

The game uses dynamic linking, and the requiered .dll files are already in the repo.
