### Installation
install dependencies
```bash
sudo pacman -S libxft libxinerama freetype2 libx11 fontconfig base-devel feh flameshot xclip
```
build and install
```bash
cd dwm
sudo make install

cd ../dmenu
sudo make install

cd ../slock
sudo make install

cd ../slstatus
sudo make install
```
add file .xinitrc to your homedir
```bash
~/.fehbg &
xsetroot -cursor_name left_ptr &
slstatus &
exec dwm
```