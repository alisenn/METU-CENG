> e2237824 Ahmet Kürşad Şaşmaz
> e2264661 Ali Şen

# CENG435 Term Project Part 1

# HOW TO RUN

## SETTING UP THE SYSTEM
- Copy 'configureR1.sh' to the node r1
- Add execute permission with
```
chmod +x configureR1.sh
```
- Execute configureR1.sh with
```
./configureR1.sh
```
- Copy 'configureR2.sh' to the node r2
- Add execute permission with
```
chmod +x configureR2.sh
```
- Execute configureR2.sh with
```
./configureR2.sh
```
- Execute the command below for synchronizing nodes on every node
```
sudo ntpdate -qu north-america.pool.ntp.org
```
- Copy python scripts to the relevant nodes
## STARTING SERVERS
- Execute s.py
- Execute d.py
- Execute r1.py
- Execute r3.py
- Execute r2.py
- After a while, terminate all .py processes
- Get `[s|d|r1|r2|r3][s|d|r1|r2|r3]_[send|recv].txt` files in a directory from the nodes r1, r2 and r3
- You may use executable `stat` file to calculate the average RTT values

## RESET THE SYSTEM FOR EXPERIMENTS
- Copy 'configureR[1|2|3].sh' to the node r3
- Add execute permission with
```
chmod +x configureR*.sh
```
- Copy 'configureS[1|2|3].sh' to the node s
- Add execute permission with
```
chmod +x configureS*.sh
```
- Copy python scripts to the relevant nodes
## FOR EVERY SPECIFIC EXPERIMENT
- Execute related configureSx.sh with
```
./configureSx.sh
```
- Execute related configureRx.sh with
```
./configureRx.sh
```
- Execute d.py
- Execute r3.py
- Execute s.py
- After a while, terminate all .py processes
- Get `[send|recv].txt` files in a directory from the nodes s and d
- You may use executable `stat_exp` file to get matched packets' end to end delay values
