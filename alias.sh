
alias ls='ls --color=tty --classify $*'
alias ll='ls -lhA'

export TPATH=/var/lib/cloud9/technical_interview_questions/

function tcd() {
    cd $TPATH
    keyword="${1// }"
    if [ ! -z "$keyword" ]; 
    then
        dirdest=$(find . -iname *"$keyword"* | head -1)
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
    git add -A
    git commit -m "${1:-little change}"
    git push -u origin master
}


#cat alias.sh >> ~/.bash_aliases
