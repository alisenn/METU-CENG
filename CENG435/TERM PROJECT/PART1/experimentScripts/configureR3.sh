d=$(getent ahosts "d" | cut -d " " -f 1 | uniq)

d_adapter=$(ip route get $d | grep -Po '(?<=(dev )).*(?= src| proto)')

sudo tc qdisc del dev $d_adapter root netem
sudo tc qdisc add dev $d_adapter root netem delay 50ms 5ms distribution normal
