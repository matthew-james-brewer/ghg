# about ghg (generalized headphone game)

ghg is a program that lets you play simple games on headphones with volume buttons. These games can be programmed with json; an example is provided (AtypicalAdventure).

# How to install on:

## iPhone / iPad / mac

Download the original programs written in Apple Shortcuts: [icloud link](https://www.icloud.com/shortcuts/8e4fc6a71b504ec5acc433c7ee7d0261) + [volume helper](https://www.icloud.com/shortcuts/32b39ab19edd40d3bfa823ae8d67221f).
You'll still need to download and extract this repository so you can copy AtypicalAdventure into the iCloud shortcuts folder (if you need an example).

## Linux

### anything other than Debian, Red Hat/Fedora based, Alpine, or Arch

If you are not using Debian or Red Hat/Fedora based Linux, you'll need to manually install the dependencies: libcjson, libasound, and libespeak (or libesepeak-ng with a symlink). Exact package names vary between package managers.
Then you can continue on:

### all distros

To install, run `curl -Ls https://github.com/matthew-james-brewer/ghg/raw/refs/heads/master/smart-dl.sh | sudo sh`

On Arch and Alpine, this will build it from source. On Alpine, you will need to generate keys and trust them.

If you want to force it to use a different system, you can append the desired os name to the command. For example: `curl -Ls https://github.com/matthew-james-brewer/ghg/raw/refs/heads/master/smart-dl.sh | sudo sh debian`. Use `none` for no distro.

## Windows

On Windows, the only dependency is cJSON. It can be easily installed with vcpkg.

Then you can download the [compressed archive (for x86_64)](https://github.com/matthew-james-brewer/ghg/releases/latest/download/x86_64-windows-msvc-ghg.tar.gz).

There is also [a compressed arm64 archive](https://github.com/matthew-james-brewer/ghg/releases/latest/download/aarch64-windows-msvc-ghg.tar.gz).

# How to use

## Linux and Windows

ghg is a command-line only program. To use it, run `[install path]/games/ghg [install path]/var/games/ghg/examples/AtypicalAdventure`.

AtypicalAdventure is the name of the example, but you can also create your own headphone game (no docs yet).

# How to uninstall

## Linux

Debian based = `sudo apt remove ghg`

Red Hat / Fedora based = `sudo dnf remove ghg`

Arch = `pacman -R ghg`

Alpine = `apk del ghg`

Other = `curl -Ls https://github.com/matthew-james-brewer/ghg/raw/refs/heads/master/uninstall.sh | sudo sh`
