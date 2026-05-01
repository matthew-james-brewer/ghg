#!/usr/bin/env sh

harch=$(uname -m)
sarch=$(sed -n "s/^ID=//p" /etc/os-release | sed "s/['\"]//g")
sarchlike=$(sed -n "s/^ID_LIKE=//p" /etc/os-release | sed "s/['\"]//g")

arch_compat() {
 [ "$sarch" = "$1" ] || ( [ "$sarchlike" != "" ] && [ "$(echo "$sarchlike" | sed "s/\b$1\b//")" != "$sarchlike" ] )
 return $?
}

ext="tar.gz";

if $(arch_compat "debian"); then
 ext="deb";
fi

if $(arch_compat "rhel") || $(arch_compat "fedora"); then
 ext="rpm";
fi

if $(arch_compat "arch"); then
 set -e
 mkdir -p /tmp/ghg
 curl "https://github.com/matthew-james-brewer/ghg/raw/refs/heads/master/PKGBUILD" -Lo /tmp/ghg/PKGBUILD
 cd /tmp/ghg
 sudo -u nobody makepkg -si
 exit
fi

if $(arch_compat "alpine"); then
 set -e
 mkdir -p /tmp/ghg
 curl "https://github.com/matthew-james-brewer/ghg/raw/refs/heads/master/APKBUILD" -Lo /tmp/ghg/APKBUILD
 cd /tmp/ghg
 abuild -Fr
 apk add /root/packages/root/$harch/ghg-*.apk
 rm /root/packages/root/$harch/ghg-*.apk
 exit
fi

fname="$harch-linux-gnu-ghg.$ext"
curl "https://github.com/matthew-james-brewer/ghg/releases/latest/download/$fname" -Lo /tmp/$fname

case $ext in
 deb) apt install /tmp/$fname -y;;

 rpm) dnf install /tmp/$fname -y;;

 *) read -p "Your package manager could not be detected; please provide an install path (use /usr for a global install): " ipath < /dev/tty;
    tar xzvf /tmp/$fname -C /tmp;
    cp -r /tmp/compiled/* $ipath;
    rm -rf /tmp/compiled;;
esac

rm /tmp/$fname
