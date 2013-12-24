#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
//#define K 3
//#define pi 3.1415926

const int K = 3;
const float pi = 3.1415926;

int mycount = 0;
int midcount = 0;

using namespace std;

//********************************* Count_Lines **********************************//
int Count_Lines(char*filename)
{
    int n=0;
    std::ifstream ReadFile;
    //char line[512];
    std::string temp;
    ReadFile.open(filename);
    if(ReadFile.fail())
    {
        return 0;
    }
    else
    {
        while(getline(ReadFile,temp))
        {
            n++;
        }
        return n;
    }
    ReadFile.close();
}

//********************************* Input_points ***********************************//
long double** Input_points(char *filename,int frame_n)
{
    ifstream readFile;
    readFile.open(filename);
    long double **point0 = new long double *[frame_n];

    for (int i =0; i<frame_n;i++)
    {
        point0[i]=new long double [2];
        for (int j=0; j<2; j++)
        {
            readFile >> point0[i][j];
        }

    }
    readFile.close();
    return point0;
}

//********************************* Inverse_matrix ***********************************//
//按第一行展开计算|A|
long double getA(long double** arcs,int n)
{
    long double ans = 0;  //ans = |A|
    long double** temp = new long double* [2];
    for (int i =0;i<2;i++)
    {
        temp[i] = new long double [2];
    }

    if(n==1)
    {
        return arcs[0][0];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1;j++)
        {  
            for(int k=0;k<n-1;k++)  
            {  
                temp[j][k] = arcs[j+1][(k>=i)?k+1:k];  
            }  
        }  
        long double t = getA(temp,n-1);  //递归调用
        if(i%2==0)  
        {  
            ans += arcs[0][i]*t;  
        }  
        else  
        {  
            ans -=  arcs[0][i]*t;  
        }  
    }  
    return ans;  
}

//计算每一行每一列的每个元素所对应的余子式，组成A*  
void getAStart(long double** arcs,int n,long double** ans)
{  
    if(n==1)  
    {  
        ans[0][0] = 1;  
        return;  
    }   

    long double** temp = new long double* [2];
    for (int i =0;i<2;i++)
    {
        temp[i] = new long double [2];
    }
    for(int i=0;i<n;i++)  
    {  
        for(int j=0;j<n;j++)  
        {  
            for(int k=0;k<n-1;k++)  
            {  
                for(int t=0;t<n-1;t++)  
                {  
                    temp[k][t] = arcs[k>=i?k+1:k][t>=j?t+1:t];  
                }  
            }  

            ans[j][i]  =  getA(temp,n-1);  
            if((i+j)%2 == 1)  
            {  
                ans[j][i] = - ans[j][i];  
            }  
        }  
    }  
}

long double** Inverse_matrix(long double** initial)
{
    //原始矩阵
    long double** arcs = new long double* [2];
    for (int i=0;i<2;i++)
    {  arcs[i] = new long double [2];
        for (int j=0;j<2;j++)
        {
            arcs[i][j] = initial[i][j];
        }
    }
    //伴随矩阵
    long double** astar = new long double* [2];
    for (int i=0;i<2;i++)
    { 
        astar[i] = new long double [2]; 
    }
    int n = 2;  
    long double a = getA(initial,n);  
    if(a==0)  
    {  
        printf("can not transform!\n");  
    }  
    else  
    {  
        getAStart(arcs,n,astar);   
    }  
    //  printf("\n");  
    long double** inverse = new long double* [2];
    for (int i=0;i<2;i++)
    {  inverse[i] = new long double [2];
        for (int j=0;j<2;j++)
        {
            inverse[i][j] = astar[i][j]/a;
        }
    }
    return  (inverse);
}

