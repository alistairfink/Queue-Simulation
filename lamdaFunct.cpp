#include <math.c>
#include<cstdlib>

float x_func(float u, float lamda){
	float k = -1.0/lambda;
	return k*log(1-u);
}

int main(){

	float x = 1;

	float ans =0;
	float lamda = 1/75;


	ans = x_func(x,lamda);

	cout<< ans<<endl;


	return 0;
}