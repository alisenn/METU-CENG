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
  experiment)
    s=true
    d=true
    ;;
  routers)
    r1=true
    r2=true
    r3=true
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
    ssh s\
      "killall -9 python"
fi

if [ $r1 = true ] ; then
    ssh r1\
      "killall -9 python"
fi

if [ $r2 = true ] ; then
    ssh r2\
      "killall -9 python"
fi

if [ $r3 = true ] ; then
    ssh r3\
      "killall -9 python"
fi

if [ $d = true ] ; then
    ssh d\
      "killall -9 python"
fi