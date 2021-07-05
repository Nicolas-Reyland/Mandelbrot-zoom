#include "mandelbrot.hpp"
#include <FL/fl_draw.H>

Mandelbrot::Mandelbrot(int max_iter, int screen_width, int screen_height, double start_x, double end_x, double start_y, double end_y, double zoom_center_x, double zoom_center_y, double zoom_coeff) :
	max_iter(max_iter),
	screen_width(screen_width), screen_height(screen_height),
	start_x(start_x), start_y(start_y), end_x(end_x), end_y(end_y),
	zoom_center_x(zoom_center_x), zoom_center_y(zoom_center_y), zoom_coeff(zoom_coeff)
{
}

Mandelbrot::~Mandelbrot() {}

void Mandelbrot::draw() {
	// fl_point(int x, int y) -> draws a pixel at x,y
	// fl_color(FL_Color|int c) -> sets the color
	// fl_rgb_color(uchar g) -> returns grayscale
	for (int i = 0; i < screen_height; i++) {
		for (int j = 0; j < screen_width; j++) {
			unsigned char color = set[i][j];
			Fl_Color grayscale = fl_rgb_color(color);
			fl_color(grayscale);
			fl_point(j, i); // (j,i) and not (i,j) because i=y and j=x on screen
		}
	}
}

void Mandelbrot::calculate() {
	// init variables
	set = std::vector<std::vector<unsigned char>>();
	double coeff = 255.0 / (double) max_iter;
	double step_x = (end_x - start_x) / screen_width;
	double step_y = (end_y - start_y) / screen_height;
	//
	unsigned char value;
	// loop
	for (double y = start_y; y < end_y; y += step_y) {
		std::vector<unsigned char> row;
		for (double x = start_x; x < end_x; x += step_x) {
			int num_iter = calculate_point(std::complex<double>(x, y), max_iter);
			value = (unsigned char) (255.0 - (((double) num_iter) * coeff));

			row.push_back(value);
		}
		set.push_back(row);
	}
}

void Mandelbrot::calculate_and_draw() {
	// init variables
	double coeff = 255.0 / (double) max_iter;
	double step_x = (end_x - start_x) / screen_width;
	double step_y = (end_y - start_y) / screen_height;
	//
	unsigned char value;
	// loop
	int i = 0;
	for (double y = start_y; y < end_y; y += step_y) {
		std::vector<unsigned char> row;
		int j = 0;
		for (double x = start_x; x < end_x; x += step_x) {
			int num_iter = calculate_point(std::complex<double>(x, y), max_iter);
			value = (unsigned char) (255.0 - (((double) num_iter) * coeff));
			// draw pixel
			Fl_Color grayscale = fl_rgb_color(value);
			fl_color(grayscale);
			fl_point(j, i);
			j++;
		}
		i++;
	}
}

void Mandelbrot::zoom() {
	// calculate distances
	double 	distance_left	= zoom_center_x - start_x,
			distance_right	= end_x - zoom_center_x,
			distance_top	= zoom_center_y - start_y,
			distance_bottom	= end_y - zoom_center_y;
	// calculate zoom distances
	double  zoom_left	= distance_left * zoom_coeff,
			zoom_right	= distance_right * zoom_coeff,
			zoom_top	= distance_top * zoom_coeff,
			zoom_bottom	= distance_bottom * zoom_coeff;
	// apply changes
	start_x += zoom_left;
	start_y += zoom_top;
	end_x -= zoom_right;
	end_y -= zoom_bottom;
}

int Mandelbrot::calculate_point(std::complex<double> z, int max_iter, int threshold) {
	int num_iter = 0;
	std::complex<double> c = z;

	while (num_iter < max_iter && abs(z) < threshold) {
		z = z * z + c;
		num_iter++;
	}

	return num_iter;
}
