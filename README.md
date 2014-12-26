Testbed for Coding Interview
=============================

This project was initially created to make myself prepared for coding interviews in Microsoft.

It was developed with [Cloud9](https://c9.io/) and running on [Debian](http://beagleboard.org/project/Debian/) with [BeagleBone Black (Rev.C)](http://elinux.org/Beagleboard:BeagleBoneBlack). Actually it can easily deployed to any popular Linux environments with `Bash`, `Python` and compilers.


## Features

* Test case generator
* Batch test
* Common shortcuts / aliases


## Deploy

* Git clone or extract the compressed file to your desired directory
* Change the value of **TPATH** in the following line into your desired directory in `alias.sh`:
```bash
export TPATH=/var/lib/cloud9/coding_interview_testbed/
```
* Execute `cat alias.sh >> ~/.bash_aliases` to add shortcuts to your environment. And ensure `~/.bash_aliases` can be loaded by `~/.bashrc` successfully or add the following lines to that:
```bash
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi
```
* Relogin the session to load the `~/.bash_aliases`     
* Modify the two following lines in `test.sh` if your desired compiler is other than **gcc**:
```bash
compiler=gcc
eval "$time_count" "$compiler" *.c -std=c99 -Wall -Wextra -o "$fileexe"
```


## Usage

