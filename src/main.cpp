#include <igraph.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

// Transforme un fichier au format de C. Magnien en un igraph
// (nombre de vertices suivi de la liste des edges)
igraph_t magnien_to_igraph(char* path) {
	igraph_t graph{};
	FILE* file = fopen(path, "r");
	char line[256];
	int n_vertices = std::stoi(fgets(line, sizeof(line), file));
	igraph_read_graph_edgelist(&graph, file, n_vertices, false);
	return graph;
}

void igraph_summary(const igraph_t* graph)
{
	std::cout << "vertices: " << igraph_vcount(graph) << "\n";
	std::cout << "edges: " << igraph_ecount(graph) << "\n";
	std::cout << "is directed?: " << igraph_is_directed(graph) << "\n";
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
}

