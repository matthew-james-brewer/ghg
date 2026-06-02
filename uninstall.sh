#!/usr/bin/env sh

harch=$(uname -m)

fname="$harch-linux-gnu-ghg.tar.gz"
curl "http://libhacker.cc/static/ghg/release/latest/$fname" -Lo /tmp/$fname

read -p "Where is it installed? " ipath < /dev/tty

for installed in $(tar tzf /tmp/$fname | sed "s/^compiled//"); do
 if [ -d $ipath/$installed ]; then
  rmdir --ignore-fail-on-non-empty $ipath/$installed
 else
  rm $ipath/$installed
 fi
done
