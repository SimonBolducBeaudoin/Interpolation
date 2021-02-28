#include "../includes/Interpolation.h"

template<class Type>
inline Type lin_interpol_fct(Type& x , Type& y_a , Type& y_b , Type& x_a , Type& x_b){return y_a + (x-x_a)*(y_b-y_a)/(x_b-x_a) ;};
template<class Type>
inline Type lin_interpol_fct(Type& x , Type& y_a , Type& y_b , uint& x_a ){return y_a + (x-x_a)*(y_b-y_a);};

/* BEGIN Vectorization land */
inline void lin_interpol_SIMD_loop(uint n_i , double* result , double* new_abs , uint* index_a , double* data ,  double* old_abs)
{
	#pragma GCC ivdep
	for( uint i = 0 ; i < n_i ; i++)
	{
		result[i] = 
		lin_interpol_fct
		(
			new_abs[i] ,
			data[index_a[i]] ,
			data[index_a[i]+1],
			old_abs[index_a[i]] ,
			old_abs[index_a[i]+1]
		);
	}
}

inline void lin_interpol_SIMD_loop(uint n_i , double* result , double* new_abs , uint* index_a , double* data )
{
	#pragma GCC ivdep
	for( uint i = 0 ; i < n_i ; i++)
	{
		result[i] = 
		lin_interpol_fct
		(
			new_abs[i] ,
			data[index_a[i]] , 
			data[index_a[i]+1] ,
			index_a[i]
		);
	}
}

/* END  Vectorization land */

double_1D lin_interpol_1D( const double_1D& data , const double_1D& old_abs ,const double_1D& new_abs )
{
	
	// uint index_a ;
	// uint index_b ;
	// double x_a ;
	// double x_b ;
	// double y_a ;
	// double y_b ;
	// double x;
	uint index_a[new_abs.get_n_i()] ;
	double tmp1 = old_abs[1]-old_abs[0] ; 
	for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
	{
		index_a[i] = (uint)(new_abs[i]/tmp1) ; 
	}
	
	double_1D result( new_abs.get_n_i() );
	
	lin_interpol_SIMD_loop( new_abs.get_n_i() , result.get_ptr() , new_abs.get_ptr() , index_a , data.get_ptr() , old_abs.get_ptr());
	// for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
	// {
		// index_a = (uint)(new_abs[i]/tmp1);
		// index_b = index_a + 1 ; 
		// x_a = old_abs[index_a] ;
		// x_b = old_abs[index_b] ;
		// y_a = data[index_a] ;
		// y_b = data[index_b] ;
		// x = new_abs[i] ;
		
		// result[i] =  lin_interpol_fct(x,y_a,y_b,x_a,x_b);
	// }
	
	return result ; // Move semantic should make this very fast
};


double_2D lin_interpol_1D( const double_2D& data , const double_1D& old_abs ,const double_1D& new_abs )
{
	uint index_a[new_abs.get_n_i()] ;
	
	double tmp1 = old_abs[1]-old_abs[0] ; 
	/* Calculate all the idexes onces */
	for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
	{
		index_a[i] = (uint)(new_abs[i]/tmp1) ; 
	}
	
	double_2D result( data.get_n_j() , new_abs.get_n_i() ) ;
	
	int n_threads = physical_n_threads();
	omp_set_num_threads(n_threads);
	#pragma omp parallel
	{	
		// double x_a ;
		// double x_b ;
		// double y_a ;
		// double y_b ;
		// double x ;
		#pragma omp for
		for( uint j = 0 ; j < data.get_n_j() ; j++)
		{
			lin_interpol_SIMD_loop( new_abs.get_n_i() , result[j] , new_abs.get_ptr() , index_a , data[j] , old_abs.get_ptr());
			// for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
			// {
				// x_a = old_abs[ index_a[i] ] ;
				// x_b = old_abs[ index_a[i]+1 ] ;
				// y_a = data( j , index_a[i] ) ;
				// y_b = data( j , index_a[i]+1 ) ;
				// x = new_abs[i] ;
				// result(j,i) = lin_interpol_fct(x,y_a,y_b,x_a,x_b);
			// }
		}
	}
	
	return result ; // Move semantic should make this very fast
};

double_3D lin_interpol_1D( const double_3D& data , const double_1D& old_abs ,const double_1D& new_abs )
{
	uint index_a[new_abs.get_n_i()] ;
	
	double tmp1 = old_abs[1]-old_abs[0] ; 
	double_3D result( data.get_n_k() , data.get_n_j() , new_abs.get_n_i() ) ;
	
	/* Calculate all the idexes onces */
	for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
	{
		index_a[i] = (uint)(new_abs[i]/tmp1) ; 
	}
	
	int n_threads = physical_n_threads();
	omp_set_num_threads(n_threads);
	#pragma omp parallel
	{	
		#pragma omp for
		for( uint k = 0 ; k < data.get_n_k() ; k++)
		{
			for( uint j = 0 ; j < data.get_n_j() ; j++)
			{	
				lin_interpol_SIMD_loop( new_abs.get_n_i() , result(k,j) , new_abs.get_ptr() , index_a , data(k,j) , old_abs.get_ptr());
				// #pragma GCC ivdep 
				// for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
				// {
					// result(k,j,i) = lin_interpol_fct( new_abs[i],data(k,j,index_a[i]),data(k,j,index_a[i]+1),old_abs[index_a[i]],old_abs[index_a[i]+1] );
				// }
			}
		}
	}
	
	return result ; // Move semantic should make this very fast
};


