#ifndef A_UNIQUE_HEADER_FILE_GUARD_NAME
#define A_UNIQUE_HEADER_FILE_GUARD_NAME

#include<string>
#include <unordered_map>
#include <vector>


int** ConstructionMatrice(int n, int p);

int** Matrix_cost(std::vector<std::string> s1, std::vector<std::string> s2,int del_penal, int ins_penal);

std::vector<std::string> Extract_event(std::string);

void reverse_vec(std::vector<std::string>& vec);

void Display_alignment(int** M,std::vector<std::string> s1,std::vector<std::string> s2,int del_penal,int ins_penal);

int Score_alignment(std::vector<std::string> s1, std::vector<std::string> s2, int del_penal, int ins_penal);

int** Matrix_dissimm(std::vector<std::vector<std::vector<std::string>>> vec, int del_penal, int ins_penal);

struct Coord{
    int x;
    int y;
};

Coord Maximum_matrix(int** M, int m);

int** Matrix_cost2(std::vector<std::vector<std::string>> s1, std::vector<std::vector<std::string>> s2, int del_penal, int ins_penal);

void Alignement_projection (std::vector<std::vector<std::string>>& classe1, std::vector<std::vector<std::string>>& classe2, int** M, int del_pena, int ins_penal);

std::vector<std::vector<std::vector<std::string>>> ACH(std::vector<std::vector<std::string>>vec_seq,int del_penal,int ins_penal);

#endif
