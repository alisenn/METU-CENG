#!/bin/sh

# $1 : Experiment Number
# $2 : Configure Number
# $3 : Experiment Times

if [ $1 = 1 ] ; then
  ssh r3\
      "chmod +x genconfig.sh && ./genconfig.sh r3 ${2}"
fi
if [ $1 = 2 ] ; then
  ssh r1\
      "chmod +x genconfig.sh && ./genconfig.sh r1 ${2}"
  ssh r2\
      "chmod +x genconfig.sh && ./genconfig.sh r2 ${2}"
fi

ssh d\
    "chmod +x genconfig.sh && ./genconfig.sh d ${2}"
ssh s\
    "chmod +x genconfig.sh && ./genconfig.sh s ${2}"