#ifndef A_UNIQUE_HEADER_FILE_GUARD_NAME
#define A_UNIQUE_HEADER_FILE_GUARD_NAME
#include <string>
#include <fstream>

struct parameters{
    int length_max;
    std::string expression;
    int nb_trace;
};

struct bornes{
    int min;
    int max;
    int end;
};

struct ancre{
    int type;
    int end;
    int start;
};

void search_parameters(parameters& res,std::string path);

bornes def_bounds(int index, std::string exp);

ancre def_anchor (int index, std::string exp);

void expression_0(int min, int max, std::string& trace, int length_max,std::ofstream& flux);

void expression_1(int min, int max, std::string& trace, int length_max,std::ofstream& flux);

void expression_2(int min, int max, std::string& trace, int length_trace,std::ofstream& flux);

void expression_3(int min,int max,ancre anc, std::string exp, std::string& trace, int length_max,std::ofstream& flux);

void expression_4(int min,int max,ancre anc, std::string exp, std::string& trace, int length_max,std::ofstream& flux);

void expression_5(int min,int max,ancre anc, std::string exp, std::string& trace, int length_max,std::ofstream& flux);

int length_trace(std::string trace);

#endif