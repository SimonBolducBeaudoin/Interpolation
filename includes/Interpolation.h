#pragma once

typedef unsigned int uint ; 

// https://fr.wikipedia.org/wiki/Interpolation_lin%C3%A9aire


/*
Interpolation functions are assuming that the old_abs is spread linearly
Also no checks are made.
*/
void interpolation_linear
( 
	const double* data , // A Pointer to the vector that needs to be interpolated
	const double* old_abs , // Le vecteur d'abscisse a interpoler
	uint l_data , //  La longeur de data et old_abs
	const double* new_abs , // Le vecteur d'abscisse a interpoler
	double* result , // Un vecteur de mémoire pré-allouer 
	uint l_result // La longeur de result et old_abs	
);

/*
Fonction d'interpolation écrite pour être optimale pour le projet de Martin P.
Cette fonction d'interpolation suppose que l'abscisse du vecteur d'entré est de la forme [0,1,2...,n-1]
*/
void interpolation_linear_index
( 
	const double* data , // A Pointer to the vector that needs to be interpolated
	const double* new_abs , // Le vecteur d'abscisse a interpoler
	double* result , // Un vecteur de mémoire pré-allouer 
	uint l_result // La longeur de result et old_abs	
);
