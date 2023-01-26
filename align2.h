#ifndef A_UNIQUE_HEADER_FILE_GUARD_NAME
#define A_UNIQUE_HEADER_FILE_GUARD_NAME

#include<string>
#include <unordered_map>
#include <vector>

std::vector<std::vector<int>> Matrix_cost(std::vector<std::string>& s1, std::vector<std::string>& s2,int del_penal, int ins_penal,int match_score,int mismatch_score);

std::vector<std::string> Extract_event(std::string);

std::vector<std::vector<std::string>> fromfile_tovec (std::string path);

void reverse_vec(std::vector<std::string>& vec);

void Display_alignment(int** M,std::vector<std::string> s1,std::vector<std::string> s2,int del_penal,int ins_penal);

int Score_alignment(std::vector<std::string>& s1, std::vector<std::string>& s2, int del_penal, int ins_penal,int match_score,int mismatch_score);

std::vector<std::vector<int>> Matrix_dissimm(std::vector<std::vector<std::vector<std::string>>>& vec, int del_penal, int ins_penal,int match_score,int mismatch_score);

std::vector<std::vector<int>> Matrix_dissimm2(std::vector<std::vector<std::string>>& vec, int del_penal, int ins_penal,int match_score,int mismatch_score);

struct Coord{
    int x;
    int y;
};

Coord Maximum_matrix(std::vector<std::vector<int>>& M, int m);

std::vector<std::vector<int>> Matrix_cost2(std::vector<std::vector<std::string>>& s1, std::vector<std::vector<std::string>>& s2, int del_penal, int ins_penal,int match_score,int mismatch_score);

std::vector<std::vector<std::string>> Alignment_projection (std::vector<std::vector<std::string>>& classe1, std::vector<std::vector<std::string>>& classe2, std::vector<std::vector<int>> M, int del_pena, int ins_penal);

void Display(std::vector<std::vector<std::string>>& al);

void write_alignment(std::vector<std::vector<std::string>>& al,std::string path);

int Score_alignment_class(std::vector<std::vector<std::string>>& class1, std::vector<std::vector<std::string>>& class2, int del_penal,int ins_penal,int match_score,int mismatch_score);

void Update_M_dissim(std::vector<std::vector<int>>& M_dissim,std::vector<std::vector<std::string>>& new_classe,std::vector<std::vector<std::vector<std::string>>>& vec_seq, int index1, int index2, int del_penal, int ins_penal,int match_score,int mismatch_score);

float  difference(std::vector<std::vector<int>> M1, std::vector<std::vector<int>> M2, int length);

void initialization_matrix(std::vector<std::vector<int>>& M,int n, int m);

float score_alignment_multiple(std::vector<std::vector<std::string>>& al,int del_penal,int ins_penal,int match_score,int mismatch_score);

void ACH(std::vector<std::vector<std::string>>& vec_seq,int del_penal,int ins_penal,int match_score,int mismatch_score);

void Alignment_multiple(std::vector<std::vector<std::string>>& al,float seuil,std::string path,int del_penal, int ins_penal,int match_score,int mismatch_score);

int nb_event_per_column(std::vector<std::vector<std::string>>align);

void carac_csv (std::string path, std::vector<std::vector<std::string>>al, int del_penal, int ins_penal,int match_score,int mismatch_score,float time,std::string path_align);

#endif
