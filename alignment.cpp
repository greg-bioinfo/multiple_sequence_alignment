#include <iostream>
#include <string>
#include "alignment.h"
#include <unordered_map>
#include <vector>
using namespace std;



int main(){
    string s1,s2,s3,s4,s5;
    int length1, length2;
    int i,j,del_penal,ins_penal;

    // toujours mettre un espace à la fin
    vector<string> vec {"E2 E8 E3 E5 ","E3 E5 E6 E8 ","E2 E2 E8 E3 E4 E5 E6 ","E2 E1 E8 E3 E4 E5 E7 ","E8 E3 E4 E5 E6 ","E1 E2 E3 E8","E2 E1 E5 E6 "};
    vector<vector<string>> vec_seq;    
    for(i=0;i<vec.size();i++){
        vec_seq.push_back(Extract_event(vec[i]));
    }

    del_penal=-2;
    ins_penal=-2;
    
    /*
    vector<string> v1,v2;
    
    vector<vector<vector<string>>> v3;
    for(int i=0;i<vec_seq.size();i++){
        vector<vector<string>> vec_temp;
        vec_temp.push_back(vec_seq[i]);
        v3.push_back(vec_temp);
    }
    cout<<v3.size()<<endl;
    for(i=0;i<vec_seq.size();i++){
        for(j=0;j<i;j++){
            int** M=Matrix_cost(vec_seq[i],vec_seq[j],del_penal,ins_penal);
            Display_alignment(M,vec_seq[i],vec_seq[j],del_penal,ins_penal);
            cout<<endl;
            cout<<"sequence: "<<i<<" / "<<j<<" score= "<<Score_alignment(vec_seq[i],vec_seq[j],del_penal,ins_penal)<<endl;
        }
    }

    int** M_d=Matrix_dissimm(v3,del_penal,ins_penal);
    for(i=0;i<v3.size();i++){
        for(j=0;j<i;j++){
            cout<<M_d[i][j]<<" ";
        }
    cout<<endl;
    }
    Coord c=Maximum_matrix(M_d,vec_seq.size());
    cout<<"Maximum: "<<M_d[c.x][c.y]<<" Sequences: "<<c.x+1<<" et "<<c.y+1<<endl;
*/
vector<vector<vector<string>>> v;

v=ACH(vec_seq,del_penal,ins_penal);
for(int i=0;i<v.size();i++){
    for(int j=0;j<v[i].size();j++){
        for(int y=0;y<v[i][j].size();y++){
            cout<<v[i][j][y];
        }
        cout<<endl;
    }
}
}

