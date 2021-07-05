#include "mandelbrot.hpp"
#include <FL/fl_draw.H>

Mandelbrot::Mandelbrot(int screen_width, int screen_height, double start_x, double end_x, double start_y, double end_y) :
	screen_width(screen_width), screen_height(screen_height),
	start_x(start_x), start_y(start_y),
	end_x(end_x), end_y(end_y)
{
	step_x = (end_x - start_x) / (double) screen_width;
	/*std::cout << "start_x : " << start_x << " end_x : " << end_x <<
		" step_x : " << step_x <<
		" sw : " << screen_width << std::endl;*/
	step_y = (end_y - start_y) / (double) screen_height;
	/*std::cout << "start_y : " << start_y << " end_y : " << end_y <<
		" step_y : " << step_y <<
		" sh : " << screen_height << std::endl;*/
	// initialize the calculation state
	init_calculation_state();
}

Mandelbrot::~Mandelbrot() {}

void Mandelbrot::draw() {
	// fl_point(int x, int y) -> draws a pixel at x,y
	// fl_color(FL_Color|int c) -> sets the color
	// fl_rgb_color(uchar g) -> returns grayscale
	for (int i = 0; i < screen_height; i++) {
		for (int j = 0; j < screen_width; j++) {
			unsigned char color = (unsigned char) set[i][j];
			Fl_Color grayscale = fl_rgb_color(color);
			fl_color(grayscale);
			fl_point(j, i); // (j,i) and not (i,j) because i=y and j=x on screen
		}
	}
}

void Mandelbrot::init_calculation_state() {
	// init variables
	last_calculation_max_iter = 1;
	last_calculation_state = std::vector<std::vector<calculation_state_struct>>();
	// loop
	for (double y = start_y; y < end_y; y += step_y) {
		std::vector<calculation_state_struct> row;
		for (double x = start_x; x < end_x; x += step_x) {
			row.push_back((calculation_state_struct){
				.calculation_finished = false,
				.num_iter = 0,
				.z = std::complex<double>(x, y),
				.c = std::complex<double>(x, y)
			});
		}
		last_calculation_state.push_back(row);
	}
}

void Mandelbrot::next_iter_set() {
	// init variables
	set = std::vector<std::vector<unsigned char>>();
	double coeff = 255.0 / (double) last_calculation_max_iter;
	unsigned char value;
	// loop
	for (int i = 0; i < screen_height; i++) {
		std::vector<unsigned char> row;
		for (int j = 0; j < screen_width; j++) {
			calculation_state_struct last_state = last_calculation_state[i][j];
			// max calculation depth has been reached for this pixel
			/*if (last_state.calculation_finished) {
				// add to set & continue
				value = (unsigned char) 255.0 - ((double) last_state.num_iter * coeff);
				continue;
			}*/
			// new state
			calculation_state_struct current_state = this->calculate_point(
				last_state.z,
				last_state.c,
				last_state.num_iter
			);
			//
			last_calculation_state[i][j] = current_state;
			// add to set
			value = (unsigned char) (255.0 - (((double) last_state.num_iter) * coeff));

			row.push_back(value);
		}
		set.push_back(row);
	}
	last_calculation_max_iter++;
}

calculation_state_struct Mandelbrot::calculate_point(std::complex<double> z, std::complex<double> c, int num_iter, int threshold) {
	// default state
	calculation_state_struct state;
	state.calculation_finished = true;
	state.num_iter = num_iter;
	state.z = z;
	state.c = c;
	// next state should be different
	if (abs(z) < threshold) {
		// if (num_iter > 2) std::cout << "new" << std::endl;
		std::complex<double> z2 = z * z + c;
		state.calculation_finished = false;
		state.num_iter++;
		state.z = z2;
	}
	// return the state
	return state;
}
