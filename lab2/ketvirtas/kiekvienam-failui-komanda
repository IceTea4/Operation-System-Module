#!/bin/sh
dir=`pwd`
for i in * ; do 
    if test -d $dir/$i ; then
        cd   $dir/$i
        while echo “$i:”; read   x; do
            eval $x
        done
        cd ..
    fi
done
