#include <Multi_array.h>
#include <Interpolation.h>
#include <benchmark/benchmark.h>

static void LIN_INTERPOL_1D_ALIGN64(benchmark::State& state)
{
	double_1D new_abs(1024);
	double_1D data(1024);
	
	int  x = 0 ;
	for(uint i = 0 ; i < 1024 ; i++)
	{
		new_abs(i) = x ;
		data(i) = x/3.14159 ;
		x+=1 ;
	}
	
	for (auto _ : state)
	{
		for(uint k = 0 ; k < 128 ; k++)
		{
			for(uint j = 0 ; j < 1024 ; j++)
			{
				double_1D result = lin_interpol_1D( data , new_abs );
			}
		}
	}
		
}

BENCHMARK(LIN_INTERPOL_1D_ALIGN64)->UseRealTime();

static void LIN_INTERPOL_2D_ALIGN64(benchmark::State& state)
{
	double_1D new_abs(1024);
	double_2D data(1024,1024);
	
	for (auto _ : state)
	{
		for(uint k = 0 ; k < 128 ; k++)
		{
			double_2D result = lin_interpol_1D( data , new_abs );
		}
	}	
}
BENCHMARK(LIN_INTERPOL_2D_ALIGN64)->UseRealTime();

static void LIN_INTERPOL_3D_ALIGN64(benchmark::State& state)
{
	double_1D new_abs(1024);
	double_3D data(128,1024,1024);
	
	for (auto _ : state)
	{
		double_3D result = lin_interpol_1D( data , new_abs );
	}
		
}
BENCHMARK(LIN_INTERPOL_3D_ALIGN64)->UseRealTime();

BENCHMARK_MAIN();