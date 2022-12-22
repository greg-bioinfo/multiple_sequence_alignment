#include<iostream>
#include "alignment.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int** ConstructionMatrice(int n, int p){
    int i;
    int** tab;
    tab=new int*[n];
    for(i=0;i<n;i++){
      tab[i]=new int[p];
    }
    return tab;
}

vector<string> Extract_event(string s1){
    vector<string> vec_event;
    string exp;
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

int** Matrix_cost(vector<string> s1, vector<string> s2, int del_penal, int ins_penal){

    int n,m,i,j,match_score;
    string E1,E2;

    n=s1.size();
    m=s2.size();

    int** M=ConstructionMatrice(n+1,m+1);
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
                match_score=1;
            }else{
                match_score=-1;
            }
            M[i][j]=max(max((M[i][j-1]+ins_penal),(M[i-1][j]+del_penal)),(M[i-1][j-1]+match_score));
        }

    } 
    return M;
}


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

void Display_alignment(int** M,vector<string> s1, vector<string> s2,int del_penal,int ins_penal){
    vector<string> al1,al2;
    int i,j;
    i=s1.size();
    j=s2.size();

    while((i!=0)&&(j!=0)){
        if (M[i][j]==M[i][j-1]+ins_penal){
            al1.push_back("__");
            al2.push_back(s2[j-1]);
            j--;
        }else if (M[i][j]==M[i-1][j]+del_penal){
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

int Score_alignment(vector<string> s1, vector<string> s2, int del_penal, int ins_penal){
    int n,m;
    int** M= Matrix_cost(s1,s2, del_penal, ins_penal);
    n=s1.size();
    m=s2.size();
    int score=M[n][m];
    return score;
}

/*
int** Matrix_dissimm(vector<vector<string>> vec, int del_penal, int ins_penal){
    int length=vec.size();
    int** M = ConstructionMatrice(length,length);

    for(int i=0;i<length;i++){
        for(int j=0;j<i;j++){
            M[i][j]=Score_alignment(vec[i],vec[j],del_penal,ins_penal);

        }
    }
    return M;
}
*/

Coord Maximum_matrix(int** M, int m){
    double max=-500000;
    Coord c;
    for(int i=0;i<m;i++){
        for(int j=0;j<i;j++){
            if(M[i][j]>max){
                max=M[i][j];
                c.x=i;
                c.y=j;
            }
        }
    }
    return c;
}

//Matrice de dissimilarité entre plusieurs classes composées de séquences
int** Matrix_dissimm(vector<vector<vector<string>>> vec, int del_penal, int ins_penal){
    int length=vec.size();
    int** M = ConstructionMatrice(length,length);

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
            M[i][i2]=score;
        }
    }
    return M;
}

//Matrice de coût pourl'alignement multiple entre deux classes
int** Matrix_cost2(vector<vector<string>> s1, vector<vector<string>> s2, int del_penal, int ins_penal){

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

    int** M=ConstructionMatrice(max_s1+1,max_s2+1);
    
    M[0][0]=0;
    //mettre une pénalité pour chaque séquence
    for(i=1;i<(max_s1+1);i++){
        //Initialiser la case de la matrice avant += Pour chaque séquence
        M[i][0]=0;
        for(int s=0;s<s1.size();s++){
            M[i][0]+=M[i-1][0]+del_penal;
        }
    }
    
    for(j=1;j<(max_s2+1);j++){
        M[0][j]=0;
        for(int s=0;s<s2.size();s++){
            M[0][j]+=M[0][j-1]+ins_penal;
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
                        match_score+=1;
                    }else{
                        match_score-=1;
            }
            M[i][j]=max(max((M[i][j-1]+score_ins),(M[i-1][j]+score_del)),(M[i-1][j-1]+match_score));
            }

            }
        } 
    }
    /*
    cout<<endl<<"Matrice de cout"<<endl;
    for(int i=0;i<max_s1+1;i++){
            for(int j=0;j<max_s2+1;j++){
                cout<<M[i][j]<<" ";
            }
            cout<<endl;
        }
    cout<<max_s1<<" / "<<max_s2<<endl;
    */
    return M;
}

//fonction qui crée l'alignement entre plusieurs alignements

void Alignement_projection (vector<vector<string>>& classe1, vector<vector<string>>& classe2, int** M, int del_penal, int ins_penal){
    
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
        if (M[i][j]==M[i][j-1]+ nb_pair * ins_penal){
            for(int r=0; r<classe1.size();r++){
                new_classe1[r].push_back("__");
            }
            for(int r2=0; r2<classe2.size();r2++){
                new_classe2[r2].push_back(classe2[r2][j-1]);
            } 
            j--;
        }else if (M[i][j]==M[i-1][j]+ nb_pair * del_penal){
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

vector<vector<vector<string>>> ACH(vector<vector<string>>vec_seq,int del_penal,int ins_penal){
    vector<vector<vector<string>>> tree;
    int** M_new;
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
        /*
         for(int i=0;i<tree.size();i++){
            for(int j=0;j<i;j++){
                cout<<M_new[i][j]<<" ";
            }
            cout<<endl;
        }
        */
        //Trouver les deux classes les plus proches
        Coord c=Maximum_matrix(M_new,tree.size());
        int** M_cost=Matrix_cost2(tree[c.x],tree[c.y],del_penal,ins_penal);
        Alignement_projection(tree[c.x],tree[c.y],M_cost,del_penal, ins_penal);
        vector<vector<vector<string>>>new_tree;

        //Pour les 2 classes les plus proches je crée une classe qui les regroupeet je les ajouter au nouvel arbre
        //vector<vector<string>> v;
        /* cout<<"************"<<endl;
        for(int i=0;i<tree[c.x].size();i++){
            //v.push_back(tree[c.x][i]);
            for(int e=0;e<tree[c.x][i].size();e++){
                cout<<tree[c.x][i][e];
            }
            cout<<endl;
        }
        for(int i=0;i<tree[c.y].size();i++){
            //v.push_back(tree[c.y][i]);
            for(int e=0;e<tree[c.y][i].size();e++){
               cout<<tree[c.y][i][e];
            }
            cout<<endl;
        }
        cout<<"************"<<endl;
        */
    
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
    return tree;
}