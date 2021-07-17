#!/usr/bin/python3

from sys import argv

if len(argv)<2:
    exit()

def process_matched_strline(strline):
    #  input                                      output  
    # class gps                                -> gps
    # class bus_stop_detail: public bus_stop   -> bus_stop_detail
    if ':' in strline:
        strline = strline[:strline.index(':')]
    return strline[6:].rstrip()

def getUserDefinedType(filepath):
    with open(filepath) as infile:
        strlines = infile.readlines()
        matched = list(filter(lambda x: x[:6] == 'class ', strlines))
        return list(map(process_matched_strline, matched))
    return []

for filepath in argv[1:]:
    for udtype in getUserDefinedType(filepath):
        print(udtype)