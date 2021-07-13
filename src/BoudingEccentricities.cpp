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

template <class T, class U>
T min(T a, U b)
{
    if (a > b)
        return b;
    return a;
}


// implémentation de l'algorithme BoundingEccentricities de Takes-Kosters.
// 
void boudingEccentricities(igraph_t graph) {
    std::cout << "-- calcul des eccentricités\n";
    igraph_t W{};
    igraph_copy(&W, &graph);    // W est une copie du graphe d'entrée
    
    igraph_integer_t n_edges = igraph_ecount(&W);     // nombre d'edges
    igraph_integer_t n_verts = igraph_vcount(&W);     // nombre de vertices 
    std::cout << n_verts << " vertices\n";
    
    // eccentricité et bornes sup/inf - initialisation
    igraph_vector_t ecc, eccU, eccL;
    igraph_real_t ecc_c[n_verts] = {0};
    igraph_real_t eccU_c[n_verts] = {std::numeric_limits<igraph_integer_t>::max()};
    igraph_real_t eccL_c[n_verts] = {std::numeric_limits<igraph_integer_t>::min()};
    igraph_vector_init_copy(&ecc, ecc_c, n_verts);
    igraph_vector_init_copy(&eccU, eccU_c, n_verts);
    igraph_vector_init_copy(&eccL, eccL_c, n_verts);
    
    srand(time(0));
    int it = 0;
    while (igraph_ecount(&W) != 0)
    {

        // sélection d'un noeud


        igraph_integer_t v = rand() % n_verts;

        it++;
        std::cout << "iteration " << it << " - n_verts=" << igraph_ecount(&W) << " - v=" << v << " - ";

        // calcul de l'eccentricité
        igraph_vector_t ecc_i;
        igraph_vector_init(&ecc_i, n_verts);
        igraph_eccentricity(&W, &ecc_i, igraph_vss_1(v), IGRAPH_ALL);
        igraph_real_t eccentricity = igraph_vector_e(&ecc_i, 0);
        igraph_vector_set(&ecc, v, eccentricity);

        print_vector(&ecc, n_verts);
        
        for (igraph_integer_t w = 0; w < n_verts; w++)
        {
            n_verts = igraph_vcount(&W);     // nombre de vertices 
            // d : distance entre v et w
            int d = 0;
            igraph_vector_t v_w, e_w;
            igraph_vector_init(&v_w, n_verts);
            igraph_vector_init(&e_w, n_verts);

            
            igraph_get_shortest_path(&W, &v_w, &e_w, v, w, IGRAPH_ALL);
            // std::cout << "path from " << v << " to " << w << "\n";
            // print_vector(&e_w, igraph_ecount(&W));
            // print_vector(&v_w, igraph_ecount(&W));

            // TODO : calcul de d //
            

            igraph_vector_set(&eccL, w, max(igraph_vector_e(&eccL, w), max(igraph_vector_e(&ecc, n_verts) - d, d)));
            igraph_vector_set(&eccU, w, min(igraph_vector_e(&eccU, w), d));

            if (igraph_vector_e(&eccL, w) == igraph_vector_e(&eccU, w))
            {
                igraph_vector_set(&ecc, w, igraph_vector_e(&eccL, w));
                igraph_delete_vertices(&W, igraph_vss_1(w));
                std::cout << "DELETING VERTICE " << w << "\n";
            }

        }

        // TODO : retirer ce break

        
    }

}