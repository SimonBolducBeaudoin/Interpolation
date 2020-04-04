#pragma once

typedef unsigned int uint ; 

// https://fr.wikipedia.org/wiki/Interpolation_lin%C3%A9aire

/*
Fonction d'interpolation écrite pour être optimale pour le projet de Martin P.

Cette fonction d'interpolation doit être ré-écrite pour être générale.
Pour l'instant elle ne fonctionne que pour le cas ou l'abscise initiale est uint.
*/

void Interpolation_linear
( 
	const double* data , // A Pointer to the vector that needs to be interpolated
	const double* new_abs , // Le vecteur d'abscisse a interpoler
	double* result , // Un vecteur de mémoire pré-allouer 
	uint l_result // La longeur de result et old_abs	
);
