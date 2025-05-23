import re
import sys
import os

reg_value = []
reg_head = []

def write_reg_head(head):
    for i in head:
        f.write(i)
    f.write('#include <arduino.h>\n')

def assemble_c_array(arr_name, pos, size):
    f.write('\nword %s[%d] = {\n' % (arr_name, size))
    i = pos
    while i < pos + size :
        f.write(reg_value[i])
        f.write(',\n')
        i = i + 1
    f.write('};\n')
    return i

# check command line parameters, if none, quit program
if(len(sys.argv) < 2):
    print("Please give a exp file, ")
    print("for example: python exp2array.py config.exp")
    quit()

with open(sys.argv[1], 'r') as f:
    re_hd = re.compile(r'^;')
    re_reg = re.compile(r'^0x[0-9A-F]{2}  0x[0-9A-F]{2}$')
    for line in f.readlines():
        m = re_hd.match(line)
        if m :
            reg_head.append('//' + line)
            continue
        m = re_reg.match(line)
        if m :
            #reg_value.append(re.sub(r'  0x', '', m.group(0)))
            reg_value.append(m.group(0).replace('  0x', ''))
    f.close()

reg_file = os.path.join(os.path.dirname(os.path.abspath(sys.argv[1])),'cmt2300_regs.c')
with open(reg_file,'w') as f:
    write_reg_head(reg_head)
    pos = 0
    pos = assemble_c_array('CMTBank', pos,12)
    pos = assemble_c_array('SystemBank', pos, 12)
    pos = assemble_c_array('FrequencyBank', pos, 8)
    pos = assemble_c_array('DataRateBank', pos, 24)
    pos = assemble_c_array('BasebandBank', pos, 29)
    pos = assemble_c_array('TXBank', pos, 11)
    f.close()

print("%s had made!" % 'cmt2300_regs.c' )