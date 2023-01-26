#include <iostream>
#include <string>
#include "align2.h"
#include <vector>
#include <fstream>
#include<chrono>
#include <cstdlib>
using namespace std;



int main(int argc, char *argv[]){
    int i,j,del_penal,ins_penal,match_score,mismatch_score;

    //initialize each parameters
    string path=argv[1],path_align=argv[2];
    float seuil=atoi(argv[6]);
    del_penal=atoi(argv[4]);
    ins_penal=atoi(argv[5]);
    match_score=atoi(argv[7]);
    mismatch_score=atoi(argv[8]);

    vector<vector<string>> v;
    //Calcul the time of  execution
    auto start = chrono::high_resolution_clock::now();
    Alignment_multiple(v,seuil,path,del_penal,ins_penal,match_score,mismatch_score);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    float time_ex=duration.count()/1000;
    write_alignment(v,path_align);
    carac_csv (argv[3],v,del_penal,ins_penal,match_score,mismatch_score, time_ex,path_align);
}

