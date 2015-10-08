/* prolog.c: a simple Prolog interpreter written in C++,                */
/*           including an example test run as main().                   */
/* Copyright (c) Alan Mycroft, University of Cambridge, 2000.           */

#include "Atom.h"
#include "Clause.h"
#include "Goal.h"
#include "Program.h"
#include "Term.h"
#include "TermCons.h"
#include "TermVar.h"
#include "TermVarMapping.h"
#include "Trail.h"


int main(int argc, char *argv[])
{
/* A sample test program: append */

Atom *at_app = new Atom("app");
Atom *at_cons = new Atom("cons");
TermCons *f_nil = new TermCons(new Atom("nil"));
TermCons *f_1 = new TermCons(new Atom("1"));
TermCons *f_2 = new TermCons(new Atom("2"));
TermCons *f_3 = new TermCons(new Atom("3"));

Term *v_x = new TermVar();
TermCons *lhs1 = new TermCons(at_app, f_nil, v_x, v_x);
Clause *c1 = new Clause(lhs1, NULL);

Term *v_l = new TermVar();
Term *v_m = new TermVar();
Term *v_n = new TermVar();
TermCons *rhs2 = new TermCons(at_app, v_l, v_m, v_n);
TermCons *lhs2 = new TermCons(at_app, new TermCons(at_cons, v_x, v_l),
                                      v_m,
                                      new TermCons(at_cons, v_x, v_n));
Clause *c2 = new Clause(lhs2, new Goal(rhs2,NULL));

TermVar *v_i = new TermVar();
TermVar *v_j = new TermVar();
TermCons *rhs3 = new TermCons(at_app, v_i, v_j, 
                      new TermCons(at_cons, f_1,
                      new TermCons(at_cons, f_2,
                      new TermCons(at_cons, f_3, f_nil))));

Goal *g1 = new Goal(rhs3, NULL);

Program *test_p = new Program(c1, new Program(c2, NULL));
Program *test_p2 = new Program(c2, new Program(c1, NULL));

TermVar *varvar[] = {v_i, v_j};
std::string varname[] =  {"I", "J"};
TermVarMapping *var_name_map = new TermVarMapping(varvar, varname, 2);

for(int i=0;i< 10; i++)
{
   std::cout << "\n\nRound " << i << "\n";
   std::cout << "=======Append with normal clause order:\n";
   g1->solve(test_p, 0, var_name_map);
   std::cout << "\n=======Append with reversed normal clause order:\n";
   g1->solve(test_p2, 0, var_name_map);
}
std::cout << "\n\nDONE\n";
std::cout << "test_p\n";
delete test_p;
std::cout << "test_p2\n";
delete test_p2;
   return 0;
}