double_1D lin_interpol_1D( const double_1D& data , const double_1D& new_abs )
{
	
	// uint x_a ;
	// uint x_b ;
	// double y_a ;
	// double y_b ;
	// double x;
	
	// double_1D result( new_abs.get_n_i() );
	
	// for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
	// {
		// x_a = (uint)(new_abs[i]) ; 
		// x_b = x_a + 1 ; 
		// y_a = data[x_a] ;
		// y_b = data[x_b] ;
		// x = new_abs[i] ;
		// result[i] = lin_interpol_fct(x,y_a,y_b,x_a);
	// }
	uint index_a[new_abs.get_n_i()] ;
	for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
	{
		index_a[i] = (uint)(new_abs[i]) ; 
	}
	
	double_1D result( new_abs.get_n_i() );
	
	lin_interpol_SIMD_loop( new_abs.get_n_i() , result.get_ptr() , new_abs.get_ptr() , index_a , data.get_ptr() );
	
	return result; // Move semantic should make this very fast
};

double_2D lin_interpol_1D( const double_2D& data , const double_1D& new_abs )
{
	
	uint index_a[new_abs.get_n_i()] ;
	
	double_2D result( data.get_n_j() , new_abs.get_n_i() ) ;
	
	/* Calculate all the idexes onces */
	for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
	{
		index_a[i] = (uint)(new_abs[i]) ; 
	}
	
	int n_threads = physical_n_threads();
	omp_set_num_threads(n_threads);
	#pragma omp parallel
	{	
		// uint x_a ;
		// uint x_b ;
		// double y_a ;
		// double y_b ;
		// double x;
		#pragma omp for
		for( uint j = 0 ; j < data.get_n_j() ; j++)
		{
			lin_interpol_SIMD_loop( new_abs.get_n_i() , result(j) , new_abs.get_ptr() , index_a , data(j) );
			// for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
			// {
				// x_a = index_a[i] ;
				// x_b = index_a[i]+1 ;
				// y_a = data( j , x_a ) ;
				// y_b = data( j , x_b ) ;
				// x = new_abs[i] ;
				// result(j,i) = lin_interpol_fct(x,y_a,y_b,x_a);
			// }
		}
	}

	return result ; // Move semantic should make this very fast
};

double_3D lin_interpol_1D( const double_3D& data , const double_1D& new_abs )
{
	uint index_a[new_abs.get_n_i()] ;
	double_3D result( data.get_n_k() , data.get_n_j() , new_abs.get_n_i() ) ;
	
	/* Calculate all the idexes onces */
	for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
	{
		index_a[i] = (uint)(new_abs[i]) ; 
	}
	
	int n_threads = physical_n_threads();
	omp_set_num_threads(n_threads);
	#pragma omp parallel
	{	
		#pragma omp for
		for( uint k = 0 ; k < data.get_n_k() ; k++)
		{
			for( uint j = 0 ; j < data.get_n_j() ; j++)
			{
				lin_interpol_SIMD_loop( new_abs.get_n_i() , result(k,j) , new_abs.get_ptr() , index_a , data(k,j) );
				// for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
				// {
					// result(k,j,i) = lin_interpol_fct( new_abs[i],data( k , j , index_a[i] ),data( k , j , index_a[i]+1 ),index_a[i] );
				// }
			}
		}
	}
	return result ; // Move semantic should make this very fast
};

linear_interpolation_1D::linear_interpolation_1D(const double_3D& data,const double_1D& new_abs)
:
	index_a( uint_1D(new_abs.get_n_i()) ),
	result( double_3D(data.get_n_k() , data.get_n_j() , new_abs.get_n_i()) )
{};

double_3D linear_interpolation_1D::execute( const double_3D& data , const double_1D& new_abs )
{
	for( uint i = 0 ; i < new_abs.get_n_i() ; i++)
	{
		index_a[i] = (uint)(new_abs[i]) ; 
	}
	int n_threads = physical_n_threads();
	omp_set_num_threads(n_threads);
	
	#pragma omp parallel for collapse(2)
	for( uint k = 0 ; k < data.get_n_k() ; k++)
	{
		for( uint j = 0 ; j < data.get_n_j() ; j++)
		{
			lin_interpol_SIMD_loop( new_abs.get_n_i() , result(k,j) , new_abs.get_ptr() , index_a.get_ptr() , data(k,j) );
		}
	}
	return result ; 
};

////// Deprecated ///////

// void interpolation_linear ( const double* data , const double* old_abs , uint l_data , const double* new_abs , double* result , uint l_result )
// { 
	// uint index_a ;
	// uint index_b ;
	// double x_a ;
	// double x_b ;
	// double y_a ;
	// double y_b ;
	// double x;
	
	// double tmp1 = old_abs[l_data-1]/l_data ; 
	
	// for( uint i = 0 ; i < l_result ; i++)
	// {
		// index_a = (uint)(new_abs[i]/tmp1); 
		// index_b = index_a + 1 ; 
		// x_a = old_abs[index_a] ;
		// x_b = old_abs[index_b] ;
		// y_a = data[index_a] ;
		// y_b = data[index_b] ;
		// x = new_abs[i] ;
		// result[i] = ( x - x_b ) * y_a / ( x_a - x_b ) + ( x_a - x ) * y_b / ( x_a - x_b ) ;
	// }
// };

// void interpolation_linear_index( const double* data , const double* new_abs , double* result , uint l_result )
// { 
	// uint x_a ;
	// uint x_b ;
	// double y_a ;
	// double y_b ;
	// double x;
	
	// for( uint i = 0 ; i < l_result ; i++)
	// {
		// x_a = (uint)(new_abs[i]) ; 
		// x_b = x_a + 1 ; 
		// y_a = data[x_a] ;
		// y_b = data[x_b] ;
		// x = new_abs[i] ;
		// result[i] = (x_b - x)*y_a + (x - x_a)*y_b ;
	// }
// };