#include <iostream>
#include <string>
#include "align2.h"
#include <vector>
#include <fstream>
#include<chrono>
#include <cstdlib>
using namespace std;



int main(int argc, char *argv[]){
    int i,j,del_penal,ins_penal;
    string path=argv[1];
    float seuil=10;
    ofstream outFile (argv[2]);


    del_penal=atoi(argv[4]);
    ins_penal=atoi(argv[5]);

    vector<vector<string>> v;
    auto start = chrono::high_resolution_clock::now();
    double time=Alignement_multiple(v,seuil,path,-4,-4);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    float time_ex=duration.count();
    cout<<duration.count()<<endl;
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[i].size();j++){
            for(int y=0;y<v[i][j].size();y++){
                outFile<<v[i][j][y];
            }
            outFile<<string(5-v[i][j].size(),' ');
        }
        outFile<<"\n";
    }
carac_csv (argv[3],v,del_penal,ins_penal,time_ex);

}

