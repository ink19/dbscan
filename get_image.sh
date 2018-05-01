#!/usr/bin/sh
for file in $(ls ./diff_data)
do
    matlab -nosplash -nodesktop -r "echo_image('./diff_data/${file}', './data_image/${file%.*}.jpg')"
done