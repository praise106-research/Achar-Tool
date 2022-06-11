#!/bin/bash

figlet "Colassus Build" | lolcat

docker start colossus
docker exec colossus env TERM=xterm script -q -c "cd /data/klee-colassus/build ; make ; sudo make install"
docker exec colossus env TERM=xterm script -q -c "klee -help"


figlet "Done" | lolcat