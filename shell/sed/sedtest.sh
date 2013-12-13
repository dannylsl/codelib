#!/bin/bash

filename="apt.conf"
echo "show $filename"
nl $filename

echo "[DELETE]"
echo "================================"
echo "remove line 2"
nl $filename | sed '2d'

echo "remove line 2-3"
nl $filename | sed '2,3d'

echo "remove line 2-end"
nl $filename | sed '2,$d'


echo "[ADD STRING]"
echo "================================"
echo "add Drink tea after line 2"
nl $filename | sed '2a Drink tea'

echo "add Drink tea before line 2"
nl $filename | sed '2i Drink tea'

echo "add string with several lines"
nl $filename | sed '2i Drink tea or ......\
       drink beer?'


echo "[CHANGE STRING]"
echo "================================"
echo "change one line to 'Hello World'"
nl $filename | sed '2c Hello World'

echo "change serval lines to 'Hello World'"
nl $filename | sed '2,3c Hello World'

echo "[REPLACE STRING]"
echo "================================"
echo "change all Acquire to Atp-Acquire"
nl $filename | sed 's/Acquire/Apt-Acquire/g'

echo "[GET IP ADDR]"
echo "================================"
ifconfig eth0| grep 'inet addr' | sed 's/^.*addr://g' | sed 's/Bcast.*$//g'
