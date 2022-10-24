#ifndef A_UNIQUE_HEADER_FILE_GUARD_NAME
#define A_UNIQUE_HEADER_FILE_GUARD_NAME
#include <string>

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

void expression_0(int min, int max);

void expression_1(int min, int max);

void expression_2(int min, int max);

void expression_3(int min,int max,ancre anc, std::string exp);


#endif