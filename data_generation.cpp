#include <iostream>
# include <string>
#include "data.h"
#include <random>
using namespace std;


int main(){

    string exp="Ea3<(2-5)E2|E3|E4>E5";
    int i,l,j,x,count;
    string c;
    l=exp.length();
    for(count=0;count<50;count++){
        for(i=0;i<exp.length();i++){
            c=exp[i];
            if ((c!="(")&(c!="<")){
                cout<<c;
            } else if(c=="("){
                bornes b;
                b=def_bornes(i,exp);
                expression_0(b.min,b.max);
                i=b.end;
            } else if (c=="<"){
                bornes b;
                ancre anc;
                b=def_bornes(i+1,exp);
                anc=def_ancre(i,exp);
                if (anc.type==1){
                    expression_1(b.min,b.max);
                }else if (anc.type==2){
                    expression_2(b.min,b.max);
                }else if(anc.type==3){
                    expression_3(b.min,b.max,anc,exp);
                }
                i+=anc.end;
            }
        }
        cout<<endl;
    }
    

}