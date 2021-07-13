// Bounding Eccentricity algorithm

#include <BoudingEccentricities.hh>




void print_vector(igraph_vector_t *v, igraph_integer_t e)
{

    for (int i = 0; i < e; i++)
        std::cout << (int)igraph_vector_e(v, i) << " ";
    std::cout << "\n";
}

template <class T, class U>
T max(T a, U b)
{
    if (a > b)
        return a;
    return b;
}


// implémentation de l'algorithme BoundingEccentricities de Takes-Kosters.
// 
void boudingEccentricities(igraph_t graph) {
    std::cout << "-- calcul des eccentricités\n";
    igraph_t W{};
    igraph_copy(&W, &graph);    // W est une copie du graphe d'entrée
    
    igraph_integer_t e = igraph_ecount(&graph);     // nombre d'edges
    igraph_integer_t v = igraph_vcount(&graph);     // nombre de vertices 
    std::cout << v << " vertices\n";
    
    // eccentricité et bornes sup/inf - initialisation
    igraph_vector_t ecc, eccU, eccL;
    igraph_real_t ecc_c[v] = {0};
    igraph_real_t eccU_c[v] = {std::numeric_limits<igraph_integer_t>::max()};
    igraph_real_t eccL_c[v] = {std::numeric_limits<igraph_integer_t>::min()};
    igraph_vector_init_copy(&ecc, ecc_c, v);
    igraph_vector_init_copy(&eccU, eccU_c, v);
    igraph_vector_init_copy(&eccL, eccL_c, v);


    while (igraph_ecount(&W) != 0)
    {
        // sélection d'un noeud
        igraph_integer_t vert = 8;

        // calcul de l'eccentricité
        igraph_vector_t ecc_i;
        igraph_vector_init(&ecc_i, v);
        igraph_eccentricity(&W, &ecc_i, igraph_vss_1(vert), IGRAPH_ALL);
        igraph_real_t eccentricity = igraph_vector_e(&ecc_i, 0);
        igraph_vector_set(&ecc, vert, eccentricity);

        print_vector(&ecc, v);
        break;
        /*
        for (igraph_integer_t w = 0; w < v; w++)
        {
            // d : distance entre v et w
            int d = 0;
            igraph_vector_t v_w;
            igraph_vector_init(&v_w, v, -1);
            igraph_vector_t e_w;
            igraph_vector_init(&e_w, v, -1);


            igraph_get_shortest_path(&W, &v_w, &e_w, v, w, IGRAPH_ALL);
            std::cout << "path for " << w << " with v = " << v << "\n";
            print_vector(&e_w, igraph_ecount(&W));
            print_vector(&v_w, igraph_ecount(&W));
            

            igraph_vector_set(&eccL, w, max(igraph_vector_e(&eccL, w), max(igraph_vector_e(&ecc, v) - d, d)));
        }

        // TODO
        break;

        */
    }

}