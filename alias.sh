
alias ..='cd ..'
alias ...='cd ../../'
alias ....='cd ../../../'
alias .....='cd ../../../../'
alias ......='cd ../../../../../'

alias ls='ls --color=tty --classify $*'
alias ll='ls -lhA'

export TPATH=/var/lib/cloud9/technical_interview_questions/
export TZ='Asia/Shanghai'

function pause(){
   read -p "$*"
}

function mcd() {
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
    date
    pause "Press [Enter] key to confirm the files and current date..."
    git add -A
    git commit -m "${1:-little change}"
    git push -u origin master
    history -c
    history -w
}


#cat alias.sh > ~/.bash_aliases