//********************************* Gauss_Function ***********************************//
//标准正态分布在原点的概率密度就是0.4左右.
long double Gauss_Function(long double* x, long double* u, long double** v)
{
    long double** inverse = Inverse_matrix(v);  //逆矩阵没问题
    long double rr=(x[0]-u[0])*(x[0]-u[0])*inverse[0][0] +(x[0]-u[0])*(x[1]-u[1])*(inverse[1][0]+inverse[0][1]) + (x[1]-u[1])*(x[1]-u[1])*inverse[1][1];
    long double ee = exp((-0.5)*(rr));
    long double gg = (1/(2*pi*sqrt(v[0][0]*v[1][1]-v[0][1]*v[1][0])))*ee;
    return gg;
}

//********************************* Gauss_Mixture_Model ***********************************//

long double Gauss_Mixture_Model (long double** point, int points_number)
{
    int NUMBER = points_number;
    long double coefficient[3] = {0.2,0.2,0.3};
    long double u[3][2] = {{300,250},{400,250},{350,350}};
    long double*** var = new long double** [3];   //var[][][]
    for (int i =0;i<3;i++)
    {
        var[i] = new long double* [2];
        for (int j = 0;j<2;j++)
        {
            var[i][j] = new long double [2];
        }
    }

    var[0][0][0] = 100;
    var[0][0][1] = 0;
    var[0][1][0] = 0;
    var[0][1][1] = 100;

    var[1][0][0] = 100;
    var[1][0][1] = 0;
    var[1][1][0] = 0;
    var[1][1][1] = 100;

    var[2][0][0] = 100;
    var[2][0][1] = 0;
    var[2][1][0] = 0;
    var[2][1][1] = 100;

    long double  **responsible = new long double  *[points_number];
    for (int i =0; i<NUMBER;i++)
    { 
        responsible[i]=new long double [K];
        for (int j=0; j<K; j++)
        {
            responsible[i][j] = 0;
        }
    }
    long double whole_probability = 0;
    long double N_k[K] = {0,0,0};

    //E-STEP//
    for(int nn=0;nn<10;nn++)
    {
        for (int i =0;i<NUMBER;i++)
        {
            for (int j=0;j<K;j++)
            {
                whole_probability = whole_probability + coefficient[j]*Gauss_Function(point[i],u[j],var[j]);

                if(Gauss_Function(point[i],u[j],var[j]) < 0.000001 ||  Gauss_Function(point[i],u[j],var[j]) > 100000)
                      mycount ++;
//              cout << Gauss_Function(point[i],u[j],var[j]) << endl;
                midcount ++;
            }
            //cout << whole_probability << endl;
            for (int j=0;j<K;j++)
            {
                responsible[i][j] = coefficient[j]*Gauss_Function(point[i],u[j],var[j])/whole_probability;
                if (responsible[i][j] <= 0.25)
                {
                    responsible[i][j] = 0;
                }
                //cout << responsible[i][j] << endl;
            }

            whole_probability = 0;
        }

        long double sum = 0; // 正确的话 sum(r_nk) = NUMBER  E-STEP没问题
        for (int i = 0;i<NUMBER;i++)
        {
            for (int j = 0;j<K;j++)
            {
                //sum = sum + responsible[i][j];  //cout << "sum(r_nk) = " << sum << endl;
            }
        }
        cout << "sum(r_nk) = " << sum << endl;

        //M-STEP//
        for (int i=0;i<3;i++)    //待估系数清零
        {
            coefficient[i] = 0;
            N_k[i] = 0;
            for (int j=0;j<2;j++)
            {
                u[i][j] = 0;
                for (int k=0;k<2;k++)
                {
                    var[i][j][k] = 0;
                }
            }
        }
        //var[3][2][2] = {{20,0,0,20},{40,0,0,40},{80,0,0,80}};

        for (int i=0;i<K;i++)
        {
            for (int j=0;j<NUMBER;j++)
            {
                N_k[i] = N_k[i]+responsible[j][i];
            }
            //cout << "N_k[" << i << "] = " << N_k[i] << endl;
        }

        for (int i=0;i<K;i++)
        {
            for (int j =0;j<NUMBER;j++)
            {
                u[i][0] = u[i][0]+(1/N_k[i])*(responsible[j][i]*point[j][0]);
                u[i][1] = u[i][1]+(1/N_k[i])*(responsible[j][i]*point[j][1]);
            }
        }
        for (int i=0;i<K;i++)
        {
            for (int j =0;j<NUMBER;j++)
            {
                //var[i] = var[i]+(1/N_k[i])*(responsible[j][i])*(point[j]-u[i])*(point[j]-u[i]);
                var[i][0][0] = var[i][0][0]+(1/N_k[i])*(responsible[j][i])*(point[j][0]-u[i][0])*(point[j][0]-u[i][0]);
                var[i][0][1] = var[i][0][1]+(1/N_k[i])*(responsible[j][i])*(point[j][0]-u[i][0])*(point[j][1]-u[i][1]); 
                var[i][1][0] = var[i][1][0]+(1/N_k[i])*(responsible[j][i])*(point[j][1]-u[i][1])*(point[j][0]-u[i][0]);
                var[i][1][1] = var[i][1][1]+(1/N_k[i])*(responsible[j][i])*(point[j][1]-u[i][1])*(point[j][1]-u[i][1]);
            }
        }

        for (int i =0;i<K;i++)
        {
            coefficient[i] = N_k[i]/NUMBER;
        }

        /*
           for (int i =0;i<K;i++)              //输出 coe[]、u[][]、var[][][]
           {
           cout << "coe[" << i << "] = " << coefficient[i] << "   " ;
           }
           cout << endl << endl;
           for (int i =0;i<3;i++)
           {   
           for (int j =0;j<2;j++)
           {
           cout << "u[" << i << "][" << j << "] = " << u[i][j] <<"    ";
           }
           cout << endl;
           }
           cout << endl;
           for (int i =0;i<3;i++)
           {
           for (int j =0;j<2;j++)
           {
           for (int k =0;k<2;k++)
           {
           cout << "var[" << i << "][" << j << "][" << k << "] = " << var[i][j][k] << "   ";
           }
           cout << endl;
           }
           cout << endl;
           }
         */

    }
    return 1;
}


