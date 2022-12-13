#!/bin/bash

#-d (exist dir), -r (read perm), -nt (newer than)
for name in `ls /usr/include` ; do
    if test -d /usr/include/$name -a -r /usr/include/$name -a /usr/include/$name -nt /usr/include/stdio.h ; then
        echo $name
    fi
done
