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
* Modify the following lines in `test.sh` if your desired compiler is other than **gcc**:
```bash
compiler=gcc
eval "$time_count" "$compiler" *.c -std=c99 -Wall -Wextra -o "$fileexe"
cp -f"$verbose" *.c "$dirtest"
```
* If you're using languages like Java or Python, you may also need to adjust these lines:
```bash
fileexe="$dirtest"a.out
eval "$time_count" "$fileexe"
result=$(eval "$time_count" "$fileexe")
```


## Usage

### Start new projects
A new project should be put in a folder with unique name in **TPATH** directory. Shortcuts `mcd` and `mcdc` can help you with that.    
A source code file with extension (default **.c**) is a must for every project. Apart from source code file, input/output data should be placed in the same folder. Without input/output data, it will only be tested once.     
Thus a typical project may look like this:     
```
└── unique_char
    ├── input
    │   ├── input01.txt
    │   ├── input02.txt
    │   ├── input03.txt
    │   ├── input04.txt
    │   ├── input05.txt
    │   ├── input06.txt
    │   ├── input07.txt
    │   └── input08.txt
    ├── output
    │   ├── output01.txt
    │   ├── output02.txt
    │   ├── output03.txt
    │   ├── output04.txt
    │   ├── output05.txt
    │   ├── output06.txt
    │   ├── output07.txt
    │   └── output08.txt
    ├── raw.txt
    └── unique_char.c
```

### Write codes
You can use `tcd` as shortcut to switch to the project folder quickly.     
Your program should meet the following requirements:    
* Set exit code 0 if succeeded, non-zero for errors
* Read input data from `input.txt` if applicable
* Write output data to `output.txt` if applicable

### Create test cases
`generator.py` is a tool to help you create test cases from single text file.

### Run test cases

