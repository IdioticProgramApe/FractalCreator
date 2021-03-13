#include <iostream>
#include <string>

#include "FractalCreator.h"


int main()
{
	constexpr int WIDTH = 800;
	constexpr int HEIGHT = 600;
	const std::string SAVE_DIR = "../Resource/bitmap";

	bool genCode = true;

#ifdef _DEBUG
	// generating a black image
	{
		Bitmap::Bitmap bitmap(WIDTH, HEIGHT, SAVE_DIR);
		genCode &= bitmap.write("black.bmp");
	}
	
	// generating an image with some basic colors
	{
		Bitmap::Bitmap bitmap(WIDTH, HEIGHT, SAVE_DIR);
		bitmap.setRegion(HEIGHT / 2, 0, HEIGHT / 2, WIDTH / 2, Color::RED);				// top left red
		bitmap.setRegion(HEIGHT / 2, WIDTH / 2, HEIGHT / 2, WIDTH / 2, Color::GREEN);	// top right green
		bitmap.setRegion(0, 0, HEIGHT / 2, WIDTH / 2, Color::BLUE);						// bottom left blue
		bitmap.setRegion(0, WIDTH / 2, HEIGHT / 2, WIDTH / 2, Color::GRAY);				// bottom right gray
		genCode &= bitmap.write("basics.bmp");
	}

	// check clear after a successful write
	{
		Bitmap::Bitmap bitmap(WIDTH, HEIGHT, SAVE_DIR);
		genCode &= bitmap.write("clear.bmp");
	}
#endif // _DEBUG

	//Mandelbrot
	{
		Bitmap::FractalCreator fractalCreator(WIDTH, HEIGHT, SAVE_DIR);
		fractalCreator.addRange(0.0, Color::BLACK);
		fractalCreator.addRange(0.3, Color::RED);
		fractalCreator.addRange(0.5, Color::YELLOW);
		fractalCreator.addRange(1.0, Color::WHITE);

		fractalCreator.addZoom(202, 295, 0.1);
		fractalCreator.addZoom(304, 312, 0.1);

		genCode &= fractalCreator.mandelbrot("mandelbrot_zoom.bmp");
	}

	if (genCode)
	{
		std::cout << "Bitmaps are successfully generated." << std::endl;
	}
	else
	{
		std::cout << "Something wrong with bitmap generation." << std::endl;
	}

	return 0;
}