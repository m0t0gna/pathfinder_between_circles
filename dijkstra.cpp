#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <cmath>
#include <iomanip>


using namespace std;


//defining the structure for the starting point A and destination point B
struct Point {
    int x, y;
};


// calculating the distance in plane between A and B without considering circles
double calculateDistance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}


// checking if the line intersects with any circle
bool isInsideCircle(Point p, Point center, double radius) {
    return calculateDistance(p, center) <= radius;
}




int minDistance(double dist[], bool sptSet[], int V) {
    double min = INT_MAX;
    int min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}


void dijkstra(vector<vector<double>>& graph, int src, int dest, vector<Point>& circles, vector<double>& radii) {
    int V = graph.size();
    double dist[V];
    bool sptSet[V];

    // Check if circles are disjoint
    for (int i = 0; i < circles.size(); ++i) {
        Point center = circles[i];
        double radius = radii[i];
        if (isInsideCircle(Point{graph[src][0], graph[src][1]}, center, radius) ||
            isInsideCircle(Point{graph[dest][0], graph[dest][1]}, center, radius)) {
            cout << "Impossible" << endl;
            return;
        }
    }

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    cout << "The shortest destination from A to B: " << fixed << setprecision(10) << dist[dest] << endl;
}

int main() {
    ifstream fin("date.in");

    int num_circles;
    fin >> num_circles;
    cout << "Enter the number of circles: " << num_circles << endl;

    vector<Point> circles(num_circles);
    vector<double> radii(num_circles);
    for (int i = 0; i < num_circles; ++i) {
        fin >> circles[i].x >> circles[i].y >> radii[i];
        cout << "Enter the coordinates for circle " << i+1 << " (x y): " << circles[i].x << " " << circles[i].y << endl;
        cout << "Enter the radius of circle " << i+1 << " : " << radii[i] << endl;
    }

    int source, dest;
    cout << "Enter the coordinates of point A (x y): ";
    fin >> source >> dest;
    cout << "Coordinates of point A: " << source << " " << dest << endl;

    cout << "Enter the coordinates of point B (x y): ";
    fin >> source >> dest;
    cout << "Coordinates of point B: " << source << " " << dest << endl << endl;

    // Construct graph with distances
    vector<vector<double>> graph(2, vector<double>(2, 0));
    graph[0][1] = graph[1][0] = calculateDistance(Point{0, 0}, Point{source, dest});

    // Perform Dijkstra's algorithm
    dijkstra(graph, 0, 1, circles, radii);


// cam asta i tot programu 
    return 0;
}
