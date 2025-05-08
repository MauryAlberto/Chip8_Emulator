#include "Chip8.hpp"
#include "Platform.hpp"
#include <chrono>
#include <iostream>


int main(int argc, char** argv)
{
	// Check for proper number of command line arguments
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
		std::exit(EXIT_FAILURE);
	}

	int videoScale = std::stoi(argv[1]);// Scale factor for screen rendering
	int cycleDelay = std::stoi(argv[2]);// Delay between CPU cycles in milliseconds
	char const* romFilename = argv[3];// Path to the ROM file

	Platform platform("CHIP-8 Emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

	// Instantiate the Chip8 emulator and load the ROM into memory
	Chip8 chip8;
	chip8.LoadROM(romFilename);

	// Calculate the pitch (bytes per row) of the video memory
	int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;

	// Used to track when to execute theh next CPU cycle
	auto lastCycleTime = std::chrono::high_resolution_clock::now();
	bool quit = false;// Flag to check when to exit the loop

	// Main emulation loop
	while (!quit)
	{
		// Poll input and update the emulator's keypad state
		quit = platform.ProcessInput(chip8.keypad);

		// Get the current time
		auto currentTime = std::chrono::high_resolution_clock::now();

		// Compute the time difference in milliseconds between current and last cycle
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

		// Only run a new cycle if enough time has passed
		if (dt > cycleDelay)
		{
			lastCycleTime = currentTime;// Update the last cycle time

			chip8.Cycle();// Execute one CHIP-8 CPU cycle

			platform.Update(chip8.video, videoPitch);// Render the display to the screen
		}
	}

	return 0;
}