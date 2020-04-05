#include "../includes/Interpolation.h"
#include <stdio.h>

void interpolation_linear ( const double* data , const double* old_abs , uint l_data , const double* new_abs , double* result , uint l_result )
{ 
	uint index_a ;
	uint index_b ;
	double x_a ;
	double x_b ;
	double y_a ;
	double y_b ;
	double x;
	
	double tmp1 = old_abs[l_data-1]/l_data ; // max absscise over l_data
	
	for( uint i = 0 ; i < l_result ; i++)
	{
		index_a = (uint)(new_abs[i]/tmp1); 
		index_b = index_a + 1 ; 
		x_a = old_abs[index_a] ;
		x_b = old_abs[index_b] ;
		y_a = data[index_a] ;
		y_b = data[index_b] ;
		x = new_abs[i] ;
		result[i] = ( x - x_b ) * y_a / ( x_a - x_b ) + ( x_a - x ) * y_b / ( x_a - x_b ) ;
	}
};

void interpolation_linear_index( const double* data , const double* new_abs , double* result , uint l_result )
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
		result[i] = (x_b - x)*y_a + (x - x_a)*y_b ;
	}
};