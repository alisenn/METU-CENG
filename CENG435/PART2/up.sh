#!/bin/sh

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
esac


if [ $s = true ] ; then
    ssh s\
    "python s.py s ${2} ${3} ${4}"
fi

if [ $r1 = true ] ; then
    ssh r1\
      "python r.py r1"
fi

if [ $r2 = true ] ; then
    ssh r2\
      "python r.py r2"
fi

if [ $r3 = true ] ; then
    ssh r3\
      "python r.py r3"
fi

if [ $d = true ] ; then
    ssh d\
    "python d.py d ${2} ${3}"
fi