# Suckless 

## Description
This project is a dynamic window manager for X. It manages windows in tiled, monocle and floating layouts. All of the layouts can be applied dynamically, optimising the environment for the application in use and the task performed. Minimalistic and efficient, it's designed to 'suck less', providing a streamlined and clean user experience. It's highly customizable and extensible, allowing users to tailor the environment to their specific needs.
## Installation
### Dependencies
```bash
sudo pacman -S libxft libxinerama freetype2 libx11 fontconfig base-devel feh flameshot xclip dunst cronie acpi \
  firefox chromium pcmanfm sxiv kitty neovim pavucontrol rofi-emoji discord noto-fonts noto-fonts-cjk noto-fonts-emoji \
  noto-fonts-extra ttf-jetbrains-mono-nerd obs-studio spotify-launcher discord picom \
```
### Build and Install
to build and install the project, follow these steps:
```bash
# Navigate to dwm directory and install
cd dwm
sudo make install

# Navigate to dmenu directory and install
cd ../dmenu
sudo make install

# Navigate to slock directory and install
cd ../slock
sudo make install

# Navigate to slstatus directory and install
cd ../slstatus
sudo make install
```
### Post Installation
Add the file .xinitrc to your home directory with the following content:
```bash
~/.fehbg &
flameshot &
xsetroot -cursor_name left_ptr &
picom -b &
slstatus &
exec dwm
```