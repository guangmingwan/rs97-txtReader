#!/bin/bash

mkdir -p bin
find . -name ".DS_Store" -exec rm {} \;  
rm -rf ipkg/home/
mkdir -p ipkg/home/retrofw/apps/gmenu2x/sections/media/
cp txtreader.lnk ipkg/home/retrofw/apps/gmenu2x/sections/media/txtreader.lnk
mkdir -p ipkg/home/retrofw/apps/qtxtReader/bin/
cp qtxtReader.dge ipkg/home/retrofw/apps/qtxtReader/bin/qtxtReader.dge
cp bin/qtxtReader ipkg/home/retrofw/apps/qtxtReader/bin/
cp background.png ipkg/home/retrofw/apps/qtxtReader/bin/
cp -R lib ipkg/home/retrofw/apps/qtxtReader/lib

cd ipkg

tar -czf control.tar.gz control --owner=0 --group=0
tar -czf data.tar.gz home --owner=0 --group=0
ar rv qtxtReader.ipk control.tar.gz data.tar.gz debian-binary

cd ..

mv ipkg/qtxtReader.ipk bin/
rm ipkg/control.tar.gz
rm ipkg/data.tar.gz
#rm ipkg/home/retrofw/apps/qtxtReader/qtxtReader.dge
#rm -R ipkg/home/retrofw/apps/qtxtReader/res
