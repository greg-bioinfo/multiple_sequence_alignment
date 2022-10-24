#include "data.h"
#include <string>
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

bornes def_bornes(int index, string exp){
    string sub;
    sub=exp.substr(index,exp.length());
    string c,tr,num1,num2;
    bornes b;
    int j;
    for(j=0;j<sub.length();j++){
                c=sub[j];
                if (c==")"){
                    break;
                }
            }
    tr=sub.substr(0,j+1);
    int y;
    for (y=0;y<tr.length();y++){
        c=tr[y];
        if (c=="-"){
            num1=tr.substr(1,y-1);
            num2=tr.substr(y+1,tr.length()-1);
            break;
        }
    }
    int min = stoi(num1);
    int max = stoi(num2);
    b.min=min;
    b.max=max;
    b.end=j+index;
    return b;
}

ancre def_ancre(int index, string exp){
    int j,res;
    ancre anc;
    string sub,c;
    sub=exp.substr(index,exp.length());

    for (j=0;j<sub.length();j++){
        c=sub[j];
        if (c=="+"){
            res=1;
        }else if (c=="*"){
            res=2;
        }else if (c=="|"){
            res=3;
        }else if (c=="%"){
            res=4;
        }
        else if (c==">"){
            break;
        }
    }
    anc.start=index;
    anc.type=res;
    anc.end=j;
    return anc;
}

void expression_0(int min, int max){
    int x;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(min,max);
    int r=distr(gen);
    for(x=0;x<r;x++){
        cout<<" "<<"*"<<" ";
    }
}

void expression_1(int min, int max){
    int x;
    vector<int> evenement;
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distr(min,max);
    int r=distr(gen);

    uniform_int_distribution<> distr1(1,r-1);
    int i=distr1(gen);
    int n;
    for (n=0;n<i;n++){
        int indice=distr1(gen);
        evenement.push_back(indice);
    }
    
    for(x=0;x<r;x++){
        if (find(evenement.begin(), evenement.end(), x) == evenement.end()){
            cout<<" "<<"*"<<" ";
        }else{
            uniform_int_distribution<> distr2(0,50);
            int n2= distr2(gen);
            cout<<" "<<"Ea"<<n2<<" ";

        }   
    }
}


void expression_2(int min, int max){
    int x;
    vector<int> evenement;
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distr(min,max);
    int r=distr(gen);

    uniform_int_distribution<> distr1(0,r-1);
    int i=distr1(gen);
    int n;
    for (n=0;n<i;n++){
        int indice=distr1(gen);
        evenement.push_back(indice);
    }
    
    for(x=0;x<r;x++){
        if (find(evenement.begin(), evenement.end(), x) == evenement.end()){
            cout<<" "<<"*"<<" ";
        }else{
            uniform_int_distribution<> distr2(0,50);
            int n2= distr2(gen);
            cout<<" "<<"Ea"<<n2<<" ";

        }   
    }
}

void expression_3(int min,int max,ancre anc, string exp){
    string sub= exp.substr(anc.start,anc.end+1);
    string c,num;
    vector<string> vec_exp;
    int i,j;
    for (i=0;i<sub.length();i++){
        c=sub[i];
        if (c==")"){
            break;
        }
    }
    for (j=0;j<sub.length();j++){
        c=sub[j];
        if ((c=="|")||(c==">")){
            num=sub.substr(i+1,j-(i+1));
            vec_exp.push_back(num);
            i=j;

        }
    }
    int x;
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distr(min,max);
    int r=distr(gen);

    uniform_int_distribution<> distr1(0,r-1);
    int indice= distr1(gen);

    for(x=0;x<r;x++){
        if (x!=indice){
            cout<<" "<<"*"<<" ";
        }else{
            uniform_int_distribution<> distr2(0,vec_exp.size()-1);
            int n2= distr2(gen);
            cout<<" "<<vec_exp[n2]<<" ";
        }
    }


}
