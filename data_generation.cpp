#include <iostream>
# include <string>
#include "data.h"
#include <random>
#include <fstream>
using namespace std;


int main(int argc, char *argv[]){
    string path_param=argv[1];
    string path_trace=argv[2];

    //structure for parameters
    parameters res; 
    ofstream flux{path_trace};
    search_parameters(res,path_param);
    string exp=res.expression;
    int length_max=res.length_max;
    int nb_trace=res.nb_trace;
    int i,l,j,x,count,leng;
    string c;
    l=exp.length();
    //As long as the trace length does not exceed the maximum
    for(count=0;count<nb_trace;count++){
        string trace="";
        leng=length_trace(trace);
        for(i=0;i<exp.length();i++){
            c=exp[i];
            //no expression
            if ((c!="(")&(c!="<")&(leng<length_max)){
                flux<<c;
                trace+=c;
            } else if((c=="(")&(leng<length_max)){
                flux<<" ";
                trace+=" ";
                bornes b;
                b=def_bounds(i,exp);
                expression_0(b.min,b.max,trace,length_max,flux);
                i=b.end;
            } else if ((c=="<")&(leng<length_max)){
                flux<<" ";
                trace+=" ";
                bornes b;
                ancre anc;
                b=def_bounds(i+1,exp);
                anc=def_anchor(i,exp);
                if (anc.type==1){
                    expression_1(b.min,b.max,trace, length_max,flux);
                }else if (anc.type==2){
                    expression_2(b.min,b.max,trace, length_max,flux);
                }else if(anc.type==3){
                    expression_3(b.min,b.max,anc,exp,trace, length_max,flux);
                }else if(anc.type==4){
                    expression_4(b.min,b.max,anc,exp,trace, length_max,flux);
                }else if(anc.type==5){
                    expression_5(b.min,b.max,anc,exp,trace, length_max,flux);
                }
                i+=anc.end;
            }
        }
        flux<<endl;
    }
    

}

