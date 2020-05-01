//
// Created by Braulio Lobo on 14-04-20.
//

#include "IndexIterator.h"

IndexIterator::IndexIterator(int index, int limitTop) {
    this->index = index;
    this->limitTop = limitTop;
    this->limitBottom = 0;
}

IndexIterator::IndexIterator(int index, int limitTop, int limitBottom) {
    this->index = index;
    this->limitTop = limitTop;
    this->limitBottom = limitBottom;
}

void IndexIterator::next(){
    index++;
    if(index > limitTop){
        index = limitBottom;
    }
}

void IndexIterator::back(){
    index--;
    if(index < limitBottom){
        index = limitTop;
    }
}

int IndexIterator::get(){
    return index;
}