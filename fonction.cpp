#include "data.h"
#include <string>
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>

using namespace std;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function search the parameters in a file and save them in a structure called parameters
void search_parameters(parameters& res,string path){
   
	ifstream file;
	char line[256];
	string exp,ex,l,nb;
	file.open(path,ios::in);

	while(file.getline(line,sizeof line)){
    	exp=line;
    	ex=exp.substr(0,12);
    	if(ex=="<expression>"){
        res.expression=exp.substr(12,exp.length()-11);
        continue;
    	};
     	nb=exp.substr(0,17);
    	if(nb=="<nombre_de_trace>"){
        res.nb_trace=stoi(exp.substr(17,exp.length()-17));
        continue;
    	};
      l=exp.substr(0,29);
    	if(l=="<longueur_maximum_des_traces>"){
        res.length_max=stoi(exp.substr(29,exp.length()-29));
        continue;
    	};
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this function calcul the nummber of evenment or point in a trace (separate by a white space)
int length_trace(string trace){
    int i,count=0;
    string c;
    for (i=0;i<trace.length();i++){
        c=trace[i];
        if (c==" "){
            count+=1;
        }
    }
    return count+1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This function extracts the minimum and maximum time between parentheses

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This function is used to determine the type of expression
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
        }else if (c==" "){
            res=5;
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void expression_0(int min, int max, string& trace, int length_max,ofstream& flux){
    int x;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(min,max);
    int r=distr(gen);
    for(x=0;x<r;x++){
        if (length_trace(trace)<length_max){
            flux<<"*"<<" ";
            trace+="* ";
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void expression_1(int min, int max, string& trace, int length_max,ofstream& flux){
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
            if (length_trace(trace)<length_max){
                flux<<"*"<<" ";
                trace+="* ";
            }
        }else{
            if (length_trace(trace)<length_max){
                uniform_int_distribution<> distr2(0,9);
                int n2= distr2(gen);
                flux<<"E"<<n2<<" ";
                trace=trace + "E "+ to_string(n2) + " ";
            }
        }   
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void expression_2(int min, int max, string& trace,int length_max,ofstream& flux){
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
        if (length_trace(trace)<length_max){
        if (find(evenement.begin(), evenement.end(), x) == evenement.end()){
            flux<<"*"<<" ";
            trace+="* ";
        }else{
            uniform_int_distribution<> distr2(0,9);
            int n2= distr2(gen);
            flux<<"E"<<n2<<" ";
            trace=trace + "E"+ to_string(n2) + " ";

        }   
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void expression_3(int min,int max,ancre anc, string exp, string& trace, int length_max,ofstream& flux){
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
            flux<<" "<<"*"<<" ";
        }else{
            uniform_int_distribution<> distr2(0,vec_exp.size()-1);
            int n2= distr2(gen);
            flux<<" "<<vec_exp[n2]<<" ";
        }
    }


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void expression_4(int min,int max,ancre anc, string exp, string& trace, int length_max,ofstream& flux){
    string sub= exp.substr(anc.start,anc.end+1);
    string c,num,prop;
    vector<string> vec_exp,vec_prop;
    int i,j,proba,p,somme=0;
    for (i=0;i<sub.length();i++){
        c=sub[i];
        if (c==")"){
            break;
        }
    }
    for (j=0;j<sub.length();j++){
        c=sub[j];
        if (c=="%"){
            num=sub.substr(i+1,j-(i+1));
            vec_exp.push_back(num);
            i=j;
        }else if ((c=="|")||(c==">")){
            prop=sub.substr(i+1,j-(i+1));
            vec_prop.push_back(prop);
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

    uniform_int_distribution<> distr3(0,100);
    int d= distr3(gen);

    for(x=0;x<r;x++){
        if (length_trace(trace)<length_max){
        if (x!=indice){
            flux<<"*"<<" ";
            trace+="* ";
        }else{
            for (p=0;p<vec_prop.size();p++){
                proba=stoi(vec_prop[p]);
                somme=somme+proba;
                if (d<=somme){
                    flux<<" "<<vec_exp[p]<<" ";
                    trace=trace + " "+ vec_exp[p] + " ";

                    break;
                }
            }
        }
        }
    }


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void expression_5(int min,int max,ancre anc, string exp, string& trace, int length_max,ofstream& flux){
    string sub= exp.substr(anc.start,anc.end+1);
    string c,num,ex,ch;
    bool x_times;
    vector<string> vec_exp;
    int i,j,x,nb,nb_times;
    // find ) where begin the expression
    for (i=0;i<sub.length();i++){
        c=sub[i];
        if (c==")"){
            break;
        }
    }
    i++;
    for (j=0;j<sub.length();j++){
        c=sub[j];
        if (c==" "){
            num=sub.substr(i,j-(i));
            x_times=false;
            for (x=0;x<num.length();x++){
                ch=num[x];
                if (ch=="X"){
                    x_times=true;
                    ex=num.substr(0,x);
                    nb_times= stoi(num.substr(x+1,num.length()-(x+1)));
                    for (int nb=0;nb<nb_times;nb++){
                        vec_exp.push_back(ex);
                    }        
                    i=j+1;
                    break;
                    continue;
                }
            }
            if (x_times==false){
            vec_exp.push_back(num);
            i=j+1;
            }
        }
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(min,max);
    int r=distr(gen);


    int dist=r;
    uniform_int_distribution<> distr2(0,1);

    bool evenment=true;
    for(x=0;x<r;x++){
        int choice=distr2(gen);
        if (length_trace(trace)<length_max){
        if (((choice==0)&&(dist>=vec_exp.size()))|| (evenment==false)){
            flux<<"*"<<" ";
            trace+="* ";
            dist-=1;
        }else{
            if (vec_exp.size()==1){
                evenment=false;
            }
            uniform_int_distribution<> distr1(0,vec_exp.size()-1);
            int index= distr1(gen);
            flux<<vec_exp[index]<<" ";
            trace=trace + vec_exp[index] + " ";
            dist-=1;
            if (vec_exp.size()>1){
                vec_exp.erase(vec_exp.begin()+index);
            }
        }
        }
    }


}
