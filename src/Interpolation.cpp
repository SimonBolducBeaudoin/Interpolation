#include "../includes/Interpolation.h"

void Interpolation_linear ( const double* data , const double* new_abs , double* result , uint l_result )
{ 
	uint x_a ;
	uint x_b ;
	double y_a ;
	double y_b ;
	
	double x;
	
	for( uint i = 0 ; i < l_result ; i++)
	{
		x_a = (uint)(new_abs[i]) ; 
		x_b = x_a + 1 ; 
		y_a = data[x_a] ;
		y_b = data[x_b] ;
		x = new_abs[i] ;
		result[i] = (x - x_b)*y_a + (x_a - x)*y_b ;
	}
};