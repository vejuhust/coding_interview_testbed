#!/bin/bash

TZ='Asia/Shanghai'; export TZ

COMPILER=gcc

keyword="${1// }"
dirtest="/tmp/test-$(cat /dev/urandom | tr -dc 'a-z0-9' | fold -w 8 | head -n 1)"
dirin="$dirtest"/input/
dirout="$dirtest"/output/

color_none='\033[0m'
color_red='\033[0;31m'
color_blue='\033[0;34m'
color_green='\033[0;32m'
color_yellow='\033[1;33m'

function print_log() {
    content=$(printf "[%s] %s" "$(date '+%T:%N')" "$*")
    echo -e "${color_yellow}${content}${color_none}"
}

function print_warn() {
    content=$(printf "[%s] %s" "$(date '+%T:%N')" "$*")
    echo -e "${color_red}${content}${color_none}"
}


cd "$TPATH"

if [ -z "$keyword" ];
then
    print_warn "keyword should not be empty!"
    exit 1
fi

dirsrc=$(find . -iname "*$keyword*" -not -path "./.git/*" | head -1)
if [ -z "$dirsrc" ];
then
    print_warn "project '${keyword}' not found!"
    exit 2
fi
cd "$dirsrc"

nameprj="${dirsrc##*/}"
print_log "project '${nameprj}' - test starts"

mkdir -vp "$dirtest"
mkdir -vp "$dirin"
mkdir -vp "$dirout"

print_log "copy source code and test cases"
cp -v *.c "$dirtest"
cp -v input*.txt "$dirin"
cp -v output*.txt "$dirout"

print_log "clean up tmp files"
rm -vfr "$dirtest"

print_log "project '${nameprj}' - test ends"
