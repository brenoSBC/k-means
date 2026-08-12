#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

#define DATASET_PATH "dataset.txt"
#define K 2

struct Point {
	double x, y;
	int cluster;
	double min_distance;

	Point() = default;

	Point(double x, double y) : x(x), y(y), cluster(-1), min_distance(__DBL_MAX__) {} 
};

void read_dataset(std::vector<Point>& p) {

	std::ifstream file(DATASET_PATH);
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
	return std::sqrt( (p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y) );
}


int main()
{
	std::vector<Point> centroides { {1.0, 1.0}, {6.0, 6.0} };
	std::vector<Point> points;
	
	read_dataset(points);

	int iterations{0};
	bool changed{true};
	
	while(changed) {
		changed = false;
		iterations++;

		// para cada ponto calcula a distancia do centroide mais proximo
		for(int j = 0; j < points.size(); j++) {
			points[j].min_distance = __DBL_MAX__;
			int old_cluster{points[j].cluster};

			for(int k = 0; k < centroides.size(); k++) {
				double curr_distance{calculate_distance(points[j], centroides[k])};
				
				if(curr_distance < points[j].min_distance) {
					points[j].min_distance = curr_distance;
					points[j].cluster = k; // centroid index
				}
			}
			if(old_cluster != points[j].cluster) changed = true;
		}

		// para cada centroide calcula sua media com os pontos que pertencem ao seu cluster
		for(int m = 0; m < centroides.size(); m++) {
			double x_sum{0};
			double y_sum{0};
			int    count{0};

			for(int n = 0; n < points.size(); n++) {
				if(points[n].cluster == m) {
					x_sum += points[n].x;
					y_sum += points[n].y;
					count++;
				}
			}
			
			if(count > 0) {
				double x_mean{x_sum / count};
				double y_mean{y_sum / count};
				centroides[m] = {x_mean, y_mean};

				std::cout << "CENTROIDE: " << centroides[m].x << " " << centroides[m].y << std::endl;
			}
		}
	}
	std::cout << "ITERACOES: " << iterations << std::endl;
	return 0;
}
