#pragma once

#include "../../includes/header_common.h"
#include "Interpolation.h"
// #include "../../SM-Scoped_timer/includes/scoped_timer.h"
// #include "../../Omp_extra/includes/omp_extra.h"
// #include "../../Multi_array/Multi_array.h"

typedef py::array_t<double,py::array::c_style> np_double ; 


/*
No checks are made for now
*/

// Numpy compatible functions
np_double interpolation_linear_py( np_double& data , np_double& old_abs , np_double& new_abs );
np_double interpolation_linear_index_py( np_double& data , np_double& new_abs );

void init_interpolation(py::module &m);
