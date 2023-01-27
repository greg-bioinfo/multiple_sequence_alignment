#include<iostream>
#include "alignment.h"
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This function extracts the sequence into a vector without white space 
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
//This function extract the sequence from a file into a vector to use them during ACH

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
    }
    for(int i=0;i<vec.size();i++){
        vec_seq.push_back(Extract_event(vec[i]));
    }
    return vec_seq;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This function return a matrix with the score of each possible alignments from two sequences 
vector<vector<int>> Matrix_cost(vector<string>& s1, vector<string>& s2, int del_penal, int ins_penal,int match_score,int mismatch_score){

    int n,m,i,j,score;
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
                    score=6;
                }else{
                    score=match_score;
                } 
            }else{
                score=mismatch_score;
            }
            M[i][j]=max(max((M[i][j-1]+ins_penal),(M[i-1][j]+del_penal)),(M[i-1][j-1]+score));
        }

    } 
    return M;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function reverse a vector
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
// This function create the cost matrix and return the last case wich is the score of alignment
int Score_alignment(vector<string>& s1, vector<string>& s2, int del_penal, int ins_penal, int match_score, int mismatch_score){
    int n,m;
    vector<vector<int>> Mat= Matrix_cost(s1,s2, del_penal, ins_penal,match_score,mismatch_score);
    n=s1.size();
    m=s2.size();
    int score=Mat[n][m];
    return score;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This Function return the coordinate of a the max of a matrix
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
//Function wich returns a matrix with the alignment score of each class
vector<vector<int>> Matrix_dissimm(vector<vector<vector<string>>>& vec, int del_penal, int ins_penal,int match_score, int mismatch_score){
    int length=vec.size();
    vector<vector<int>> dissim(length, vector<int>(length, 0));

    for(int i=0;i<length;i++){
        for(int i2=0;i2<length;i2++){
            int score=0;
            int sum=0;
            //For each sequence of the first class
            for(int j=0;j<vec[i].size();j++){
                //For each sequence Of the 2nd
                for(int j2=0;j2<vec[i2].size();j2++){
                    //somme des scores
                    sum+=Score_alignment(vec[i][j],vec[i2][j2],del_penal,ins_penal,match_score,mismatch_score);
                }
            }
            //Mean of the score
            score=sum/(vec[i].size()*vec[i2].size());
            dissim[i][i2]=score;
        }
    }
    return dissim;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix of dissimilarity from vector<vector<string>> between several class
vector<vector<int>> Matrix_dissimm2(vector<vector<string>>& vec, int del_penal, int ins_penal,int match_score,int mismatch_score){
    int length=vec.size();
    vector<vector<int>> dissim(length, vector<int>(length, 0));

    //For each class
    for(int i=0;i<length;i++){
        //Compared with the others class
        for(int i2=0;i2<length;i2++){
            dissim[i][i2]=Score_alignment(vec[i],vec[i2],del_penal,ins_penal,match_score,mismatch_score);
        }
    }
    return dissim;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix of cost for the multiple alignment between two class
vector<vector<int>> Matrix_cost2(vector<vector<string>>& s1, vector<vector<string>>& s2, int del_penal, int ins_penal,int match_score, int mismatch_score){

    int n,m,i,j,max_s1=0,max_s2=0,score_ins=0,score_del=0,score_match=0;
    string E1,E2;

    //Find the longest sequence to know the size of the matrix

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
    //Deletion Penalty for each sequence from the first class
    for(i=1;i<(max_s1+1);i++){
        //Initialize the case
        Mat[i][0]=0;
        for(int s=0;s<s1.size();s++){
            Mat[i][0]+=Mat[i-1][0]+del_penal;
        }
    }
    
    //Insertion Penalty for each sequence from the second class
    for(j=1;j<(max_s2+1);j++){
        Mat[0][j]=0;
        for(int s=0;s<s2.size();s++){
            Mat[0][j]+=Mat[0][j-1]+ins_penal;
        }
    
        for(i=1;i<(max_s1+1);i++){
            //Calcul the cost of a substitution, or a deletion or an insertion for each sequence of the first class with the second
            score_match=0;
            score_del=0;
            score_ins=0;
            for(int e=0;e<s1.size();e++){
                for(int e2=0;e2<s2.size();e2++){
                    E1=s1[e][i-1];
                    E2=s2[e2][j-1];
                    score_ins+=ins_penal;
                    score_del+=del_penal;
                    if (E1==E2){
                        if(E1=="*"){
                            score_match+=6;
                        }else{
                            score_match+=match_score;
                        }
                    }else{
                        score_match+=mismatch_score;
            }
            Mat[i][j]=max(max((Mat[i][j-1]+score_ins),(Mat[i-1][j]+score_del)),(Mat[i-1][j-1]+score_match));
            }

            }
        } 
    }

    return Mat;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This function the alignment of several alignments (projection)

vector<vector<string>> Alignement_projection (vector<vector<string>>& class1, vector<vector<string>>& class2, vector<vector<int>> Mat, int del_penal, int ins_penal){
    
    int max1=0,max2=0,i,j;
    //Number of pair
    int nb_pair= class1.size() * class2.size();
    vector<vector<string>> new_class1,new_class2,result;


    //Initialize the two new class
    for(int i=0;i<class1.size();i++){
        vector<string> vec;
        new_class1.push_back(vec);
    }
    for(int i=0;i<class2.size();i++){
        vector<string> vec;
        new_class2.push_back(vec);
    }        
      //Find the size of the matrix
    for(int s=0;s<class1.size();s++){
        if(class1[s].size()>max1){
            max1=class1[s].size();
        }
    }
    for(int s=0;s<class2.size();s++){
        if(class2[s].size()>max2){
            max2=class2[s].size();
        }
    }
    i=max1;
    j=max2;

    while((i!=0)&&(j!=0)){
        
        if (Mat[i][j]==Mat[i][j-1]+ nb_pair * ins_penal){
            for(int r=0; r<class1.size();r++){
                new_class1[r].push_back("_");
            }
            for(int r2=0; r2<class2.size();r2++){
                new_class2[r2].push_back(class2[r2][j-1]);
            } 
            j--;
        }else if (Mat[i][j]==Mat[i-1][j]+ nb_pair * del_penal){
            for(int r=0; r<class1.size();r++){
                new_class1[r].push_back(class1[r][i-1]);
            }
            for(int r2=0; r2<class2.size();r2++){
                new_class2[r2].push_back("_");
            } 
            i--;
        }else{
            for(int r=0; r<class1.size();r++){
                new_class1[r].push_back(class1[r][i-1]);
            }
            for(int r2=0; r2<class2.size();r2++){
                new_class2[r2].push_back(class2[r2][j-1]);
            } 
            i--;
            j--;        
        }
    }
    while(i!=0){
        for(int r=0; r<class1.size();r++){
            new_class1[r].push_back(class1[r][i-1]);
        }
        for(int r2=0; r2<class2.size();r2++){
            new_class2[r2].push_back("_");
        } 
        i--;
    }
    while(j!=0){
        for(int r=0; r<class1.size();r++){
            new_class1[r].push_back("_");
        }
        for(int r2=0; r2<class2.size();r2++){
            new_class2[r2].push_back(class2[r2][j-1]);
        } 
        j--;
    }
    for(int i=0;i<class1.size();i++){
        reverse_vec(new_class1[i]);
    }
    for(int i=0;i<class2.size();i++){
        reverse_vec(new_class2[i]);
    }
    
    for(int i=0;i<new_class1.size();i++){
        result.push_back(new_class1[i]);
    }   
    for(int i=0;i<new_class2.size();i++){
        result.push_back(new_class2[i]);
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Score_alignment_class(vector<vector<string>>& class1, vector<vector<string>>& class2, int del_penal,int ins_penal,int match_score,int mismatch_score){
    vector<vector<int>> M_score= Matrix_cost2(class1,class2,del_penal,ins_penal,match_score,mismatch_score);
    //in a classe each sequence has the same size. find the last score in the matrix
    int n =class1[0].size();
    int m=class2[0].size();
    return M_score[n][m];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Update_M_dissim(vector<vector<int>>& M_dissim,vector<vector<string>>& new_class,vector<vector<vector<string>>>& vec_seq, int index1, int index2, int del_penal, int ins_penal,int match_score,int mismatch_score ){
     
     //score_alignment of the new classe with the others execept index1 and index2
     vector<int> score_new_class;
     for(int i=0;i<M_dissim.size();i++){
        if((i!=index1)&&(i!=index2)){
            score_new_class.push_back(Score_alignment_class(new_class,vec_seq[i],del_penal,ins_penal,match_score,mismatch_score));
        }
     }
     //delete the score for index1 and index2 (in the rows and columns)
     M_dissim.erase(M_dissim.begin() +index1);
     M_dissim.erase(M_dissim.begin()+index2);
    for(int i=0;i<M_dissim.size();i++){
        for(int j=0;j<M_dissim[i].size();j++){
                if((j==index1)||(j==index2)){
                    M_dissim[i].erase(M_dissim[i].begin()+j);
                }
        }
    }
    //add score with the new class in each row
    for(int i=0;i<score_new_class.size();i++){
        M_dissim[i].push_back(score_new_class[i]);
    }
    //add a row for the new class
    M_dissim.push_back(score_new_class);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// the vector of vector of vector of string has the role of a tree, and contains each class

void ACH(vector<vector<string>>&vec_seq,int del_penal,int ins_penal,int match_score,int mismatch_score){
    vector<vector<int>> M_cost;
    vector<vector<int>> M_dissim;
    vector<vector<vector<string>>> tree; 
    //put each sequence in a vector  (classe)
    for(int i=0; i<vec_seq.size();i++){
        vector<vector<string>> temp;
        temp.push_back(vec_seq[i]);
        tree.push_back(temp);
    }

    // matrix score alignment of each class
    M_dissim=Matrix_dissimm(tree,del_penal,ins_penal,match_score,mismatch_score);
    
    //tree contains every class: The goal is to group them into a single class
    while(tree.size()>1){

        //find the two closest class
        Coord c=Maximum_matrix(M_dissim,tree.size());
        M_cost=Matrix_cost2(tree[c.x],tree[c.y],del_penal,ins_penal,match_score,mismatch_score);
        
        vector<vector<string>> new_classe= Alignement_projection(tree[c.x],tree[c.y],M_cost,del_penal, ins_penal);
        
        //update matrix dissim with new  classes
        Update_M_dissim(M_dissim,new_classe,tree,c.x,c.y,del_penal,ins_penal,match_score,mismatch_score);
        
        // Delete the two classes from the tree that we want to combine
        tree.erase(tree.begin()+c.x);
        tree.erase(tree.begin()+c.y);
        
        //add new  class
        tree.push_back(new_classe);
    }
    //put the projections in a vector
    vec_seq.clear();
        
    for(int i=0;i<tree.size();i++){
        for(int j=0;j<tree[i].size();j++){
            vec_seq.push_back(tree[i][j]);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This function calculates the difference between two matrices
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
//Function that displays an alignment
void Display(vector<vector<string>>& al){
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
// Calculating a multiple alignment score
float score_alignment_multiple(vector<vector<string>>&al,int del_penal,int ins_penal,int match_score, int mismatch_score){
    float score=0;
    for(int i=0;i<al.size();i++){
        for(int j=i+1;j<al.size();j++){
            score+=Score_alignment(al[i],al[j],del_penal,ins_penal,match_score,mismatch_score);
        }
    }
    return score;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that writes an alignment to a file
void write_alignment(vector<vector<string>>& al,string path){
    ofstream flux(path);
    for(int i=0;i<al.size();i++){
        for(int j=0;j<al[i].size();j++){
            for(int y=0;y<al[i][j].size();y++){
                flux<<al[i][j][y]; 
            }
            flux<<string(3-al[i][j].size(),' ');
        }
        flux<<"\n";
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// initialization matrix with high values
void initialization_matrix(vector<vector<int>>& M,int n, int m){
    for(int i=0;i<n;i++){
        vector<int> temp(m,5000);
        M.push_back(temp);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Repeat ACH until convergence

void Alignment_multiple( vector<vector<string>>& al, float seuil,string path,int del_penal, int ins_penal, int match_score, int mismatch_score ){
    bool convergence= false;
    float d,d_prec=5000;
    al= fromfile_tovec(path);
    vector<vector<int>> M,M_prec;
    while(convergence==false){
        ACH(al,del_penal,ins_penal,match_score,mismatch_score);
        M = Matrix_dissimm2(al,del_penal, ins_penal,match_score,mismatch_score);
        if(M_prec.size()==0){
            initialization_matrix(M_prec,M.size(),M[0].size());
        }
        d=difference(M,M_prec,al.size());
        if((d<seuil)||(d>d_prec)){
            convergence=true;
        }
        else{
            M_prec=M;
            d_prec=d;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Counts the number of occurrences of an event appearing at least twice at the same position
int nb_event_per_column(vector<vector<string>>align){
    int score=0,count_element;
    vector<string> columns,already_check;
    //for each columns
    for(int i=0;i<align[0].size();i++){
        //compare each lines 
        for(int j=0;j<align.size();j++){
            columns.push_back(align[j][i]);
        }
        for(int y=0;y<columns.size();y++){
                if(columns[y]!="*"){
                //if the element not already counted in this column
                if(find(already_check.begin(),already_check.end(),columns[y])==already_check.end()){
                    count_element=count(columns.begin(),columns.end(),columns[y]);
                    //count only if the element appears twice
                    if(count_element>1){
                        score+=count_element;
                        already_check.push_back(columns[y]);
                    }
                }
                }
        }
    }
    return score;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function that writes all alignment scores in a single file
void carac_csv (string path, vector<vector<string>>al,int del_penal, int ins_penal,int match_score,int mismatch_score, float time,string path_align){

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
    ifstream ifile(path); 
    if(!ifile.is_open()){
        ofstream file(path,ios::app);
        file<<"file_alignment,"<<"score_NW,"<<"score_event,"<<"count_g,"<<"length,"<<"time"<<"\n";
    }
    ofstream file(path,ios::app);
    file<<path_align.substr(11,path_align.length())<<",";
    file<<score_alignment_multiple(al,del_penal,ins_penal,match_score,mismatch_score)<<",";
    file<<nb_event_per_column(al)<<",";
    file<<count_gap<<",";
    file<<length<<",";
    file<<time<<"\n";


}