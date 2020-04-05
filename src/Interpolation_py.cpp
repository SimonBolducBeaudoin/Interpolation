#include "../includes/Interpolation_py.h"

// Numpy compatible functions
np_double interpolation_linear_py( np_double& data , np_double& old_abs , np_double& new_abs )
{
	py::buffer_info buf_data = data.request(),
					buf_old_abs = old_abs.request(),
					buf_new_abs = new_abs.request() ;

	/* Temporary variables */
	uint l_data = buf_old_abs.size ; 
	uint l_result = buf_new_abs.size ;
	
	double* result = (double*)malloc(l_result*sizeof(double)); // Will be freed by python 
	py::capsule free_when_done( result , free ) ; // This will help python to free result pointer
	
	interpolation_linear( (double*)buf_data.ptr , (double*)buf_old_abs.ptr , l_data , (double*)buf_new_abs.ptr , result , l_result ) ;
	
	return  np_double
			(
				{ l_result }, // shape
				{ sizeof(double) }, // Strides
				result, // Pointer
				free_when_done
			);
}


np_double interpolation_linear_index_py( np_double& data , np_double& new_abs )
{
	py::buffer_info buf_data = data.request(),
					buf_new_abs = new_abs.request() ;

	uint l_result = buf_new_abs.size ;
	
	double* result = (double*)malloc(l_result*sizeof(double)); // Will be freed by python 
	py::capsule free_when_done( result , free ) ; // This will help python to free result pointer
	
	
	interpolation_linear_index( (double*)buf_data.ptr , (double*)buf_new_abs.ptr , result , l_result ) ;
	
	return  np_double
			(
				{ l_result }, // shape
				{ sizeof(double) }, // Strides
				result, // Pointer
				free_when_done
			);
}

void init_interpolation(py::module &m)
{
	m.def("interpolation_linear", &interpolation_linear_py , "data"_a.noconvert() , "old_abs"_a.noconvert() , "new_abs"_a.noconvert() ) ;
	m.def("interpolation_linear_index", &interpolation_linear_index_py , "data"_a.noconvert() , "new_abs"_a.noconvert() ) ;
}


