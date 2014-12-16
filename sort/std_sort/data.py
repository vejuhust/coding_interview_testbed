#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random

limit_min = 1
limit_max = 2048


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


def process_shuffle(raw):
    random.SystemRandom().shuffle(raw)
    return raw

def process_drop(raw):
    data = []
    for item in raw:
        if (random.SystemRandom().randint(1, 10) <= 7):
            data.append(item)
    random.shuffle(data)
    return data

def process_dropblock(raw):
    data = []
    count = 0
    for item in raw:
        if count > 0:
            count -= 1
        else:
            data.append(item)
            drop = random.SystemRandom().randint(1, 10) <= 2
            if drop:
                count = random.SystemRandom().randint(0, 6)
    random.shuffle(data)
    return data


if __name__ == '__main__':
    raw = range(limit_min, limit_max + 1)
    data = process_dropblock(raw)
    output_result(data)
