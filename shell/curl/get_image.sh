#!/bin/bash
#RETRIEVE IMAGE FROM http://www.zhenhaotv.com/dazi.php

# HTTP POST REQUEST
basehost="http://www.zhenhaotv.com/"

word_gbk=$1
word=`echo $word_gbk | iconv -f utf-8 -t gb2312 `

fieldsets=`curl -d "text=$word&wzcolor=000000&bgcolor=ffffff&touming=on" "http://www.zhenhaotv.com/dazi.php" | grep fieldset | iconv -f gb2312 -t utf-8 | sed "s/<\/fieldset>/<\/fieldset>\n/g"`

echo "text=$word&wzcolor=000000&bgcolor=ffffff&touming=on"

OLDIFS=$IFS
IFS=$'\x0a'

for x in $fieldsets
do
echo -e "\n"
echo "FIELDSET = "$x
legend=`echo $x | sed "s/ *<fieldset>.*gif\" \/> //g" | sed "s/<\/legend>.*//g"`
echo "LEGEND=["$legend"]"
imgurl=`echo $x | sed "s/ *<fieldset>.*<\/legend>.*src=\"//g" | sed "s/\" id.*//g"`
echo "IMGURL=["$imgurl"]"
wget $basehost"/"$imgurl -O ${word_gbk}_$legend.png

done

IFS=$OLDIFS



#curl -d "text=鱼&wzcolor=000000&bgcolor=ffffff" "http://www.zhenhaotv.com/dazi.php" | grep fieldset | iconv -f gb2312 -t utf-8

