#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import string
import random


flags = [ "[INPUT]", "[OUTPUT]" ]
counter = {}


def random_string(size = 8, chars = string.ascii_lowercase + string.ascii_uppercase + string.digits):
    return ''.join(random.SystemRandom().choice(chars) for _ in range(size))

def load_raw_data(filename):
    file = open(filename, 'r')
    content = file.readlines()
    file.close()
    return content

def save_data(typename, content):
    if typename in counter:
        counter[typename] += 1
    else:
        counter[typename] = 1
    count = counter[typename]
    filename = "%s%s%.2d.txt" % (dirname, typename, count)
    file = open(filename, 'w')
    for line in content:
        if len(line) > 0:
            file.write(line + "\n")
    file.close()
    print "generated", filename, content


if __name__ == '__main__':
    dirname = "/tmp/data-%s/" % random_string()
    os.mkdir(dirname)
    
    lines_all = load_raw_data("string/reserve_sentence/raw.txt")
    lines_file = []
    typename = ""
    for line in lines_all:
        line = line.strip()
        if line in flags:
            if len(typename) > 0:
                save_data(typename, lines_file)
            lines_file = []
            typename = line.lstrip("[").rstrip("]").lower()
        else:
            lines_file.append(line)
    if len(typename) > 0:
        save_data(typename, lines_file)
    
    print dirname, "is ready now"
