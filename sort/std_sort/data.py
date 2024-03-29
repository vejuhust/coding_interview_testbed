#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random


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
    print ""


def rand_true(p):
    return random.SystemRandom().randint(1, 100) <= p

def rand_int(intmin, intmax):
    return random.SystemRandom().randint(intmin, intmax)


def process_shuffle(raw):
    random.SystemRandom().shuffle(raw)
    return raw

def process_drop(raw):
    data = []
    for item in raw:
        if (rand_true(70)):
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
            if rand_true(20):
                count = rand_int(0, 6)
    random.shuffle(data)
    return data

def process_repeat(raw):
    data = []
    for item in raw:
        if (rand_true(15)):
            count = rand_int(0, 3)
            while count > 0:
                data.append(item)
                count -= 1
        else:
            data.append(item)
    random.shuffle(data)
    return data
    
def process_amplify(raw):
    data = []
    for item in raw:
        if (rand_true(45)):
            item *= rand_int(-2, 8)
        data.append(item)
    random.shuffle(data)
    return data

def process_ascend(raw):
    return sorted(raw)

def process_descend(raw):
    return sorted(raw, reverse = True)


def process_mix1(raw):
    data = process_shuffle(raw)
    data = process_drop(data)
    data = process_dropblock(data)
    data = process_repeat(data)
    return data

def process_mix2(raw):
    data = process_shuffle(raw)
    data = process_drop(data)
    data = process_repeat(data)
    return data

def process_mix3(raw):
    data = process_shuffle(raw)
    data = process_dropblock(data)
    data = process_repeat(data)
    return data

def process_mix4(raw):
    data = process_shuffle(raw)
    data = process_drop(data)
    data = process_dropblock(data)
    return data


if __name__ == '__main__':
    limit_min = 1
    limit_max = 1024 * 2

    raw = range(limit_min, limit_max + 1)
    data = process_descend(raw)
    output_result(data)
