#!/bin/bash

# Get Experiment Number and Set Loss Percent Value
case $2 in
  1)
    percent="5%"
    ;;
  2)
    percent="15%"
    ;;
  3)
    percent="38%"
    ;;
esac

# Who Am I?
me=$1

# Set Which Links Are Going To Be Configured
set_s=false
set_d=false
set_r1=false
set_r2=false
set_r3=false

case $me in
  s)
    set_r1=true
    set_r2=true
    set_r3=true
		;;
  d)
    set_r1=true
    set_r2=true
    set_r3=true
		;;
  r1)
    set_s=true
    set_d=true
  	;;
  r2)
    set_s=true
    set_d=true
    ;;
  r3)
    set_s=true
    set_d=true
  	;;
esac

# Configure Proper Links
if [ $set_s = true ] ; then
    s=$(getent ahosts "s" | cut -d " " -f 1 | uniq)
    s_adapter=$(ip route get $s | grep -Po '(?<=(dev )).*(?= src| proto)')
    sudo tc qdisc del dev $s_adapter root
    sudo tc qdisc add dev $s_adapter root netem loss $percent delay 3ms
fi

if [ $set_d = true ] ; then
    d=$(getent ahosts "d" | cut -d " " -f 1 | uniq)
    d_adapter=$(ip route get $d | grep -Po '(?<=(dev )).*(?= src| proto)')
    sudo tc qdisc del dev $d_adapter root
    sudo tc qdisc add dev $d_adapter root netem loss $percent delay 3ms
fi

if [ $set_r1 = true ] ; then
    r1=$(getent ahosts "r1" | cut -d " " -f 1 | uniq)
    r1_adapter=$(ip route get $r1 | grep -Po '(?<=(dev )).*(?= src| proto)')
    sudo tc qdisc del dev $r1_adapter root
    sudo tc qdisc add dev $r1_adapter root netem loss $percent delay 3ms
fi

if [ $set_r2 = true ] ; then
    r2=$(getent ahosts "r2" | cut -d " " -f 1 | uniq)
    r2_adapter=$(ip route get $r2 | grep -Po '(?<=(dev )).*(?= src| proto)')
    sudo tc qdisc del dev $r2_adapter root
    sudo tc qdisc add dev $r2_adapter root netem loss $percent delay 3ms
fi

if [ $set_r3 = true ] ; then
    r3=$(getent ahosts "r3" | cut -d " " -f 1 | uniq)
    r3_adapter=$(ip route get $r3 | grep -Po '(?<=(dev )).*(?= src| proto)')
    sudo tc qdisc del dev $r3_adapter root
    sudo tc qdisc add dev $r3_adapter root netem loss $percent delay 3ms
fi
