Testbed for Coding Interview
=============================

This project was initially created to make myself prepared for coding interviews in Microsoft.

It was developed with [Cloud9](https://c9.io/) and running on [Debian](http://beagleboard.org/project/Debian/) with [BeagleBone Black (Rev.C)](http://elinux.org/Beagleboard:BeagleBoneBlack). Actually it can easily deployed to any popular Linux environments with `Bash`, `Python` and compilers.


## Features
* Test case generator     
* Batch test      
* Common shortcuts / aliases      


## Deploy

1. Git clone or extract the compressed file to your desired directory    
2. Change the value of **TPATH** in the following line into your desired directory in `alias.sh`:     
`export TPATH=/var/lib/cloud9/coding_interview_testbed/`
3. Execute `cat alias.sh >> ~/.bash_aliases` to add shortcuts to your environment. And ensure `~/.bash_aliases` loaded by `~/.bashrc` successfully or add the following lines to `~/.bashrc`:
```bash
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi
```


## Usage

