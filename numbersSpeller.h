//
// Created by ali-masa on 1/29/20.
//

#ifndef FIXEDPOINTPRICE_NUMBERSSPELLER_H
#define FIXEDPOINTPRICE_NUMBERSSPELLER_H

#include <string>
typedef unsigned long Spellable;
class NumbersSpeller{
public:
    static std::string spell(Spellable n);
    static std::string spellHundreds(unsigned n);
};

#endif //FIXEDPOINTPRICE_NUMBERSSPELLER_H
