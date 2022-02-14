#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;

//fullyconnected takes as inputs the names of the txt files(x,y,z) to take input from
//and the name of the output file(w) to print output into
void fullyconnected(string x,string y,string z,string w){
    ifstream xx(x); // xx denotes the input stream of inputmatrix
    ifstream yy(y); // yy denotes the input stream of weightmatrix
    ifstream zz(z); // zz denotes the input stream of biasmatrix
    ofstream ww(w); // ww denotes the output stream for output matrix
    int b;
    xx>>b; // b denotes the number of columns of input matrix
    int a;
    xx>>a; //a denotes the number of rows of input matrix
    float inputMatrix[a][b]; //inputMatrix contains the inputmatrix in the 2d array form
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < a; j++)
        {
            float val;
            xx>>val;
            inputMatrix[j][i] = val;
        }    
    }
    int c; // c denotes the number of columns of weight matrix
    yy>>c;
    int temp;
    yy>>temp;
    if(temp!=b){
        ww<<"The product is undefined as Matrix sizes are not compatible.";
        return;
    } //Checking if the number of rows of weight matrix is equal to number of columns of input matrix
    float weightMatrix[b][c]; //weightMatrix contains the weight matrix in 2d array form
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < b; j++)
        {
            float val;
            yy>>val;
            weightMatrix[j][i] = val;
        }
    }
    zz>>temp;
    if(temp!=c){
        ww<<"The addition of bias matrix is not possible as number of columns do not match.";
        return;
    }//Checking that number of columns of bias matrix is equal to c
    zz>>temp;
    if(temp!=a){
        ww<<"The addition of bias matrix is not possible as number of rows do not match.";
        return;
    } //Checking that number of rows of bias matrix is equal to a
    float biasMatrix[a][c]; //biasMatrix contains the bias matrix in 2d array form
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < a; j++)
        {
            float val;
            zz>>val;
            biasMatrix[j][i] = val;
        }
    }
    float outputMatrix[a][c]; //This contains our evaluated matrix in 2d array form
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < c; j++)
        {
            outputMatrix[i][j] = 0;
            for (int k = 0;k<b; k++)
            {
                outputMatrix[i][j] += inputMatrix[i][k]*weightMatrix[k][j]; 
            }
            
        }
    }
    for(int i = 0; i < a; ++i){
        for (int j = 0; j < c; ++j){
            outputMatrix[i][j] += biasMatrix[i][j];
        }
    }
    ww<<c;
    ww<<'\n';
    ww<<a;
    ww<<'\n';
    for(int i = 0; i < c; ++i){
        for(int j = 0; j < a; ++j){
            ww<<outputMatrix[j][i];
            ww<<'\n';
        }
    } //Printing answer to ww
    ww.close();
}

//relu takes the name of input and output files as inputs
void relu(string x, string y){
    ifstream xx(x); //xx is the input stream for the input file
    ofstream yy(y); //yy is the output stream for the output file
    int a; //a denotes the number of columns of input matrix
    xx>>a;
    yy<<a; //printing a to outputfile
    yy<<'\n';
    int b; //b denotes the number of rows of input matrix
    xx>>b;
    yy<<b; //printing b to outputfile
    yy<<'\n';
    float temp;
    for(int i = 0; i < a*b ; ++i){
        xx>>temp;//taking input from inputfile
        if(temp<0){
            temp = 0;
        }
        yy<<temp; //printing the relu of the input to outputfile
        yy<<'\n';
    }
    yy.close();
}

//tanh takes in the names of input and output files as input
void tanh(string x, string y){
    ifstream xx(x); //xx denotes the input stream for the input file
    ofstream yy(y); //yy denotes the output stream for the output file
    int a; //a denotes the number of columns of the inputmatrix
    xx>>a;
    yy<<a; //printing a to output
    yy<<'\n';
    int b; // b denotes the number of number of columns of inputmatrix
    xx>>b;
    yy<<b; //printing b to output
    yy<<'\n';
    float temp;
    for(int i = 0; i < a*b; ++i){
        xx>>temp; //taking input from inputfile
        temp *= 2;
        float temptemp = exp(temp);
        float temptemptemp = temptemp - 1;
        float temptemptemptemp = temptemp + 1;
        float ans = temptemptemp/temptemptemptemp;
        yy<<ans; //printing the tanh to outputfile
        yy<<'\n';
    }
    yy.close();
}

//maxpooling takes the input name, stride and output name as inputs in string format
void maxpooling(string x, string y, string z){
    ifstream xx(x); //xx denotes the input stream for the input file
    int stride = stoi(y); //stride denotes the integer format for string y
    ofstream zz(z); //zz denotes the output stream for the output file
    int b;
    xx>>b; //b denotes the number of columns of the matrix
    int a;
    xx>>a; //a denotes the number of rows of the matrix
    if(b%stride!=0){
        zz<<"Column must be a multiple of stride.";
        return;
    }
    if(a%stride != 0){
        zz<<"Row must be a multiple of stride.";
        return;
    }
    float matrix[a][b];
    for(int i = 0; i < b; ++i){
        for(int j = 0; j < a; ++j){
            float temp;
            xx>>temp;
            matrix[j][i] = temp;
        }
    }
    int ansrow = a/stride;
    int anscolumn = b/stride;
    float ansarr[ansrow][anscolumn]; //contains the answer matrix in 2d array form
    int k = 0;
    while(k<a){
        int l = 0;
        while(l < b){
            float mx = matrix[k][l];
            for(int i = k; i < k + stride; ++i){
                for(int j = l; j < l + stride; ++j){
                    mx = max(mx,matrix[i][j]);
                }
            }
            int p = k/stride;
            int q = l/stride;
            ansarr[p][q] = mx;
            l += stride;
        }
        k += stride;
    }
    zz<<anscolumn;
    zz<<'\n';
    zz<<ansrow;
    zz<<'\n';
    for(int i = 0; i < anscolumn; ++i){
        for(int j = 0; j < ansrow; ++j){
            float temp = ansarr[j][i];
            zz<<temp;
            zz<<'\n';
        }
    }
    zz.close();



}

