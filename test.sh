#!/bin/bash

TZ='Asia/Shanghai'; export TZ

compiler=gcc
time_count=time
cutter=1-150

verbose=
limitdata=5
dirtest="/tmp/test-$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 8 | head -n 1)/"
dirin="$dirtest"input/
dirout="$dirtest"output/
fileexe="$dirtest"a.out
filetmpin="$dirtest"input.txt
filetmpout="$dirtest"output.txt

count_all=0
count_ok=0

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
    input="$1"
    output="$2"
    print_info "input file content - '${input}'"
    colorize_output "$color_blue" "$(cat "$input" | head -${limitdata} | cut -c ${cutter})"
    print_info "output file content - '${output}'"
    colorize_output "$color_blue" "$(cat "$output" | head -${limitdata} | cut -c ${cutter})"
    cp -f"$verbose" "$input" "$filetmpin"
    print_log "execute '${fileexe}' with '${input}'"
    eval "$time_count" "$fileexe"
    if [ 0 -eq "$?" ];
    then
        print_ok "execution success"
        result=$(diff -sb "$output" "$filetmpout")
        if [ 0 -eq "$?" ];
        then
            print_ok "test success"
            count_ok=`expr $count_ok + 1`
        else
            print_warn "test failure"
            cutted=""
            for line in "$result"
            do
                cutted+=$(echo "$line" | cut -c "$cutter")
            done
            colorize_output "$color_red" "$cutted"
        fi
    else
        print_warn "execution failure"
    fi
    rm -f"$verbose" "$filetmpin" "$filetmpout"
}

function test_only() {
    input="$1"
    if [ -e "$input" ];
    then
        print_info "input file content - '${input}'"
        colorize_output "$color_blue" "$(cat "$input" | head -${limitdata} | cut -c ${cutter})"
        cp -f"$verbose" "$input" "$filetmpin"
        print_log "execute '${fileexe}' with '${input}'"
    else
        print_log "execute '${fileexe}' without input file"
    fi
    result=$(eval "$time_count" "$fileexe")
    if [ 0 -eq "$?" ];
    then
        print_ok "execution && test (tentative) success"
        count_ok=`expr $count_ok + 1`
        if [ -e "$filetmpout" ];
        then
            print_info "execution result file - '${filetmpout}'"
            colorize_output "$color_blue" "$(cat "$filetmpout" | head -${limitdata} | cut -c ${cutter})"
        else
            print_info "execution result stdout"
            colorize_output "$color_blue" "$result"
        fi
    else
        print_warn "execution || test failure"
        colorize_output "$color_red" "$result"
    fi
    rm -f"$verbose" "$filetmpin" "$filetmpout"
}


cd "$TPATH"

keyword="${1// }"
if [ -z "$keyword" ];
then
    print_warn "keyword should not be empty!"
    exit 1
fi

dirsrc=$(find . -iname "*$keyword*" -not -path "./.git/*" | head -1)
if [ -z "$dirsrc" ] || [ ! -d "$dirsrc" ];
then
    print_warn "project '${keyword}' not found!"
    exit 2
fi
cd "$dirsrc"

filesrc=$(find . -maxdepth 1 -iname "*.c")
if [ -z "$filesrc" ];
then
    print_warn "source code in '${dirsrc}' not found!"
    exit 3
fi

nameprj="${dirsrc##*/}"
print_log "project '${nameprj}' - test starts"

mkdir -p"$verbose" "$dirtest"
mkdir -p"$verbose" "$dirin"
mkdir -p"$verbose" "$dirout"

print_log "copy source codes and test cases"
cp -f"$verbose" *.c "$dirtest"
cp -f"$verbose" input/input*.txt "$dirin"
cp -f"$verbose" output/output*.txt "$dirout"

cd "$dirtest"
print_log "compile source codes"
eval "$time_count" "$compiler" *.c -std=c99 -Wall -Wextra -o "$fileexe"

if [ -e "$fileexe" ];
then
    print_ok "file '${fileexe}' was built successfully"
    for filein in $(find "$dirin" -iname "*.txt" | sort) 
    do
        count_all=`expr $count_all + 1`
        strtmp="${filein##*/}"
        fileout="${dirout}${strtmp//input/output}"
        if [ -e "$fileout" ];
        then
            print_log "test case: ${count_all} - with full data:"
            test_and_diff "$filein" "$fileout"
        else
            print_log "test case: ${count_all} - without output data."
            test_only "$filein"
        fi
    done
    if [ 0 -eq "$count_all" ];
    then
        count_all=1
        print_log "test case: ${count_all} - without input/output data."
        test_only
    fi
else
    print_warn "build failure"
fi

print_log "clean up tmp files"
rm -rf"$verbose" "$dirtest"

if [ "$count_ok" -eq "$count_all" ];
then
    print_ok "all ${count_all} test(s) passed!"
else
    count_fail=`expr $count_all - $count_ok`
    print_warn "only ${count_ok} out of ${count_all} test(s) passed, ${count_fail} failed! take your time."
fi

print_log "project '${nameprj}' - test ends"
