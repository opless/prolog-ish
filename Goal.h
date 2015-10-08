#include <iostream>
#include <string.h>

class Program;
class TermVarMapping;

class Goal {
private:
    TermCons *car;
    Goal *cdr;
public:
    Goal(TermCons *h, Goal *t) : car(h), cdr(t) {}
    Goal *copy() { return new Goal(car->copy2(),
                                   cdr==NULL ? NULL : cdr->copy()); }
    Goal *append(Goal *l) { return new Goal(car,
                                   cdr==NULL ? NULL : cdr->append(l)); }
    void print() { car->print();
                   if (cdr != NULL) { std::cout << "; ", cdr->print(); }
                 }
    void solve(Program *p, int level, TermVarMapping *map);
};
