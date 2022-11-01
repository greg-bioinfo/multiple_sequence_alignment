#include <iostream>
# include <string>
#include "data.h"
#include <random>
#include <fstream>
using namespace std;

std::ofstream flux{"trace.txt"};

int main(int argc, char** argv){


    string exp=argv[1];//E1<(6-8)E2%45|E1%55>E8";
    int i,l,j,x,count,leng;
    int length_max=25;
    string c;
    l=exp.length();
    for(count=0;count<50;count++){
        string trace="";
        leng=length_trace(trace);
        for(i=0;i<exp.length();i++){
            c=exp[i];
            if ((c!="(")&(c!="<")&(leng<length_max)){
                flux<<c;
                trace+=c;
            } else if((c=="(")&(leng<length_max)){
                flux<<" ";
                trace+=" ";
                bornes b;
                b=def_bornes(i,exp);
                expression_0(b.min,b.max,trace,length_max);
                i=b.end;
            } else if ((c=="<")&(leng<length_max)){
                flux<<" ";
                trace+=" ";
                bornes b;
                ancre anc;
                b=def_bornes(i+1,exp);
                anc=def_ancre(i,exp);
                if (anc.type==1){
                    expression_1(b.min,b.max,trace, length_max);
                }else if (anc.type==2){
                    expression_2(b.min,b.max,trace, length_max);
                }else if(anc.type==3){
                    expression_3(b.min,b.max,anc,exp,trace, length_max);
                }else if(anc.type==4){
                    expression_4(b.min,b.max,anc,exp,trace, length_max);
                }else if(anc.type==5){
                    expression_5(b.min,b.max,anc,exp,trace, length_max);
                }
                i+=anc.end;
            }
        }
        flux<<endl;
    }
    

}

