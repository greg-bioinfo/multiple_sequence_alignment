import subprocess
import sys
import os

file_param=sys.argv[1]
file_trace=sys.argv[2]
file_align=sys.argv[3]
file_score=sys.argv[4]

if not os.path.exists("./resultat"):
    os.makedirs("./resultat")
if os.path.isfile(file_param):
    #find the number of alignement and insertion/deleytion parameters
    with open(file_param,"r") as f:
        line=f.readlines()
        for l in line:
            if l[:18]=="<number_alignment>":
                number_al=l[18:-1]
            if l[:20]=="<penality_insertion>":
                penal_insert=l[20:-2]
            if l[:19]=="<penality_deletion>":
                penal_deletion=l[19:-2]
            if l[:15]=="<threshold_ACH>":
                seuil=l[15:-2]
            if l[:13]=="<match_score>":
                match_score=l[13:-2]
            if l[:16]=="<mismatch_score>":
                mismatch_score=l[16:]

    #Execute data_generation.cpp number_alignment times
    for i in range(int(number_al)):
        subprocess.check_call(["./data_generation.exe", file_param,"./resultat/"+str(i)+'_'+file_trace])
        subprocess.check_call(["./alignment.exe","./resultat/"+str(i)+'_'+file_trace,"./resultat/"+str(i)+'_'+file_align,"./resultat/"+file_score,penal_deletion,penal_insert,seuil,match_score,mismatch_score])
else:
    print("File not available")
