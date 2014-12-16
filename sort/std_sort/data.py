#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random

limit_min = 1
limit_max = 1024


def print_length(data):
    print len(data)

def print_raw(raw):
    for item in raw:
        print item,
    print ""

def print_sorted(raw):
    data = sorted(raw)
    for item in data:
        print item,
    print ""

def output_result(raw):
    print "[INPUT]"
    print_length(raw)
    print_raw(raw)
    print "[OUTPUT]"
    print_sorted(raw)


def process(data):
    random.shuffle(data)


if __name__ == '__main__':
    raw = range(limit_min, limit_max + 1)
    process(raw)
    output_result(raw)
