# about ghg (generalized headphone game)

ghg is a program that lets you play simple games on headphones with volume buttons. These games can be programmed with json; an example is provided (AtypicalAdventure).

# How to install on:

## iPhone / iPad / mac

Download the original program written in Apple Shortcuts: [icloud link](https://www.icloud.com/shortcuts/8e4fc6a71b504ec5acc433c7ee7d0261).
You'll still need to download and extract this repository so you can copy AtypicalAdventure into the iCloud shortcuts folder (if you need an example).

## Linux

### anything other than Debian and Red Hat/Fedora based

If you are not using Debian or Red Hat/Fedora based Linux, you'll need to manually install the dependencies: libcjson, libasound, and libespeak (or libesepeak-ng with a symlink). Exact package names vary between package managers.

### all distros

After that, run `curl -Ls https://github.com/matthew-james-brewer/ghg/raw/refs/heads/master/smart-dl.sh | sudo sh`

## Windows

On Windows, the only dependency is cJSON. It can be easily installed with vcpkg.

Then you can download the [compressed archive (for x86_64)](https://github.com/matthew-james-brewer/ghg/releases/latest/download/x86_64-windows-msvc-ghg.tar.gz).

There is also [a compressed arm64 archive](https://github.com/matthew-james-brewer/ghg/releases/latest/download/aarch64-windows-msvc-ghg.tar.gz).

# How to use

## Linux and Windows

ghg is a command-line only program. To use it, run `[install path]/games/ghg [install path]/share/doc/ghg/examples/AtypicalAdventure`.

AtypicalAdventure is the name of the example, but you can also create your own headphone game (no docs yet).

# How to uninstall

## Linux

Debian based = `sudo apt remove ghg`

Red Hat / Fedora based = `sudo dnf remove ghg`

Other = `curl -Ls https://github.com/matthew-james-brewer/ghg/raw/refs/heads/master/uninstall.sh | sudo sh`
