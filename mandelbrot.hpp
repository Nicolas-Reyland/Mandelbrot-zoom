#include <vector>
#include <complex>

typedef struct calculation_state_struct
{
	bool calculation_finished;
	int num_iter;
	std::complex<double> z;
	std::complex<double> c;
} calculation_state_struct;

class Mandelbrot
{
public:
	// public attributes
	int screen_width;
	int screen_height;
	double start_x;
	double end_x;
	double start_y;
	double end_y;
	double step_x;
	double step_y;

	// constructors
	// Mandelbrot() {};
	Mandelbrot(int screen_width, int screen_height, double start_x, double end_x, double start_y, double end_y);
	~Mandelbrot();

	// public methods
	void draw();
	void next_iter_set();

private:
	// private attributes
	int last_calculation_max_iter;
	std::vector<std::vector<unsigned char>> set;
	std::vector<std::vector<calculation_state_struct>> last_calculation_state;

	// private methods
	void init_calculation_state();
	calculation_state_struct calculate_point(std::complex<double> z, std::complex<double> c, int num_iter, int threshold = 2);
};
