#include "Keybind.h"


void Keybind::tick()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[key])
        action();
}
Keybind::~Keybind()
{

}