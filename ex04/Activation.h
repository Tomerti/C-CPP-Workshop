#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"


typedef Matrix (*ActivationFunction) (const Matrix& m);

namespace activation{
    Matrix relu(const Matrix& m);
    Matrix softmax(const Matrix& m);
}


#endif //ACTIVATION_H