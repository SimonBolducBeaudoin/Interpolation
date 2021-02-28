#include "../includes/Interpolation_py.h"

// Numpy compatible functions
np_double interpolation_linear_py( np_double& np_data , np_double& np_old_abs , np_double& np_new_abs )
{
	py::buffer_info info = np_data.request();
	
	double_1D old_abs = double_1D::numpy(np_old_abs);
	double_1D new_abs = double_1D::numpy(np_new_abs);

	if (info.ndim == 1)
	{
		/* Make some verifications ? */
		double_1D data = double_1D::numpy(np_data);
		double_1D result = lin_interpol_1D( data , old_abs , new_abs );
		return  result.move_py();
	}
	else if(info.ndim == 2)
	{
		/* Make some verifications ? */
		double_2D data = double_2D::numpy(np_data);
		double_2D result = lin_interpol_1D( data , old_abs , new_abs );
		return  result.move_py();
	}
	else if(info.ndim == 3)
	{
		/* Make some verifications ? */
		double_3D data = double_3D::numpy(np_data);
		double_3D result = lin_interpol_1D( data , old_abs , new_abs );
		return  result.move_py();
	}
	else
	{
		throw std::runtime_error("Wrong dimensions !");
	}
}

np_double interpolation_linear_py( np_double& np_data , np_double& np_new_abs )
{
	
	py::buffer_info info = np_data.request();
	
	double_1D new_abs = double_1D::numpy(np_new_abs);
	
	if (info.ndim == 1)
	{
		
		/* Make some verifications ? */
		double_1D data = double_1D::numpy(np_data);
		double_1D result = lin_interpol_1D( data , new_abs );
		return  result.move_py();
	}
	else if(info.ndim == 2)
	{
		
		/* Make some verifications ? */
		double_2D data = double_2D::numpy(np_data);
		double_2D result = lin_interpol_1D( data , new_abs );
		return  result.move_py();
	}
	else if(info.ndim == 3)
	{
		
		/* Make some verifications ? */
		double_3D data = double_3D::numpy(np_data);
		double_3D result = lin_interpol_1D( data , new_abs );
		return  result.move_py();
	}
	else
	{
		throw std::runtime_error("Wrong dimensions !");
	}
}

linear_interpolation_1D_py::linear_interpolation_1D_py( np_double& data , np_double& new_abs )
:
	Cpp_object( linear_interpolation_1D( double_3D::numpy(data) , double_1D::numpy(new_abs) ) )
{};

np_double linear_interpolation_1D_py::execute( np_double& data , np_double& new_abs )
{
	double_3D result = Cpp_object.execute( double_3D::numpy(data) , double_1D::numpy(new_abs) );
	return result.share_py() ; 
};

void init_interpolation(py::module &m)
{
	m.def("lin_interpol_1D", (np_double (*)(np_double&,np_double&,np_double&) ) &interpolation_linear_py , "data"_a.noconvert() , "old_abs"_a.noconvert() , "new_abs"_a.noconvert() ) ;
	m.def("lin_interpol_1D", (np_double (*)(np_double&,np_double&			) ) &interpolation_linear_py , "data"_a.noconvert() , "new_abs"_a.noconvert() ) ;

	py::class_<linear_interpolation_1D_py>( m , "linear_interpolation_1D")
	.def
	(
		py::init<np_double&,np_double&>(),
		"data"_a.noconvert() , "new_abs"_a.noconvert()
	)
	.def("execute", &linear_interpolation_1D_py::execute)
	;
}


