#pragma once

#include <Interpolation.h>

typedef py::array_t<double,py::array::c_style> np_double ; 

// Numpy compatible functions
np_double interpolation_linear_py( np_double& data , np_double& old_abs , np_double& new_abs );
np_double interpolation_linear_index_py( np_double& data , np_double& new_abs );

class linear_interpolation_1D_py
{
	public :
	linear_interpolation_1D_py( np_double& data , np_double& new_abs );
	np_double execute( np_double& data , np_double& new_abs ) ;
	
	private :
	linear_interpolation_1D Cpp_object;
};

void init_interpolation(py::module &m);
