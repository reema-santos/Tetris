#include "IO.h"

static SDL_Surface* mScreen;
static Uint32 mColours [COLOR_MAX] = {0x000000ff,					// Colors
                               0xff0000ff, 0x00ff00ff, 0x0000ffff,
                               0x00ffffff, 0xff00ffff, 0xffff00ff,
                               0xffffffff};

IO::IO () {
    InitGraph();
}

void IO::DrawRectangle (int pX1, int pY1, int pX2, int pY2, enum colour pC) {
    boxColor(mScreen, pX1, pY1, pX2, pY2-1, mColours[pC]);
}

void IO::ClearScreen () {
    boxColor(mScreen, 0, 0, mScreen->w - 1, mScreen->h - 1, mColours[BLACK]);
}

int IO::GetScreenHeight () {
    return mScreen->h;
}

int IO::InitGraph () {
    const SDL_VideoInfo* info;
    Uint8 video_bpp;
    Uint32 videoflags;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Couldn't initialise SDL: %s\n",SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);

    info = SDL_GetVideoInfo();
    if ( info->vfmt->BitsPerPixel > 8 ) {
		video_bpp = info->vfmt->BitsPerPixel;
	} else {
		video_bpp = 16;
	}
	videoflags = SDL_SWSURFACE | SDL_DOUBLEBUF;
	
	// Set 640x480 video mode
	if ( (mScreen=SDL_SetVideoMode(640,480,video_bpp,videoflags)) == NULL ) {
		fprintf(stderr, "Couldn't set %ix%i video mode: %s\n",640,480,SDL_GetError());
		return 2;
	}
    return 0;
}

// Checks for pending events
int IO::Pollkey () {
    SDL_Event event;
    // While condition takes a pointer to an SDL_Event
    // Returns 1 (true) if an event was found or 0 (false) if no events are pending
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: // Triggered when a keyboard key is pressed
                return event.key.keysym.sym;
                // keysym.sym indicates which key was pressed
            case SDL_QUIT: // Triggered when used tries to close window
                exit(3);
        }
    }
    return -1;
}

int IO::Getkey () {
    SDL_Event event;

    while (true) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN) break;
        if (event.type == SDL_QUIT) exit(3);
    }

    return event.key.keysym.sym;
}

int IO::IsKeyDown (int pKey) {
    Uint8* mKeytable; // pointer to an unsigned 8-bit integer
    int mNumkeys;
    SDL_PumpEvents(); // Gathers pending input information from hardware
    mKeytable = SDL_GetKeyState(&mNumkeys); 
    // SDL_GetKeyState returns a pointer to an array (size is stored in numkeys)
    return mKeytable[pKey];
}

void IO::UpdateScreen () {
    SDL_Flip(mScreen);
}