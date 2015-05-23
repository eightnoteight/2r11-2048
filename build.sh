#!/bin/bash

SRCS="2048.c
      2048nc.c
      2048ac.c
      accacia/src/accacia.c"
INCS=-Iaccacia/src/
LDFLAGS=-lcurses

if [ ! -d obj ] ; then
    mkdir obj
fi
if [ ! -d bin ] ; then
    mkdir bin
fi
for s in ${SRCS}
do
    o=$(echo $s | sed s/\\.c/.o/)
    o=$(echo $o | sed s/.*\\/.*\\///)
    o="obj/"${o}
    gcc -c ${s} ${INCS} -o${o}
    if [ $? -ne 0 ] ; then
        echo "*** Caveman build failure!"
        exit 1
    fi
done

ldcmd="gcc -obin/2048 "

for s in ${SRCS}
do
    o=$(echo $s | sed s/\\.c/.o/)
    o=$(echo $o | sed s/.*\\/.*\\///)
    o="obj/"${o}" "
    ldcmd=${ldcmd}${o}
done

ldcmd=${ldcmd}${LDFLAGS}

${ldcmd}

if [ $? -ne 0 ] ; then
    echo "*** Caveman build failure!"
    exit 1
fi

echo "*** Caveman build succesful!"

exit 0
