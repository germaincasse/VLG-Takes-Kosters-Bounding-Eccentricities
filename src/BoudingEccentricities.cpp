// Bounding Eccentricity algorithm

#include <BoudingEccentricities.hh>




void print_vector(igraph_vector_t *v, igraph_integer_t e)
{

    for (int i = 0; i < e; i++)
        std::cout << (int)igraph_vector_e(v, i) << " ";
    std::cout << "\n";
}


// implémentation de l'algorithme BoundingEccentricities de Takes-Kosters.
// 
void boudingEccentricities(igraph_t graph) {
    std::cout << "-- calcul des eccentricités\n";
    igraph_t w{};
    igraph_copy(&w, &graph);    // w est une copie du graphe d'entrée
    
    igraph_integer_t e = igraph_ecount(&w);     // nombre d'edges
    
    // eccentricité et bornes sup/inf
    igraph_vector_t ecc, eccU, eccL;
    igraph_vector_init(&ecc, 0);
    igraph_vector_init(&eccU, std::numeric_limits<igraph_integer_t>::max());
    igraph_vector_init(&eccL, std::numeric_limits<igraph_integer_t>::max());


    while (igraph_ecount(&w) != 0)
    {
        // sélection d'un noeud
        igraph_integer_t v = 1;

        // calcul de l'eccentricité
        igraph_vector_t ecc_i;
        igraph_vector_init(&ecc_i, 0);
        igraph_eccentricity(&w, &ecc_i, igraph_vss_1(v), IGRAPH_ALL);
        igraph_vector_set(&ecc, v, igraph_vector_e(&ecc_i, 0));

        print_vector(&ecc, e);
        
        // TODO
        break;




    }

}