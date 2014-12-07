
alias ls='ls --color=tty --classify $*'
alias ll='ls -lhA'
alias root='cd /var/lib/cloud9/technical_interview_questions/'

function tcd() {
    cd $(find . -iname *"$1"* | head -1)
}

function tpush() {
    git status
    git add -A
    git commit -m "${1:-little change}"
    git push -u origin master
}

#cat alias.sh >> ~/.bash_aliases 
