
alias ..='cd ..'
alias ...='cd ../../'
alias ....='cd ../../../'
alias .....='cd ../../../../'
alias ......='cd ../../../../../'

alias ls='ls --color=tty --classify $*'
alias ll='ls -lhA'

export TPATH=/var/lib/cloud9/coding_interview_testbed/
export TZ='Asia/Shanghai'

function pause(){
   read -p "$*"
}

function mcd() {
    mkdir -p "$1" && cd "$1"
}

function mcdc() {
    mkdir -p "$1" && cd "$1" && touch "${1##*/}.c"
}

function tcd() {
    cd $TPATH
    keyword="${1// }"
    if [ ! -z "$keyword" ]; 
    then
        dirdest=$(find . -iname "*$keyword*" -not -path "./.git/*" | head -1)
        if [ -z "$dirdest" ];
        then
            printf "%s not found!\n" "$keyword"
            return 1
        else
            cd "$dirdest"
            return 0
        fi
    fi
}

function tpush() {
    cd $TPATH
    git status
    datestr="$(date)"
    echo -e "\033[0;31mCurrent Time: ${datestr}\033[0m"
    pause "Press [Enter] key to confirm the files and current date..."
    
    git add -A
    git commit -m "${1:-small changes}"
    git push -u origin master
    history -c
    history -w
}


# cat alias.sh > ~/.bash_aliases
