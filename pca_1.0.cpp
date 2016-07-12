#include<stdio.h>
#include<iostream>
#include<math.h>
#include<Eigen/Eigen>
#define rows 9
#define columns 4
using namespace Eigen;
using namespace std;

float calc_cov (int a, int b,float array_minusmean[rows][columns]) {
float product=0.00000;
float product_sum=0.00000;

for (int i=0;i<rows;i++){
    product=array_minusmean[i][a]*array_minusmean[i][b];
    product_sum+=product;
    product=0;
}
float covariance= product_sum/(rows-1);
return covariance;
}

int main(){
 float input_matrix[rows][columns],sum=0,avg=0,mean_diff=0,mean_diff_sq=0,mean_diff_sq_sum=0;
 float mean[columns]={0.00000};
 float std_dev[columns]={0.00000};
 float std_data[rows][columns];
 float cov_mat_std[columns][columns];
 float std_data_mean[columns]={0.00000};
 float std_data_minusmean[rows][columns];
 float input_matrix_minusmean[rows][columns];
 float cov_mat_input[columns][columns];

 // input matrix data
 for (int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
        cin>>input_matrix[i][j];
    }
 }

 // input data arithimetic mean

 for (int j=0;j<columns;j++){
        for (int i=0;i<rows;i++){
            sum=sum+input_matrix[i][j];
        }
    avg=sum/rows;
    mean[j]=avg;
    sum=0;

 }

 // std dev of input data

  for (int j=0;j<columns;j++){
        for (int i=0;i<rows;i++){
         mean_diff=input_matrix[i][j]-mean[j];
         mean_diff_sq= pow(mean_diff,2);
         mean_diff_sq_sum+=mean_diff_sq;
        }
       std_dev[j]=sqrt(mean_diff_sq_sum/(rows-1));
       mean_diff_sq_sum=0;
 }

// standardize the data

for (int j=0;j<columns;j++){
        for (int i=0;i<rows;i++){
         mean_diff=input_matrix[i][j]-mean[j];
         std_data[i][j]=mean_diff/std_dev[j];
         }

}

// mean of std data


for (int j=0;j<columns;j++){
        for (int i=0;i<rows;i++){
            sum=sum+std_data[i][j];
        }
    avg=sum/rows;
    std_data_mean[j]=avg;
    sum=0;

 }


// std data minus mean from each observation
for (int j=0;j<columns;j++){
    for(int i=0;i<rows;i++){
        std_data_minusmean[i][j]=std_data[i][j]-std_data_mean[j];
    }
}

// input data minus mean from each obs

for (int j=0;j<columns;j++){
    for(int i=0;i<rows;i++){
        input_matrix_minusmean[i][j]=input_matrix[i][j]-mean[j];
    }
}


// covariance of std data

for (int i=0;i<columns;i++){
    for (int j=0;j<columns;j++){

        cov_mat_std[i][j]=calc_cov(i,j,std_data_minusmean);
    }
}

// covariance of input data
for (int i=0;i<columns;i++){
    for (int j=0;j<columns;j++){

        cov_mat_input[i][j]=calc_cov(i,j,input_matrix_minusmean);
    }
}

typedef float myptr[columns][columns];
myptr*ptr_inputcov;
myptr*ptr_stdcov;
ptr_inputcov=&cov_mat_input;// pointer to 2d array of cov_mat_input
ptr_stdcov=&cov_mat_std;//pointer to 2d array of cov_mat_std

MatrixXf eigen_inputcov(columns,columns);
memcpy(eigen_inputcov.data(),ptr_inputcov, sizeof(float)*columns*columns);

MatrixXf eigen_stdcov(columns,columns);
memcpy(eigen_stdcov.data(),ptr_stdcov, sizeof(float)*columns*columns);

EigenSolver<MatrixXf> es(eigen_stdcov);
MatrixXcf eigenvectors_std =es.eigenvectors();
VectorXcf eigenvalues_std = es.eigenvalues();


EigenSolver<MatrixXf> es1(eigen_inputcov);
MatrixXcf eigenvectors_input =es1.eigenvectors();
VectorXcf eigenvalues_input = es1.eigenvalues();


cout<<eigenvectors_std;
cout<<endl<<"========================================================================================================================================================="<<endl;
cout<<eigenvalues_std<<endl<<endl;



/*for (int i=0;i<rows;i++){
    for (int j=0;j<columns;j++){
        cout<<std_data[i][j];
    }
    cout<<endl;
}
*/

    return 0;
}
