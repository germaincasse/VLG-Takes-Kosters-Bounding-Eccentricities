#include <BoudingEccentricities.hh>

// Transforme un fichier au format de C. Magnien
// (nombre de vertices suivi de la liste des edges)
// en un igraph
igraph_t magnien_to_igraph(char* path) {
	igraph_t graph{};
	FILE* file = fopen(path, "r");
	char line[256];
	int n_vertices = std::stoi(fgets(line, sizeof(line), file));
	igraph_read_graph_edgelist(&graph, file, n_vertices, false);
	return graph;
}

// affichage de quelques caractéristiques d'un graphe
void igraph_summary(const igraph_t* graph)
{
	std::cout << "vertices : " << igraph_vcount(graph) << "\n";
	std::cout << "edges : " << igraph_ecount(graph) << "\n";
	std::cout << "dirigé ? : " << igraph_is_directed(graph) << "\n";
	igraph_bool_t is_connected;
	igraph_is_connected(graph, &is_connected, IGRAPH_STRONG);
	std::cout << "connexe ? : " << is_connected << "\n";

}

int main(int argc, char *argv[])
{

	
	if (argc == 1)
		{
			printf("Expected 1 argument (path to a graph file). Exiting\n");
			return 1;
		}
	printf("transformation de '%s'\n", argv[1]);

	igraph_t graph = magnien_to_igraph(argv[1]);
	igraph_summary(&graph);
	boudingEccentricities(graph);
}

