#!/bin/bash

TZ='Asia/Shanghai'; export TZ

COMPILER=gcc

keyword="${1// }"
dirtest="/tmp/test-$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 8 | head -n 1)/"
dirin="$dirtest"input/
dirout="$dirtest"output/
fileexe="$dirtest"a.out

color_none='\033[0m'
color_red='\033[0;31m'
color_blue='\033[0;34m'
color_green='\033[0;32m'
color_yellow='\033[1;33m'

function update_date() {
    strtmp="$(date '+%T:%N')"
    strdate="${strtmp:0:12}"
}

function colorize_output() {
    echo -e "${1}${2}${color_none}"
}

function print_log() {
    content=$(update_date && printf "[%s] %s" "$strdate" "$*")
    colorize_output "$color_yellow" "$content" 
}

function print_warn() {
    content=$(update_date && printf "[%s] %s" "$strdate" "$*")
    colorize_output "$color_red" "$content"
}

function print_ok() {
    content=$(update_date && printf "[%s] %s" "$strdate" "$*")
    colorize_output "$color_green" "$content"
}

function print_info() {
    content=$(update_date && printf "[%s] %s" "$strdate" "$*")
    colorize_output "$color_blue" "$content"
}

function test_and_diff() {
    input=$1
    output=$2
    print_info "input file content - '${input}'"
    colorize_output "$color_blue" "$(cat "$input" | head -10)"
    print_info "output file content - '${output}'"
    colorize_output "$color_blue" "$(cat "$output" | head -10)"
}

function test_only() {
    input=$1
    print_info "input file content - '${input}'"
    colorize_output "$color_blue" "$(cat "$input" | head -10)"
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

print_log "copy source codes and test cases"
cp -v *.c "$dirtest"
cp -v input*.txt "$dirin"
cp -v output*.txt "$dirout"

cd "$dirtest"
print_log "compile source codes"
time ${COMPILER} *.c -Wall -Wextra -o "$fileexe"

if [ -e "$fileexe" ];
then
    print_ok "file '${fileexe}' was built successfully"
    count=0
    for filein in $(find "$dirin" -iname "*.txt" | sort) 
    do
        count=`expr $count + 1`
        strtmp="${filein##*/}"
        fileout="${dirout}${strtmp//input/output}"
        if [ -e "$fileout" ];
        then
            print_log "test case: ${count} - with full data:"
            test_and_diff "$filein" "$fileout"
        else
            print_log "test case: ${count} - without output data."
            test_only "$filein"
        fi
    done
else
    print_warn "build failure"
fi

print_log "clean up tmp files"
rm -vfr "$dirtest"

print_log "project '${nameprj}' - test ends"
