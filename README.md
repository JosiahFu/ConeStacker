# ConeStacker

## Building on Windows

1. Install Raylib

Download the official raylib installer and go through the install process:
https://github.com/raysan5/raylib/releases/download/4.5.0/raylib_installer_v4.5.mingw.64bit.exe

2. Install Raygui

Download a zip of the repository:
https://github.com/raysan5/raygui/releases/tag/4.0

Extract to C:/raylib/raygui so that `raylib.h` is located at C:/raylib/raygui/src/raylib.h

## Building on Linux

1. Install Raylib build dependencies

https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#install-required-libraries

(Not all of them may be necessary, experiment with leaving some out if you desire)

2. Install `raylib` and `raygui` from your distro's repos or install it manually with this command:

```bash
sudo bash << END
wget https://github.com/raysan5/raylib/releases/download/4.5.0/raylib-4.5.0_linux_amd64.tar.gz -P /tmp
tar -xvaf /tmp/raylib-4.5.0_linux_amd64.tar.gz -C /tmp
cp -r /tmp/raylib-4.5.0_linux_amd64/{include,lib} /usr/local
wget https://github.com/raysan5/raygui/raw/25c8c65a6e5f0f4d4b564a0343861898c6f2778b/src/raygui.h -P /usr/local/include
echo '/usr/local/lib/' > /etc/ld.so.conf.d/raylib-x86_64.conf
END
```

Reboot to load the changes to `/etc/ld.so.conf`.

Then run:

```bash
make
```
