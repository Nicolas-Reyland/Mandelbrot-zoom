#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "mandelbrot.hpp"
#include <iostream>
#include <FL/fl_draw.H>

void callback_func( void* );

class Main_Window : public Fl_Window {
public:
	Mandelbrot *mandel;
	Main_Window(int width, int height) : Fl_Window(width, height, "Mandelbrot") {
		// resizable(this);
		mandel = new Mandelbrot(800, 800, -3.0, 1.48, -2.14, 2.14);
	}

protected:
	void draw() override {
		Fl_Window::draw();

		for (int i = 0; i < 50; i++) {
			mandel->next_iter_set();
			mandel->draw();
		}

		std::cout << "drawn" << std::endl;
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
