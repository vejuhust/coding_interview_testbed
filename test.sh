#!/bin/bash

COMPILER=gcc
keyword="${1// }"

cd "$TPATH"

if [ -z "$keyword" ];
then
    printf "keyword should not be empty!\n"
    exit 1
fi

dirdest=$(find . -iname "*$keyword*" | head -1)
if [ -z "$dirdest" ];
then
    printf "project '%s' not found!\n" "$keyword"
    exit 2
fi

echo "$dirdest"
