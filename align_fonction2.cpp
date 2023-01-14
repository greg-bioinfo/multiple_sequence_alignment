#include<iostream>
#include "align2.h"
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fonction permettant d'extraire la séquence d'événements dans un vecteur sans les espaces
vector<string> Extract_event(string s1){
    vector<string> vec_event;
    string exp;
    s1+=" ";
    int i,j=0;
    for (i=0;i<s1.length();i++){
        exp=s1[i];
        if (exp==" "){
            vec_event.push_back(s1.substr(j,i-j));
            j=i+1;
        }
    }
    return vec_event;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction qui extrait les traces d'un fichieret les insérer dans un vecteurpour les utiliser dans la fonction ACH

vector<vector<string>> fromfile_tovec (string path){

    ifstream file;
    vector<string> vec;
    vector<vector<string>> vec_seq;
    string exp;
	char line[256];
	file.open(path,ios::in);
    while(file.getline(line,sizeof line)){
        exp=line;
        vec.push_back(exp.substr(0,exp.length()-1));
        cout<<exp.length()<<endl;
    }
    for(int i=0;i<vec.size();i++){
        vec_seq.push_back(Extract_event(vec[i]));
    }
    return vec_seq;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fonction qui renvoie une matrice type fil de fer à partir de 2 séquences d'événements
vector<vector<int>> Matrix_cost(vector<string>& s1, vector<string>& s2, int del_penal, int ins_penal){

    int n,m,i,j,match_score;
    string E1,E2;

    n=s1.size();
    m=s2.size();

    vector<vector<int>> M(n+1, vector<int>(m+1, 0));
    M[0][0]=0;
    for(i=1;i<(n+1);i++){
        M[i][0]=M[i-1][0]+del_penal;
    }
    
    for(j=1;j<(m+1);j++){
        M[0][j]=M[0][j-1]+ins_penal;
        for(i=1;i<(n+1);i++){
            E1=s1[i-1];
            E2=s2[j-1];
            if (E1==E2){
                if(E1=="*"){
                    match_score=0;
                }else{
                    match_score=5;
                } 
            }else{
                match_score=-1;
            }
            M[i][j]=max(max((M[i][j-1]+ins_penal),(M[i-1][j]+del_penal)),(M[i-1][j-1]+match_score));
        }

    } 
    return M;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fonction qui inversé un vecteur
void reverse_vec(vector<string>& vec){
    int n = vec.size();
    string temp;
    // Swap character starting from two
    // corners
    for (int i = 0; i < n / 2; i++){
        temp=vec[i];
        vec[i]=vec[n - i - 1];
        vec[n-i-1]=temp;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//fonction qui affiche l'alignement de 2 séquences à partir d'une matrice pas de cout
void Display_alignment(vector<vector<int>> Mat,vector<string>& s1, vector<string>& s2,int del_penal,int ins_penal){
    vector<string> al1,al2;
    int i,j;
    i=s1.size();
    j=s2.size();

    while((i!=0)&&(j!=0)){
        if (Mat[i][j]==Mat[i][j-1]+ins_penal){
            al1.push_back("__");
            al2.push_back(s2[j-1]);
            j--;
        }else if (Mat[i][j]==Mat[i-1][j]+del_penal){
            al1.push_back(s1[i-1]);
            al2.push_back("__");
            i--;
        }else{
            al1.push_back(s1[i-1]);
            al2.push_back(s2[j-1]);
            i--;
            j--;        }
    }
    while(i!=0){
        al1.push_back(s1[i-1]);
        al2.push_back("__");
        i--;
    }
    while(j!=0){
        al1.push_back("__");
        al2.push_back(s2[j-1]);
        j--;
    }

    reverse_vec(al1);
    reverse_vec(al2);

    for(int i=0;i<al1.size();i++){
        cout<<al1[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<al2.size();i++){
        cout<<al2[i]<<" ";
    }
    cout<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fonction qui renvoie le score d'alignement de 2 séquences d'événements en prenant la case
int Score_alignment(vector<string>& s1, vector<string>& s2, int del_penal, int ins_penal){
    int n,m;
    vector<vector<int>> Mat= Matrix_cost(s1,s2, del_penal, ins_penal);
    n=s1.size();
    m=s2.size();
    int score=Mat[n][m];
    return score;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fonction pour trouver les 2 classes ayant le score maximum dans une matrice de dissimilarité
Coord Maximum_matrix(vector<vector<int>>& Mat, int m){
    double max=-500000000;
    Coord c;
    for(int i=0;i<m;i++){
        for(int j=0;j<i;j++){
            if(Mat[i][j]>max){
                max=Mat[i][j];
                c.x=i;
                c.y=j;
            }
        }
    }
    return c;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrice de dissimilarité entre plusieurs classes composées de séquences
vector<vector<int>> Matrix_dissimm(vector<vector<vector<string>>>& vec, int del_penal, int ins_penal){
    int length=vec.size();
    vector<vector<int>> dissim(length, vector<int>(length, 0));

    //Pour chaque classe
    for(int i=0;i<length;i++){
        //Comparer avec les autres classes
        for(int i2=0;i2<length;i2++){
            int score=0;
            int somme=0;
            //Pour chaque sequence de la première classe
            for(int j=0;j<vec[i].size();j++){
                //Pour chaque sequence de la deuxième
                for(int j2=0;j2<vec[i2].size();j2++){
                    //somme des scores
                    somme+=Score_alignment(vec[i][j],vec[i2][j2],del_penal,ins_penal);
                }
            }
            //moyenne des scores
            score=somme/(vec[i].size()*vec[i2].size());
            dissim[i][i2]=score;
        }
    }
    return dissim;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrice de dissimilarité à partir de vector<vector<string>> entre plusieurs classes composées de séquences
vector<vector<int>> Matrix_dissimm2(vector<vector<string>>& vec, int del_penal, int ins_penal){
    int length=vec.size();
    vector<vector<int>> dissim(length, vector<int>(length, 0));

    //Pour chaque classe
    for(int i=0;i<length;i++){
        //Comparer avec les autres classes
        for(int i2=0;i2<length;i2++){
            dissim[i][i2]=Score_alignment(vec[i],vec[i2],del_penal,ins_penal);
        }
    }
    return dissim;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrice de coût pourl'alignement multiple entre deux classes
vector<vector<int>> Matrix_cost2(vector<vector<string>>& s1, vector<vector<string>>& s2, int del_penal, int ins_penal){

    int n,m,i,j,match_score,max_s1=0,max_s2=0,score_ins=0,score_del=0,score_match=0;
    string E1,E2;

    //trouver la séquence la plus longue pour la taille de lamatrice

    for(int s=0;s<s1.size();s++){
        if(s1[s].size()>max_s1){
            max_s1=s1[s].size();
        }
    }
    for(int s=0;s<s2.size();s++){
        if(s2[s].size()>max_s2){
            max_s2=s2[s].size();
        }
    }

    vector<vector<int>> Mat(max_s1+1, vector<int>(max_s2+1, 0));
    
    Mat[0][0]=0;
    //mettre une pénalité de deletion pour chaque séquence de la classe 1 
    for(i=1;i<(max_s1+1);i++){
        //Initialiser la case de la matrice avant += Pour chaque séquence
        Mat[i][0]=0;
        for(int s=0;s<s1.size();s++){
            Mat[i][0]+=Mat[i-1][0]+del_penal;
        }
    }
    
    //mettre une pénalité d'insertion pour chaque séquence de la classe 2
    for(j=1;j<(max_s2+1);j++){
        Mat[0][j]=0;
        for(int s=0;s<s2.size();s++){
            Mat[0][j]+=Mat[0][j-1]+ins_penal;
        }
    
        for(i=1;i<(max_s1+1);i++){
            //On calcule le coût d'une substitution d'une insertion ou d'une délétionpour chaque séquence de la première classe avec la 2nde classe
            match_score=0;
            score_del=0;
            score_ins=0;
            //Pour chaque séquencede de s1
            for(int e=0;e<s1.size();e++){
                //Pour chaque séquencede de s2
                for(int e2=0;e2<s2.size();e2++){
                    E1=s1[e][i-1];
                    E2=s2[e2][j-1];
                    score_ins+=ins_penal;
                    score_del+=del_penal;
                    if (E1==E2){
                        if(E1=="*"){
                            match_score+=0;
                        }else{
                            match_score+=5;
                        }
                    }else{
                        match_score+=-1;
            }
            Mat[i][j]=max(max((Mat[i][j-1]+score_ins),(Mat[i-1][j]+score_del)),(Mat[i-1][j-1]+match_score));
            }

            }
        } 
    }

    return Mat;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//fonction qui crée l'alignement entre plusieurs alignements

void Alignement_projection (vector<vector<string>>& classe1, vector<vector<string>>& classe2, vector<vector<int>> Mat, int del_penal, int ins_penal){
    
    int max1=0,max2=0,i,j;
    //Nombre de paires lorsque l'oncalcule le coût d'une substitution insertion deletion 
    int nb_pair= classe1.size() * classe2.size();
    vector<vector<string>> new_classe1,new_classe2;

    //Initialiserles 2 nouvelles classes avec le bon nombreDe séquence
    for(int i=0;i<classe1.size();i++){
        vector<string> vec;
        new_classe1.push_back(vec);
    }
    for(int i=0;i<classe2.size();i++){
        vector<string> vec;
        new_classe2.push_back(vec);
    }        
      //trouver la séquence la plus longue pour la taille de lamatrice
    for(int s=0;s<classe1.size();s++){
        if(classe1[s].size()>max1){
            max1=classe1[s].size();
        }
    }
    for(int s=0;s<classe2.size();s++){
        if(classe2[s].size()>max2){
            max2=classe2[s].size();
        }
    }
    i=max1;
    j=max2;

    while((i!=0)&&(j!=0)){
        // il faut changer les sequences de la classe 1
        if (Mat[i][j]==Mat[i][j-1]+ nb_pair * ins_penal){
            for(int r=0; r<classe1.size();r++){
                new_classe1[r].push_back("__");
            }
            for(int r2=0; r2<classe2.size();r2++){
                new_classe2[r2].push_back(classe2[r2][j-1]);
            } 
            j--;
        }else if (Mat[i][j]==Mat[i-1][j]+ nb_pair * del_penal){
            for(int r=0; r<classe1.size();r++){
                new_classe1[r].push_back(classe1[r][i-1]);
            }
            for(int r2=0; r2<classe2.size();r2++){
                new_classe2[r2].push_back("__");
            } 
            i--;
        }else{
            for(int r=0; r<classe1.size();r++){
                new_classe1[r].push_back(classe1[r][i-1]);
            }
            for(int r2=0; r2<classe2.size();r2++){
                new_classe2[r2].push_back(classe2[r2][j-1]);
            } 
            i--;
            j--;        
        }
    }
    while(i!=0){
        for(int r=0; r<classe1.size();r++){
            new_classe1[r].push_back(classe1[r][i-1]);
        }
        for(int r2=0; r2<classe2.size();r2++){
            new_classe2[r2].push_back("__");
        } 
        i--;
    }
    while(j!=0){
        for(int r=0; r<classe1.size();r++){
            new_classe1[r].push_back("__");
        }
        for(int r2=0; r2<classe2.size();r2++){
            new_classe2[r2].push_back(classe2[r2][j-1]);
        } 
        j--;
    }
    for(int i=0;i<classe1.size();i++){
        reverse_vec(new_classe1[i]);
    }
    for(int i=0;i<classe2.size();i++){
        reverse_vec(new_classe2[i]);
    }
    
    classe1=new_classe1;
    classe2=new_classe2;
}

//Pour stocker les séquences que j'ai regroupéesj'utilise un vecteur de vecteur qui contientles groupes de séquence
//vec={{"VGOUY","GYTRE","AQSDF"},{"HKMMM","SDVN"}}

//Objectif de l'ACH: À partir d'une matrice de dissimilarité regrouper les séquences Et ressortir un arbre sous forme de vecteur de vecteur
//vec_seq={{"E1","E2","E3"},{"E2","E6","E5"}}  
//tree={  {{"E1","E2","E3"},{"E2","E6","E5"}} ,  {{"E2","E4","E6"},{"E7","E2","E5"}} }

vector<vector<string>> ACH(vector<vector<string>>&vec_seq,int del_penal,int ins_penal){
    vector<vector<int>> M_new;
    vector<vector<int>> M_cost;
    vector<vector<vector<string>>> tree;
    vector<vector<string>> resultat;
    //Je crée un arbreoù chaque séquence constitué une classe à elle seule
    //Une classe est un vecteur contenant des vecteurs de string

    for(int i=0;i<vec_seq.size();i++){
        vector<vector<string>> vec_temp;
        vec_temp.push_back(vec_seq[i]);
        tree.push_back(vec_temp);
    }

    //tree contient les classes: le but est de regrouper tout dans une classe 
    while(tree.size()>1){
        M_new=Matrix_dissimm(tree,del_penal,ins_penal);

        //Trouver les deux classes les plus proches
        Coord c=Maximum_matrix(M_new,tree.size());
        M_cost=Matrix_cost2(tree[c.x],tree[c.y],del_penal,ins_penal);
        Alignement_projection(tree[c.x],tree[c.y],M_cost,del_penal, ins_penal);
        vector<vector<vector<string>>>new_tree;
    
        //Ajouter les classes qui n'ont pas changé dans le nouvel arbre
        vector<vector<string>> v;
        for(int i=0;i<tree.size();i++){
            if(i==c.x){
               for(int i=0;i<tree[c.x].size();i++){
                    v.push_back(tree[c.x][i]);
                    for(int e=0;e<tree[c.x][i].size();e++){
                        //cout<<tree[c.x][i][e];
                    }
                //cout<<endl;
                }
            }
            else if(i==c.y){
                for(int i=0;i<tree[c.y].size();i++){
                    v.push_back(tree[c.y][i]);
                    for(int e=0;e<tree[c.y][i].size();e++){
                        //cout<<tree[c.y][i][e];
                    }
                //cout<<endl;
                }
            }

            else{
                new_tree.push_back(tree[i]);
            }
            //cout<<endl;
        }
        new_tree.push_back(v);
        //Le nouvel arbre devient l'arbre principal
        tree=new_tree;
    }
    for(int i=0;i<tree.size();i++){
        for(int j=0;j<tree[i].size();j++){
            resultat.push_back(tree[i][j]);
        }
    }
    cout<<"Score: "<<score_alignement_multiple(resultat,del_penal,ins_penal)<<endl;
    return resultat;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Fonction calculant la différence entre 2 matrices de dissimilarité
float  difference(vector<vector<int>> M1, vector<vector<int>> M2, int length){
    float d;
    for(int i=0; i<length;i++){
        for(int j=0; j<i;j++){
            d=d+pow((M1[i][j]-M2[i][j]),2);
        }
    }
    d=d/(2*length*(length-1));
    d=pow(d,0.5);
    return d;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Fonction qui affiche un allignement
void affichage(vector<vector<string>>& al){
    for(int i=0;i<al.size();i++){
        for(int j=0;j<al[i].size();j++){
            for(int y=0;y<al[i][j].size();y++){
                cout<<al[i][j][y];
            }
        }
        cout<<endl;
    }
    cout<<endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// calcul du score d'un alignement multiple
float score_alignement_multiple(vector<vector<string>>&al,int del_penal,int ins_penal){
    float score=0;
    for(int i=0;i<al.size();i++){
        for(int j=i+1;j<al.size();j++){
            score+=Score_alignment(al[i],al[j],del_penal,ins_penal);
        }
    }
    return score;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Répétition de l' ACH jusqu'à une convergence

double Alignement_multiple(vector<vector<string>>& al, float seuil,string path,int del_penal, int ins_penal  ){
    bool convergence= false;
    float d,d_prec=5000;
    clock_t time1,time2;
    float time3;
    time1=clock();
    vector<vector<string>> v= fromfile_tovec(path);
    cout<<"Score: "<<score_alignement_multiple(v,del_penal,ins_penal)<<endl;
    affichage(v);
    vector<vector<int>> M_prec = Matrix_dissimm2(v,del_penal, ins_penal); 
    al=ACH(v,del_penal,ins_penal);
    affichage(al);
    vector<vector<int>> M = Matrix_dissimm2(al,del_penal, ins_penal); 
    while(convergence==false){
        d=difference(M,M_prec,v.size());
        cout<<"difference: "<<d<<endl;
        if((d<seuil)||(d>d_prec)){
            convergence=true;
        }
        else{
            al=ACH(al,del_penal,ins_penal);
            affichage(al);
            M_prec=M;
            M = Matrix_dissimm2(al,del_penal, ins_penal); 
            d_prec=d;
        }
    }
    time2=clock();
    time3= ( clock() - time1 ) / (double) CLOCKS_PER_SEC;
    return  time3;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fonction  qui calcule des caractéristiques et enregistre dans un fichier csv
void carac_csv (string path, vector<vector<string>>al,int del_penal, int ins_penal, float time){
    ofstream file(path);
    int count_gap=0,count_match=0,length;
    length=al[0].size();
    for(int i=0;i<al.size();i++){
        for(int j=0;j<al[i].size();j++){
            for(int y=0;y<al[i][j].size();y++){
                    if(al[i][j][y]=='_'){
                        count_gap+=1;
                    }
                }
            }
        }
    file<<"score;"<<"count_g;"<<"length;"<<"time;"<<"\n";
    file<<score_alignement_multiple(al,del_penal,ins_penal)<<";";
    file<<count_gap<<";";
    file<<length<<";";
    file<<time<<";";

}