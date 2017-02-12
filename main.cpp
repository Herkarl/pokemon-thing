//#define DEBUG

#include <iostream>
#include <chrono>
#include <thread>
#include "state.h"
#include "graphics.h"
int main(int argc, char** argv) {

	if(argc < 3){

		std::cout << "Usage: " << argv[0] << " board_height board_width [frames per second][number of frames]" << std::endl;
		return 1;

	}

	int height = std::stoi(argv[1]);
	int width  = std::stoi(argv[2]);
	double speed = 60;
	int frames = int(1e6);

	if(argc > 3) speed = std::stoi(argv[3]);
	if(argc > 4) frames = std::stoi(argv[4]);

	graphics window(height,width);
	state simulation;
	simulation.init(height,width);

	window.draw(simulation);

	while(frames --> 0){

		simulation.step();

		if(!window.draw(simulation)) break;

		std::this_thread::sleep_for(std::chrono::microseconds(int(1e6/speed)));
	}

	return 0;
}