#!/usr/bin/python3

from sys import argv

if len(argv)<2:
    exit()

def getUserDefinedType(filepath):
    with open(filepath) as infile:
        strlines = infile.readlines()
        matched = list(filter(lambda x: x[:6] == 'class ', strlines))
        return list(map(lambda x: x[6:].rstrip(), matched))
    return []

for filepath in argv[1:]:
    for udtype in getUserDefinedType(filepath):
        print(udtype)