import subprocess
import sys

file_param=sys.argv[1]
file_trace=sys.argv[2]
file_align=sys.argv[3]
file_score=sys.argv[4]

#find the number of alignement and insertion/deleytion parameters
with open(file_param,"r") as f:
    line=f.readlines()
    for l in line:
        if l[:18]=="<number_alignment>":
            number_al=l[18:]
            print(number_al)
        if l[:20]=="<penality_insertion>":
            penal_insert=l[20:]
        if l[:19]=="<penality_deletion>":
            penal_deletion=l[19:]
        
#Execute data_generation.cpp number_alignment times
for i in range(int(number_al)):
    subprocess.check_call(["./data_generation.exe", file_param,"./resultat/"+str(i)+file_trace])
    subprocess.check_call(["./alignment.exe","./resultat/"+str(i)+file_trace,"./resultat/"+str(i)+file_align,"./resultat/"+str(i)+file_score,penal_deletion,penal_insert])
