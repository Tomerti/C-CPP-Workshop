#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense{
public:
    Dense(const Matrix& weights, const Matrix& bias,
          ActivationFunction actfunc);
    const Matrix& get_weights() const;
    const Matrix& get_bias() const;
    ActivationFunction get_activation() const;
    Matrix operator()(const Matrix &m) const;


private:
    Matrix _weights;
    Matrix _bias;
    ActivationFunction _actfunc;
};


#endif //DENSE_H
