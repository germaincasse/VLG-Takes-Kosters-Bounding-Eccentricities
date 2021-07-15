// Bounding Eccentricity algorithm
#include <BoudingEccentricities.hh>

// affichage d'un vecteur de type igraph_vector_bool_t
void print_vector_bool(igraph_vector_bool_t *v, igraph_integer_t e)
{
    for (int i = 0; i < e; i++)
        std::cout << (int)igraph_vector_bool_e(v, i) << " ";
    std::cout << "\n";
}

// affichage d'un vecteur de type igraph_vector_t
void print_vector(igraph_vector_t *v, igraph_integer_t e)
{

    for (int i = 0; i < e; i++)
        std::cout << (int)igraph_vector_e(v, i) << " ";
    std::cout << "\n";
}

// fonction templatée pour le calcul du maximum entre deux valeurs
template <class T, class U>
T max(T a, U b)
{
    if (a > b)
        return a;
    return b;
}

// fonction templatée pour le calcul du minimum entre deux valeurs
template <class T, class U>
T min(T a, U b)
{
    if (a > b)
        return b;
    return a;
}

// Variable qui compte le nombre d'itérations dans la boucle While de notre
// algorithme. Cette variable est globale afin de pouvoir moyenner cette valeur
// après de nombreuses passes de l'algorithme, pour obtenir le nombre d'itérations moyen
// dans le cas où celui-ci n'est pas fixe pour un même graphe.
int it = 0;



// implémentation de l'algorithme BoundingEccentricities de Takes-Kosters.
igraph_vector_t boudingEccentricities(igraph_t graph) {

    igraph_t W{};
    igraph_copy(&W, &graph);    // W est une copie du graphe d'entrée
    
    igraph_integer_t n_edges = igraph_ecount(&graph);     // nombre d'edges
    const igraph_integer_t n_verts = igraph_vcount(&graph);     // nombre de vertices 
    igraph_integer_t n_verts_in_W = n_verts;              // nombre de vertices dans W, qui sera modifié
    
    // eccentricité et bornes sup/inf - initialisation
    igraph_vector_t ecc, eccU, eccL;
    igraph_vector_bool_t candidates;
    igraph_vector_bool_init(&candidates, n_verts);
    igraph_vector_init(&ecc, n_verts);
    igraph_vector_init(&eccU, n_verts);
    igraph_vector_init(&eccL, n_verts);
    for (igraph_integer_t i = 0; i < n_verts; i++)      // initialisations
    {
        igraph_vector_bool_set(&candidates, i, true);
        igraph_vector_set(&ecc, i, 0);
        igraph_vector_set(&eccU, i, std::numeric_limits<igraph_integer_t>::max());
        igraph_vector_set(&eccL, i, std::numeric_limits<igraph_integer_t>::min());
    }

    
    it = 0;     // compte les itérations
    while (n_verts_in_W > 0)
    {
        it++;

        // sélection d'un noeud
        igraph_integer_t v;
        if (it % 2 == 0)
            v = igraph_vector_which_max(&eccU);
        else
            v = igraph_vector_which_min(&eccL);
        
        // calcul de l'eccentricité
        igraph_vector_t ecc_i;
        igraph_vector_init(&ecc_i, n_verts);
        igraph_eccentricity(&W, &ecc_i, igraph_vss_1(v), IGRAPH_ALL);
        igraph_real_t eccentricity = igraph_vector_e(&ecc_i, 0);

        igraph_vector_set(&ecc, v, eccentricity);


        // calcul de toutes les distances entre v et les noeuds de W, avec un BFS
        igraph_vector_t distances;
        igraph_vector_init(&distances, n_verts);
        igraph_bfs(&W, v, nullptr, IGRAPH_ALL, false, nullptr, nullptr, nullptr, nullptr,
                    nullptr, nullptr, &distances, nullptr, nullptr);


        for (igraph_integer_t w = 0; w < n_verts; w++)
        {
            // on ne prend que les noeuds dans W :
            if (igraph_vector_bool_e(&candidates, w) == false)
                continue;
                
            // d : distance entre v et w
            int d = igraph_vector_e(&distances, w);

            // calcul de eccL[w] et eccU[w]
            igraph_integer_t eccL_new = max(igraph_vector_e(&eccL, w), max(igraph_vector_e(&ecc, v) - d, d));
            igraph_integer_t eccU_new = min(igraph_vector_e(&eccU, w), igraph_vector_e(&ecc, v) + d);
            igraph_vector_set(&eccL, w, eccL_new);
            igraph_vector_set(&eccU, w, eccU_new);

            if (eccL_new == eccU_new)
            {
                igraph_vector_set(&ecc, w, eccL_new);

                // suppression de w dans le graphe W
                igraph_vector_bool_set(&candidates, w, false);

                // suppression virtuelle de w dans eccU et eccL
                igraph_vector_set(&eccU, w, std::numeric_limits<igraph_integer_t>::min());
                igraph_vector_set(&eccL, w, std::numeric_limits<igraph_integer_t>::max());

                // réduction du nombre de noeuds dans W après chaque suppression :
                n_verts_in_W --;
            }
        }
    }
    std::cout << "-- FIN -- résultat :\n";
    // affichage et renvoi des résultats
    print_vector(&ecc, n_verts);
    return ecc;
}