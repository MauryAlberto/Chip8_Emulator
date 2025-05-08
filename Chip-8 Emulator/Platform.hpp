#pragma once// Ensures the header is only included once during compilation

#include <cstdint>
#include <SDL2/SDL.h>
#include <glad/glad.h>

// Platform class manages window creation, rendering, OpenGL context, and input handling
class Platform
{
	// Allow Imgui class to access private members of Platform
	friend class Imgui;

public:
	// Constructor: Initializes SDL, creates a window and OpenGL context, sets up rendering
	Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
	// Destructor: Cleans up SDL and OpenGL resources
	~Platform();
	// Updates the screen with new framebuffer data
	void Update(void const* buffer, int pitch);
	// Processes keyboard input and maps key states into the keys array
	bool ProcessInput(uint8_t* keys);

private:
	SDL_Window* window{};// Pointer to the SDL window
	SDL_GLContext gl_context{};// OpenGL rendering context created by SDL
	GLuint framebuffer_texture;// OpenGL texture used as a framebuffer for rendering pixels
	SDL_Renderer* renderer{};// SDL renderer for drawing to the window
	SDL_Texture* texture{};// SDL texture used for blitting pixel data to the screen
};