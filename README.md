# rom_00

A prototyping workspace for learning and prototyping with SDL2 in the native C99 programming language.

## Project Goals

- Test prototyping ideas for isometric roguelikes
- Further practice programming in C99
- Learn the SDL2 library and ecosystem

## Learning Resources Used

While looking for learning resources on SDL2 I found a majority of resources used C++ where I would prefer to focus on a C standard at this time. These were some great resources I found for this purpose.

- C/SDL2
    - https://acry.github.io/SDL2-C.html
    - https://www.parallelrealities.co.uk/tutorials/
- Isometric Math
    - http://clintbellanger.net/articles/isometric_math/

## Assets Used

- Current font used, dungeon-grunge.ttf is found at https://fontstruct.com and the license for it is in the `\assets` folder.
- Tiles and menu screen images created by myself with paint.net

## Dependencies

Developed against Windows x64 .dll copies of project dependencies available in the `libs\x64` folder.

- [SDL2](https://www.libsdl.org)
    - [SDL2_Image](https://www.libsdl.org/projects/SDL_image/)
    - [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)

## Building

Built using GNU Makefiles, included makefile options described here.

- `make` -- Builds the default (`make build`) executable
- `make build` -- Builds the shareable executable (default) with optomization flags
- `make debug` -- Builds a debug executable with console output
- `make clean` -- Removes any built executables

## Todo

- Test build process in Linux environment
- PROTOTYPE! TEST! and LEARN!

## License

This project in its entirety is freely available under the GNU General Public License 3, see LICENSE for the full text.