int main()
{
    //char *file_points = "test1_01.txt";
    //char *file_points = "test1_02.txt";
    char *file_points = "test1_total_new.txt";
    int num = Count_Lines(file_points);
    long double** p1 = Input_points(file_points,num);
    cout <<"points number = "<< num << endl;
    long double GG = Gauss_Mixture_Model(p1,num);
    /*
       long double* x = new long double [2]; x[0] = 3;x[1] = 5; //测试高斯函数
       long double* u = new long double [2]; u[0] = 1;u[1] = 3;
       long double**v = new long double* [2]; 
       for (int i =0;i<2;i++)
       {
       v[i] = new long double [2];
       } 
       v[0][0] = 2;v[0][1] = 0;v[1][0] = 0;v[1][1] = 2;
       long double final = Gauss_Function(x,u,v);
       cout << final << endl;
       long double** final = Inverse_matrix(v); //测试逆矩阵
       for (int i =0;i<2;i++)
       {
       for (int j =0;j<2;j++)
       {
       cout << setw(10) << final[i][j] ;
       }
       cout << endl;
       }

       long double* x = new long double [2]; x[0] = 250;x[1] = 200; 
       long double* u = new long double [2]; u[0] = 300;u[1] = 250;
       long double**v = new long double* [2]; 
       for (int i =0;i<2;i++)
       {
       v[i] = new long double [2];
       }
       v[0][0] = 500;v[0][1] = 0;v[1][0] = 0;v[1][1] = 500;//测试方差选取
       long double final = Gauss_Function(x,u,v);
       cout << final << endl;
     */
    cout << "mycount =" << mycount<< endl;
    cout << "midcount =" << midcount<< endl;
    return 0;
}

