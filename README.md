# Vdev - Ddev - Hubert Gonera

## Welcome

Welcome to snake.
This is a simple game. You need to get the biggest snake possible, by eating fruit.

## Controls:

Right arrow to set direction to the right. Left to set to the left, etc.

If you hit a wall, or yourself, you lose.

In the main menu you can also use SPACE or ENTER to start a game, or Q to quit.

## Update notes:

**Patches:**
* Changes to README.
* Moved previous update logs to a seperate file.

## Versioning:

Version format: COMPATIBILITY.MAJOR.MINOR.PATCH

* COMPATIBILITY - Wheter or not this version savefiles etc. will work with another version. Some parts may still work with previous versions.
* MAJOR - Incermented if added new feature systems, heavily reworked existing ones, or added large features.
* MINOR - Incremented if added small to medium features in existing systems, or if they were reworked slightly. NOT INCREMENTED if new feature systems were added. Then MAJOR is incremented.
* PATCH - No new features, just bug fixes.

Each README has its build version in the beginning, and build date in dd/mm/yyyy.

If that build version and build date is Vdev or Ddev, that means you have a version that is in developement, and is not yet released.
If you want a README for a specific version, please download the release or source code for that README.
The same thing applies if you see Vdev or Ddev in the game - it means you are running a development version, or you changed those values in mainheader.h.

## Credits
Thanks to everyone who created and manages SFML.
https://www.sfml-dev.org/

Big thanks to Miros³aw Zelent and Damian Stelmach for giving me an easy introduction to c++ in the first place, many years ago.
https://www.youtube.com/channel/UCzn6vAfspIcagLax1fck_jw

## Building the game yourself

### SFML
This version was made using SFML 2.6.1 for VS2022 32-bit.
https://www.sfml-dev.org/files/SFML-2.6.1-windows-vc17-32-bit.zip

Remember to download it and link it properly to your IDE.

The game uses dynamic linking, and the requiered .dll files are already in the repo.