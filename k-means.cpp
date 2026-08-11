#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

#define K 2

struct Point {
	double x, y;
	int cluster;
	double min_distance;

	Point() = default;

	Point(double x, double y) : x(x), y(y), cluster(-1), min_distance(__DBL_MAX__) {} 
};

void read_dataset(std::vector<Point>& p) {

	std::ifstream file("dataset.txt");
	if(!file.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	while(getline(file, line, '\n')) {

		double x{}, y{};
		std::stringstream ss(line);
		
		ss >> x >> y;
		p.push_back(Point(x, y));
	}
	file.close();
}

double calculate_distance(Point p, Point c) {
	return (p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y);
}


int main()
{
	
	std::vector<Point> points;
	read_dataset(points);

	Point c1{1.0, 1.0};
	Point c2{6.0, 6.0};


	// calcular distancia entre cada centroide e cada ponto
	// atribuir tal ponto para tal centroide
	// tirar a nova media do centroide
	// fazer isto ate nao modificar a media mais
	

	for(auto p : points) {
		std::cout << p.x << " " << p.y <<  std::endl; 
	}



	return 0;
}


















/*
comentarios sobre otimizações:

é possivel usar .reserve() no vector, colocando o tamanho do arquivo/quanto
de memoria sera usada, assim ele nao ira ter custo para expandir, pois
nao sera necessario





struct Point {
	double x, y;
	int cluster;
	int min_distance;

	Point() : x(0.0), y(0.0), cluster(-1), min_distance(__DBL_MAX__) {}

	Point(double x, double y) : x(x), y(y), cluster(-1), min_distance(__DBL_MAX__) {} 

};




void read_dataset() {
	std::ifstream dataset("dataset.txt");

	if(!dataset.is_open()) {
		std::cerr << "Erro arquivo" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	double p1{}, p2{};
	while(getline(dataset, line, '\n')) {
		std::stringstream ss(line);
		ss >> p1 >> p2;
		v.push_back({p1, p2});
	}
}

*/