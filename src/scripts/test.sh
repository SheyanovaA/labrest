#!/bin/bash
cd /home/alina/labrest/src
count = 0
ans="$?"
echo "$ans"
until [ $ans -eq 1 ]
do
./labrest_client sheyanova.a 70C5HE1a <command.txt
ans="$?"
let "count = $count + 1"
echo "$ans"
sleep 5s
done
echo "$count" >> count.txt
cat count.txt
exit

