#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "mandelbrot.hpp"
#include <iostream>
#include <FL/fl_draw.H>

const double SEAHORSE_VALLEY_X = -0.388325975494149322475578856028732843697071075439453125;
const double SEAHORSE_VALLEY_Y = -0.135914091422952243437549668669817037880420684814453125;
const double INTERESTING_X = -0.75;
const double INTERESTING_Y = 0.1;

void callback_func( void* );

class Main_Window : public Fl_Window {
public:
	Mandelbrot *mandel;
	Main_Window(int width, int height) : Fl_Window(width, height, "Mandelbrot") {
		// resizable(this);
		mandel = new Mandelbrot(50, 800, 800, -2.0, 0.48, -1.12, 1.12, INTERESTING_X, INTERESTING_Y, 0.05 );
	}

protected:
	void draw() override {
		Fl_Window::draw();

		while (true) {
			mandel->calculate_and_draw();
			mandel->zoom();
		}
	}
};

void callback_func( void* ) {
	//
}

int main(int argc, char **argv) {
	Main_Window w(800, 800);
	w.show(argc, argv);
	return Fl::run();

	//Mandelbrot *mandel = new Mandelbrot(500, 500, -2.0, 0.47, -1.13, 1.13);
	Fl_Window *window = new Fl_Window(800,800);
	//window->color(FL_WHITE);
	/*Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");
	box->box(FL_UP_BOX);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labelsize(36);
	box->labeltype(FL_SHADOW_LABEL);*/
	window->end();
	window->show(argc, argv);
	std::cout << "adding idle" << std::endl;
	//Fl::add_idle( callback_func );
	std::cout << "Main Loop" << std::endl;
	return Fl::run();
}
