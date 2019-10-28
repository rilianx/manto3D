//
// Created by Braulio Lobo on 24-10-19.
//

#include "Range.h"

bool Range::contiene(float num) {
    return num<=lSup && num>=lInf;
}

void Range::setLimit(float limit) {
    if(limit < lInf){
        lInf = limit;
    }
    else if(limit > lSup){
        lSup = limit;
    }
}

Range::Range() {
    this->lInf = 0;
    this->lSup = 0;
}

Range::Range(float lInf, float lSup) {
    this->lInf = lInf;
    this->lSup = lSup;
}

float Range::getLInf() const {
    return lInf;
}

float Range::getLSup() const {
    return lSup;
}
