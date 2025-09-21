#include "Activation.h"
#include <cmath>

Matrix activation::relu(const Matrix &m){
    Matrix copy(m);
    for(int i=0; i<copy.get_rows() * copy.get_cols(); i++){
        if(copy[i] < 0){
            copy[i] = 0;
        }
    }
    return copy;
}

Matrix activation::softmax(const Matrix &m){
    Matrix copy(m);
    float sum = 0;
    for(int i=0; i<copy.get_rows() * copy.get_cols(); i++){
        copy[i] = std::exp(copy[i]);
        sum+=copy[i];
    }
    for(int i=0; i<copy.get_rows() * copy.get_cols(); i++){
        copy[i] = copy[i] / sum;
    }
    return copy;
}