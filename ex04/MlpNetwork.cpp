#include "MlpNetwork.h"
MlpNetwork::MlpNetwork(Matrix *weights, Matrix *biases){
    _weights = weights;
    _biases = biases;
    for(int i=0;i<MLP_SIZE;i++){
        _denses[i] = Dense(_weights[i],_biases[i],_actfuncs[i]);
    }
}

digit MlpNetwork::operator()(const Matrix &m) const{
    int target = 0;
    Matrix copy = Matrix(m);
    copy.vectorize();
    for(int i=0;i<MLP_SIZE;i++){
        copy=_denses[i](copy);
    }
    for(int i=1;i<TEN;i++){
        if(copy[i] > copy[target]){
            target = i;
        }
    }
    digit result = {(unsigned int)target, copy[target]};
    return result;
}