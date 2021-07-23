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

def remove_char_after_left_bracket(content_string):
    if '{' in content_string:
        content_string = content_string[:content_string.index('{')+1]
    return content_string

# void funcA() {  /* remove every between brackets. */  }
def remove_function_content(content_string):
    element = content_string.split("}")
    element = list(map(remove_char_after_left_bracket, element))
    return "}".join(element)

# class dataA {
#pragma polymorphic                      // keep
#    int member_varible;                 // keep
#    void member_function() { return; }  // remove it
#    void member_function();             // remove it
# };
def remove_member_function(content_string):
    content_string = remove_function_content(content_string)
    content_string = content_string.replace("public:","")
    content = content_string.replace("}", ";").split(";")
    content = [c for c in content if not '{' in c]
    content = [c for c in content if not 'virtual' in c]
    content = [c for c in content if not 'friend' in c]
    return ";\n".join(content)

with open(argv[3], 'w') as outfile:
    for defLoc in serializableDefLocList:
        outfile.write(strlines[defLoc[1]])
        outfile.write(strlines[defLoc[1]+1])
        class_content = "\n".join(strlines[defLoc[1]+2:defLoc[2]])
        outfile.write(remove_member_function(class_content))
        outfile.write(strlines[defLoc[2]])
