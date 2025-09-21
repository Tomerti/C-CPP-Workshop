#include "Dense.h"
Dense::Dense(const Matrix &weights, const Matrix &bias,
             ActivationFunction actfunc):
_weights(weights), _bias(bias), _actfunc(actfunc)
{
}

const Matrix& Dense::get_weights() const{
    return _weights;
}

const Matrix& Dense::get_bias() const{
    return _bias;
}

ActivationFunction Dense::get_activation() const
{
    return _actfunc;
}

Matrix Dense::operator()(const Matrix &m) const{
    return _actfunc(_weights *m + _bias);
}