void averagepooling(string x, string y, string z){
    ifstream xx(x); // xx denotes the input stream for the input file
    int stride = stoi(y); //stride denotes the stride value in integer data type
    ofstream zz(z); //zz denotes the output streamd for the output file
    int b; //b denotes the number of columns
    xx>>b;
    int a; //a denotes the number of rows
    xx>>a;
    if(b%stride!=0){
        zz<<"Column must be a multiple of stride.";
        return;
    }
    if(a%stride != 0){
        zz<<"Row must be a multiple of stride.";
        return;
    }
    float matrix[a][b]; //matrix contains the input matrix in 2d array fromat
    for(int i = 0; i < b; ++i){
        for(int j = 0; j < a; ++j){
            float temp;
            xx>>temp;
            matrix[j][i] = temp;
        }
    }
    int ansrow = a/stride;
    int anscolumn = b/stride;
    float dv = stride*stride;
    float ansarr[ansrow][anscolumn]; //ansarr contains the asnwer matrix in 2d array format
    int k = 0;
    while(k<a){
        int l = 0;
        while(l < b){
            float sm = 0;
            for(int i = k; i < k + stride; ++i){
                for(int j = l; j < l + stride; ++j){
                    sm += matrix[i][j];
                }
            }
            int p = k/stride;
            int q = l/stride;
            ansarr[p][q] = sm/dv;
            l += stride;
        }
        k += stride;
    }
    zz<<anscolumn;
    zz<<'\n';
    zz<<ansrow;
    zz<<'\n';
    for(int i = 0; i < anscolumn; ++i){
        for(int j = 0; j < ansrow; ++j){
            float temp = ansarr[j][i];
            zz<<temp;
            zz<<'\n';
        }
    }
    zz.close();

}

void softmax(string x,string y){
    ifstream xx(x);
    ofstream yy(y);
    int length;
    xx>>length;
    yy<<length;
    yy<<'\n';
    float arr[length];
    float sm = 0;
    for(int i = 0; i < length; ++i){
        float temp;
        xx>>temp;
        temp = exp(temp);
        arr[i] = temp;
        sm += temp;
    }
    for(int i = 0; i < length; ++i){
        float temp = arr[i]/sm;
        yy<<temp;
        yy<<'\n';
    }
    yy.close();

}

void sigmoid(string x, string y){
    ifstream xx(x);
    ofstream yy(y);
    int length;
    xx>>length;
    yy<<length;
    yy<<'\n';
    float temp;
    float temptemp;
    for(int i = 0; i < length; ++i){
        xx>>temp;
        temp = exp(temp);
        temptemp = temp + 1;
        float temptemptemp = temp/temptemp;
        yy<<temptemptemp;
        yy<<'\n';

    }
}

int main(int argc,char *argv[]){
    if(strcmp(argv[0],"./yourcode.out")==0){
    if(strcmp(argv[1],"fullyconnected")==0){
        if(argc!=6){
            ofstream err("error.txt");
            err<<"Wrong terminal command: Number of parameters don't match.";
            return 0;
        }
        string x = argv[2];
        string y = argv[3];
        string z = argv[4];
        string w = argv[5];
        fullyconnected(x,y,z,w);
        } else if(strcmp(argv[1],"activation")==0){
            if(argc!=5){
                    ofstream err("error.txt");
                    err<<"Wrong terminal command: Number of parameters don't match.";
                    return 0;
                }
            if(strcmp(argv[2],"relu")==0){
                string x = argv[3];
                string y = argv[4];
                relu(x,y);
            }else if(strcmp(argv[2],"tanh")==0){
                string x = argv[3];
                string y = argv[4];
                tanh(x,y);
            }else{
                ofstream err("error.txt");
                err<<"Wrong terminal command: Only relu and tanh are implemented in activation functions.";
                return 0;
            }
        } else if(strcmp(argv[1],"pooling")==0){
            if(argc!=6){
                    ofstream err("error.txt");
                    err<<"Wrong terminal command: Number of parameters don't match.";
                    return 0;
                }
            if(strcmp(argv[2],"max")==0){
                string x = argv[3];
                string y = argv[4];
                string z = argv[5];
                maxpooling(x,y,z);
            } else if(strcmp(argv[2],"average")==0){
                string x = argv[3];
                string y = argv[4];
                string z = argv[5];
                averagepooling(x,y,z);
            } else{
                ofstream err("error.txt");
                err<<"Wrong terminal command: Only max and average pooling are implemented.";
                return 0;
            }
        } else if(strcmp(argv[1],"probability")==0){
            if(argc!=5){
                    ofstream err("error.txt");
                    err<<"Wrong terminal command: Number of parameters don't match.";
                    return 0;
            }
            if(strcmp(argv[2],"softmax")==0){
                string x = argv[3];
                string y = argv[4];
                softmax(x,y);
            } else if(strcmp(argv[2],"sigmoid")==0){
                string x = argv[3];
                string y = argv[4];
                sigmoid(x,y);
            } else{
                ofstream err("error.txt");
                err<<"Wrong terminal command: Only softmax and sigmoid probability functions implemented.";
                return 0;
            } 
        } else{
                ofstream err("error.txt");
                err<<"Wrong terminal command: Function called is not implemented here.";
                return 0;
            }
    }else{
        ofstream err("error.txt");
        err<<"The out file must be named and called as yourcode.";
    }
    return 0;
}