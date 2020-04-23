#!/bin/sh

s=false
r1=false
r2=false
r3=false
d=false

case $1 in
  s)
    s=true
    ;;
  r1)
    r1=true
    ;;
  r2)
    r2=true
    ;;
  r3)
    r3=true
    ;;
  d)
    d=true
    ;;
  all)
    s=true
    r1=true
    r2=true
    r3=true
    d=true
    ;;
esac


if [ $s = true ] ; then
    scp ./s.py ./results.txt ./input.txt ./gen.py ./packet.py ./ipTable.py ./genconfig.sh s:
fi

if [ $r1 = true ] ; then
    scp ./r.py ./gen.py ./packet.py ./ipTable.py ./genconfig.sh r1:
fi

if [ $r2 = true ] ; then
    scp ./r.py ./gen.py ./packet.py ./ipTable.py ./genconfig.sh r2:
fi

if [ $r3 = true ] ; then
    scp ./r.py ./gen.py ./packet.py ./ipTable.py ./genconfig.sh r3:
fi

if [ $d = true ] ; then
    scp ./d.py ./gen.py ./packet.py ./ipTable.py ./genconfig.sh d:
fi