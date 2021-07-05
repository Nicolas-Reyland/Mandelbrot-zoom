#include <vector>
#include <complex>

class Mandelbrot
{
public:
	// public attributes
	int max_iter;
	int screen_width;
	int screen_height;
	double start_x;
	double end_x;
	double start_y;
	double end_y;
	double zoom_center_x;
	double zoom_center_y;
	double zoom_coeff;

	// constructors
	// Mandelbrot() {};
	Mandelbrot(int max_iter, int screen_width, int screen_height, double start_x, double end_x, double start_y, double end_y, double zoom_center_x, double zoom_center_y, double zoom_coeff);
	~Mandelbrot();

	// public methods
	void draw();
	void calculate();
	void calculate_and_draw();
	void zoom();

private:
	// private attributes
	std::vector<std::vector<unsigned char>> set;

	// private methods
	int calculate_point(std::complex<double> z, int max_iter, int threshold = 2);
};
