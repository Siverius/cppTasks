#include <iostream>

struct Point
{
	double x, y;
};

struct Triangle
{
	Point a, b, c;
};

bool is_inside(const Triangle & triangle, const Point & point);

int main()
{
	// triangle
	double x1, y1; // first angle
	double x2, y2; // second angle
	double x3, y3; // third angle

	double xp, yp; // lonely point

	std::cout << "First angle (x and y): ";
	std::cin >> x1 >> y1;
	
	Point angle_1 = {x1, y1};

	std::cout << "Second angle (x and y): ";
	std::cin >> x2 >> y2;

	Point angle_2 = {x2, y2};
	
	std::cout << "Third angle (x and y): ";
	std::cin >> x3 >> y3;

	Point angle_3 = {x3, y3};

	Triangle triangle = {angle_1, angle_2, angle_3};

	std::cout << "Point (x and y): ";
	std::cin >> xp >> yp;

	Point point = {xp, yp};

	std::cout << (is_inside(triangle, point) > 0 ? "Point is in triangle" : "Missed") << std::endl;
}

bool is_inside(const Triangle & triangle, const Point & point)
{
	double A = (triangle.a.x - point.x)*(triangle.b.y - triangle.a.y) - (triangle.b.x - triangle.a.x)*(triangle.a.y - point.y);
	double B = (triangle.b.x - point.x)*(triangle.c.y - triangle.b.y) - (triangle.c.x - triangle.b.x)*(triangle.b.y - point.y);
	double C = (triangle.c.x - point.x)*(triangle.a.y - triangle.c.y) - (triangle.a.x - triangle.c.x)*(triangle.c.y - point.y);
	
	if(A > 0 and B > 0 and C > 0) return 1;
	if(A < 0 and B < 0 and C < 0) return 1;
	
	return 0;
}

