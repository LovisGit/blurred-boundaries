# Welcome to **Blurred Boundaries**

**Blurred Boundaries** is not your ordinary maze game - it's a creative Crackme! The protagonist, an ELF, must find their way from their cozy home through a twisted forest to a mysterious treasure chest. But beware: The game holds more than meets the eye. 🚪✨

## 🎮 **Gameplay**
The ELF can **Walk:** To move through the world:
![](/assets/walking.png)

They can also **Sit:** Perfect for taking a break:
![](/assets/sitting.png)

The goal is to reach the treasure chest. But those familiar with ELF files know there might be more hidden here... 👀

## 🕵️‍♂️ **Crackme Challenge**
Blurred Boundaries is more than just a game - it's also a **Crackme**! Your task:
- Find hidden vulnerabilities or functions in the game code
- Give the ELF **superpowers** or discover secret mechanics. Can you make them fly? Create a portal? 🧙‍♂️

This is an opportunity to test your binary hacking skills, understand the mechanics behind an interactive ELF game, and find creative solutions.

## 🚀 **Getting Started**
1. **Download the game:**  
```zsh
git clone https://github.com/LovisGit/blurred-boundaries.git
cd blurred-boundaries  
```
2. **Download the libraries**
*Debian / Ubuntu with apt*
``` zsh
sudo apt update
sudo apt install build-essential g++ libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```
*MacOs with Homebrew*
```zsh
brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf
```
*Linux with  pacman*
```zsh
sudo pacman -S sdl2 sdl2_image sdl2_mixer sdl2_ttf
```
*Fedora*
```zsh
sudo dnf install gcc-c++ SDL2-devel SDL2_image-devel SDL2_mixer-devel SDL2_ttf-devel
```
3. **Play:**  
```zsh 
cd build
make
./blurred_boundaries Name
```
4. **Hack it**  

## 🛠️ **Developer Info**
- **Technology:** C++ with SDL2 (for graphics)
- **Platform:** Linux (x86_64)
- **ELF Format:** 64-bit Executable  
  The game was specifically designed to challenge understanding of the ELF file format.

## 📢 **Note**
- This is a university project for learning return-oriented-programming please respect the boundaries of Crackme challenges. Use your skills responsibly! You will find the project write-up in the repository.
- Have fun cracking - and share your experiences or solutions with us.

## 📜 Licenses & Credits

This repository contains both source code and third-party media assets. They are distributed under the following terms:

**Source Code**
The source code of this project is licensed under the [MIT License](LICENSE).

**Media Assets**
- **Music:** The background music is by **Alexander Nakarada**. 
  Source: [YouTube - Forest Walk](https://www.youtube.com/watch?v=wCOc3mYrLTw)
  *Used with permission for free, with required attribution.*
- **Player Sprites:** The character sprites are from **Merchant Shade** ([16x16 Puny Characters](https://merchant-shade.itch.io/16x16-puny-characters/devlog/357784/new-sprites)). 
  *Licensed under CC0 (Public Domain).*