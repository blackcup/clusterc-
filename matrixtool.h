#ifndef MATRIXTOOL_H_INCLUDED
#define MATRIXTOOL_H_INCLUDED
#include<stdio.h>
#include <iostream>
#include <Eigen/Dense>
#include<algorithm>
#include<vector>
#include "TezhenValue.h"
using namespace std;
using namespace Eigen;


int sayHello()
{
    MatrixXd covMat(MatrixXd input);
    MatrixXd getEigenvalue(MatrixXd covMat);
    printf("Hello World\n");
    MatrixXd input(2,3);
    input(0,0) = 1.0;
    input(0,1) = 2.0;
    input(0,2) = 6.0;
    input(1,0) = 2.0;
    input(1,1) = 4.0;
    input(1,2) = 3.0;
    MatrixXd covMatatrix = covMat(input);
    getEigenvalue(covMatatrix);
    return 0;
}
MatrixXd covMat(MatrixXd input)
{
    MatrixXd meanVec = input.colwise().mean();
    cout << "meanVec.rows" << endl << meanVec.rows()<< endl;
    int cols = meanVec.cols();
    cout << "meanVec.size()" << endl << meanVec.size()<< endl;
    MatrixXd zeroMeanMat = input;
    RowVectorXd meanVecRow(RowVectorXd::Map(meanVec.data(),cols));
    zeroMeanMat.rowwise() -= meanVecRow;
    MatrixXd covMat = (zeroMeanMat.adjoint()*zeroMeanMat)/double(input.rows()-1);
    cout << "covMat" << endl << covMat<< endl;
    return covMat;
}

bool SortByValue( const TezhenValue &v1, const TezhenValue &v2)
{
    return v1.value > v2.value;
}
void PrintVector( vector<TezhenValue> vec)
{
    int length = vec.size();
    for(int i = 0;i<length;i++)
    {
        TezhenValue t = vec.at(i);
        cout<< "value:" << t.value << "\t index:" << t.index << endl;
    }
}
MatrixXd getEigenvalue(MatrixXd covMat,int n)
{
    EigenSolver<MatrixXd> es(covMat);
    int rows = covMat.rows();
    vector<TezhenValue> vec;
    for(int i = 0 ;i<rows; i++)
    {
        complex<double> row = es.eigenvalues()[i];
        double value = row.real();
        TezhenValue t;
        t.value = value ;
        t.index = i ;
        vec.push_back(t);
    }
    std::sort(vec.begin(),vec.end(),SortByValue);
    for(int i =0;i<n;i++)
    {
        TezhenValue t = vec.at(i);
        VectorXcd v = es.eigenvectors().col(t.index);
    }
    return covMat;
}

#endif // MATRIXTOOL_H_INCLUDED
