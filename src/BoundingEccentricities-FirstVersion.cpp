// Bounding Eccentricity algorithm - first version

#include <BoudingEccentricities.hh>


void print_vector_bool(igraph_vector_bool_t *v, igraph_integer_t e)
{
    for (int i = 0; i < e; i++)
        std::cout << (int)igraph_vector_bool_e(v, i) << " ";
    std::cout << "\n";
}

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

igraph_vector_t boudingEccentricities(igraph_t graph) {
    std::cout << "-- calcul des eccentricités\n";

    igraph_t W{};
    igraph_copy(&W, &graph);    // W est une copie du graphe d'entrée
    
    igraph_integer_t n_edges = igraph_ecount(&W);     // nombre d'edges
    igraph_integer_t n_verts = igraph_vcount(&W);     // nombre de vertices 
    igraph_integer_t n_verts_total = n_verts;
    
    // eccentricité et bornes sup/inf - initialisation
    igraph_vector_t ecc, eccU, eccL;
    igraph_vector_bool_t candidates;
    igraph_vector_bool_init(&candidates, n_verts);
    igraph_vector_init(&ecc, n_verts);
    igraph_vector_init(&eccU, n_verts);
    igraph_vector_init(&eccL, n_verts);
    for (igraph_integer_t i = 0; i < n_verts; i++)
    {
        igraph_vector_bool_set(&candidates, i, true);
        igraph_vector_set(&ecc, i, 0);
        igraph_vector_set(&eccU, i, std::numeric_limits<igraph_integer_t>::max());
        igraph_vector_set(&eccL, i, std::numeric_limits<igraph_integer_t>::min());
    }
    
    srand(time(0));     // initialisation d'un seed pour les fonctions de random
    int it = 0;
    while (n_verts > 0)
    {
        // sélection d'un noeud
        igraph_integer_t v = rand() % n_verts_total;
        
        std::cout << "itération " << it << "\n";
        it++;

        // calcul de l'eccentricité
        igraph_vector_t ecc_i;
        igraph_vector_init(&ecc_i, n_verts_total);
        igraph_eccentricity(&W, &ecc_i, igraph_vss_1(v), IGRAPH_ALL);
        igraph_real_t eccentricity = igraph_vector_e(&ecc_i, 0);
        // ecc[v] <- eccentricity(v)
        igraph_vector_set(&ecc, v, eccentricity);


        // calcul de toutes les distances entre v et les noeuds de W
        // TODO : utiliser 'candidates'
        igraph_matrix_t res;
        igraph_matrix_init(&res, 1, n_verts_total);
        igraph_shortest_paths(&W, &res, igraph_vss_1(v), igraph_vss_all(), IGRAPH_ALL);
        igraph_vector_t distances;
        igraph_vector_init(&distances, n_verts_total);
        igraph_matrix_get_row(&res, &distances, 0);


        for (igraph_integer_t w = 0; w < n_verts_total; w++)
        {
            // on ne prend que les noeuds dans W
            if (igraph_vector_bool_e(&candidates, w) == false)
                continue;
            // d : distance entre v et w
            int d = igraph_vector_e(&distances, w);

            igraph_integer_t eccL_new = max(igraph_vector_e(&eccL, w), max(igraph_vector_e(&ecc, v) - d, d));
            igraph_integer_t eccU_new = min(igraph_vector_e(&eccU, w), igraph_vector_e(&ecc, v) + d);

            igraph_vector_set(&eccL, w, eccL_new);
            igraph_vector_set(&eccU, w, eccU_new);
            if (eccL_new == eccU_new)
            {
                igraph_vector_set(&ecc, w, eccL_new);

                // suppression de w dans le graphe W
                //igraph_delete_vertices(&W, igraph_vss_1(w));
                igraph_vector_bool_set(&candidates, w, false);
                n_verts --;
            }
            
        }
    }

    std::cout << "-- DONE -- result :\n";
    print_vector(&ecc, n_verts_total);
    return ecc;
}