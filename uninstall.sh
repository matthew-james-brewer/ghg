#!/usr/bin/env sh

harch=$(uname -m)

fname="$harch-linux-gnu-ghg.tar.gz"
curl "https://github.com/matthew-james-brewer/ghg/releases/latest/download/$fname" -Lo /tmp/$fname

read -p "Where is it installed? " ipath

for installed in $(tar tzf /tmp/$fname | sed "s/^compiled//"); do
 rm $ipath/$installed
done
