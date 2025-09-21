//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

class MlpNetwork{
public:
    MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]);
    digit operator()(const Matrix &m) const;
private:
    Matrix* _weights;
    Matrix* _biases;
    Dense _denses[MLP_SIZE] = {Dense(Matrix(), Matrix(), nullptr),
                               Dense(Matrix(), Matrix(), nullptr),
                               Dense(Matrix(), Matrix(), nullptr),
                               Dense(Matrix(), Matrix(), nullptr)};
    const ActivationFunction _actfuncs[MLP_SIZE] = {activation::relu,
                                                    activation::relu,
                                                    activation::relu,
                                                    activation::softmax};
};

#endif // MLPNETWORK_H