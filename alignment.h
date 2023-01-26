#ifndef A_UNIQUE_HEADER_FILE_GUARD_NAME
#define A_UNIQUE_HEADER_FILE_GUARD_NAME

#include<string>
#include <unordered_map>
#include <vector>


struct Matrix{
    int n;
    int p;
    long** M;
};

Matrix ConstructionMatrice(int n, int p);

void delete_matrix(Matrix M,int n);

Matrix Matrix_cost(std::vector<std::string> s1, std::vector<std::string> s2,int del_penal, int ins_penal);

std::vector<std::string> Extract_event(std::string);

std::vector<std::vector<std::string>> fromfile_tovec (std::string path);

void reverse_vec(std::vector<std::string>& vec);

void Display_alignment(int** M,std::vector<std::string> s1,std::vector<std::string> s2,int del_penal,int ins_penal);

int Score_alignment(std::vector<std::string>& s1, std::vector<std::string>& s2, int del_penal, int ins_penal);

Matrix Matrix_dissimm(std::vector<std::vector<std::vector<std::string>>>& vec, int del_penal, int ins_penal);

Matrix Matrix_dissimm2(std::vector<std::vector<std::string>>& vec, int del_penal, int ins_penal);

struct Coord{
    int x;
    int y;
};

Coord Maximum_matrix(Matrix& M, int m);

Matrix Matrix_cost2(std::vector<std::vector<std::string>>& s1, std::vector<std::vector<std::string>>& s2, int del_penal, int ins_penal);

void Alignement_projection (std::vector<std::vector<std::string>>& classe1, std::vector<std::vector<std::string>>& classe2, Matrix M, int del_pena, int ins_penal);

void affichage(std::vector<std::vector<std::string>>& al);

float  difference(Matrix M1, Matrix M2, int length);

float score_alignement_multiple(std::vector<std::vector<std::string>>& al,int del_penal,int ins_penal);

std::vector<std::vector<std::string>> ACH(std::vector<std::vector<std::string>>& vec_seq,int del_penal,int ins_penal);

std::vector<std::vector<std::string>> Alignement_multiple(float seuil,std::string path,int del_penal, int ins_penal );

#endif
