#pragma once

#include <omp_extra.h>
#include <Multi_array.h>


typedef unsigned int uint ; 
typedef Multi_array<double,1,uint> double_1D ;
typedef Multi_array<double,2,uint> double_2D ;
typedef Multi_array<double,3,uint64_t> double_3D ;

typedef Multi_array<uint,1,uint> uint_1D ;

// https://fr.wikipedia.org/wiki/Interpolation_lin%C3%A9aire

double_1D lin_interpol_1D( const double_1D& data , const double_1D& old_abs ,const double_1D& new_abs );
double_1D lin_interpol_1D( const double_1D& data , const double_1D& new_abs ); // when Deltax = 1;

double_2D lin_interpol_1D( const double_2D& data , const double_1D& old_abs ,const double_1D& new_abs ); // interpolation along the fast iterating axis
double_2D lin_interpol_1D( const double_2D& data , const double_1D& new_abs ); // when Deltax = 1 and interpolation along the fast iterating axis

double_3D lin_interpol_1D( const double_3D& data , const double_1D& old_abs ,const double_1D& new_abs ); // interpolation along the fast iterating axis
double_3D lin_interpol_1D( const double_3D& data , const double_1D& new_abs ); // when Deltax = 1 and interpolation along the fast iterating axis

class linear_interpolation_1D
{
	public :
	linear_interpolation_1D( const double_3D& data , const double_1D& new_abs );
	double_3D execute( const double_3D& data , const double_1D& new_abs ) ;
	
	private :
	uint_1D index_a ;
	double_3D result ;
};

////// Deprecated ///////

// void interpolation_linear
// ( 
	// const double* data , // A Pointer to the vector that needs to be interpolated
	// const double* old_abs , // Le vecteur d'abscisse a interpoler
	// uint l_data , //  La longeur de data et old_abs
	// const double* new_abs , // Le vecteur d'abscisse a interpoler
	// double* result , // Un vecteur de mémoire pré-allouer 
	// uint l_result // La longeur de result et old_abs	
// );

// void interpolation_linear_index
// ( 
	// const double* data , // A Pointer to the vector that needs to be interpolated
	// const double* new_abs , // Le vecteur d'abscisse a interpoler
	// double* result , // Un vecteur de mémoire pré-allouer 
	// uint l_result // La longeur de result et old_abs	
// );

