#!/bin/sh
for file in $(ls | grep csv)
do
    awk '{print NR}' $file|tail -n1 > ../data/${file%.*}.data
    cat ${file} >> ../data/${file%.*}.data
done