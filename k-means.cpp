#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <random>

#define DATASET_PATH "dataset.txt"
#define K 2

using std::cout;
using std::endl;

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

void get_random_centroids(std::vector<Point>& p, std::vector<Point>& c) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, p.size());  // random number from 0 until points vector size
	            
	for(Point& centroid : c) {
		int random_index{dist(gen)}; // get a random index from points vector  
		centroid = p[random_index];
	}
}

double calculate_distance(Point p, Point c) {
	return std::sqrt( (p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y) );
}

void k_means(std::vector<Point> p, std::vector<Point> c) {

	int iterations{0};
	bool changed{true};

	while(changed) {

		changed = false;
		iterations++;

		for(int i = 0; i < p.size(); i++) {
			p[i].min_distance = __DBL_MAX__;
			int prev_cluster{p[i].cluster};

			for(int j = 0; j < c.size(); j++) {
				double curr_distance{calculate_distance(p[i], c[j])};

				if(curr_distance < p[i].min_distance) {
					p[i].min_distance = curr_distance;
					p[i].cluster      = j; // centroid index
				}
			}
			if(prev_cluster != p[i].cluster) changed = true;
		}

		for(int k = 0; k < c.size(); k++) {
			double x_sum{0};
			double y_sum{0};
			int    count{0};

			for(int m = 0; m < p.size(); m++) {
				if(p[m].cluster == k) {
					x_sum += p[m].x;
					y_sum += p[m].y;
					count++;
				}
			}
			if(count > 0) {
				double x_mean{x_sum / count};
				double y_mean{y_sum / count};
				c[k] = {x_mean, y_mean};					
			}	
		}
	}
}


int main()
{
	std::vector<Point> centroids(K);
	std::vector<Point> points;
	
	read_dataset(points);

	get_random_centroids(points, centroids);

	k_means(points, centroids);

	return 0;
}
