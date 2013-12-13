#!/bin/bash -x

media_files=`cat test_cases.conf | grep '^[^#]' | sed 's/^.*://g'`

for media_file in $media_files
#for media_file in `$configs`
do
    echo "media_file = {$media_file}"
done
