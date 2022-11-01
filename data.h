#ifndef A_UNIQUE_HEADER_FILE_GUARD_NAME
#define A_UNIQUE_HEADER_FILE_GUARD_NAME
#include <string>
#include <fstream>


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

bornes def_bornes(int index, std::string exp);

ancre def_ancre (int index, std::string exp);

void expression_0(int min, int max, std::string& trace, int length_max);

void expression_1(int min, int max, std::string& trace, int length_max);

void expression_2(int min, int max, std::string& trace, int length_trace);

void expression_3(int min,int max,ancre anc, std::string exp, std::string& trace, int length_max);

void expression_4(int min,int max,ancre anc, std::string exp, std::string& trace, int length_max);

void expression_5(int min,int max,ancre anc, std::string exp, std::string& trace, int length_max);

int length_trace(std::string trace);

#endif