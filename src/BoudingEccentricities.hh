#ifndef BE_H_
#define BE_H_

#include <igraph.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>


igraph_vector_t boudingEccentricities(igraph_t graph);

// "it" compte le nombre d'itérations de la boucle While.
// Utile pour mesurer la performance de l'algorithme.



#endif /* ! BE_H_ */