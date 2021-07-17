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

with open(argv[1]) as infile:
    serializable_list = [x.rstrip() for x in infile.readlines()]

with open(argv[2]) as infile:
    strlines = infile.readlines()

def lookClassTerminator(strlines, start_from):
    for index in range(start_from, len(strlines)):
        if '};' in strlines[index]:
            return index
    return None

serializableDefLocList = []

for index,strline in enumerate(strlines):
    if strline[:5]=='class':
        datatype = process_matched_strline(strline)
        if datatype in serializable_list:
            term = lookClassTerminator(strlines, index)
            if term:
                serializableDefLocList.append((datatype, index, term))

with open(argv[3], 'w') as outfile:
    for defLoc in serializableDefLocList:
        outfile.write("\n/*"+str(defLoc)+"*/\n")
        for strline in strlines[defLoc[1]:defLoc[2]+1]:
            outfile.write(strline)
