# Quake II RTX

**Quake II RTX** is NVIDIA's attempt at implementing a fully functional 
version of Id Software's 1997 hit game **Quake II** with RTX path-traced 
global illumination.

**Quake II RTX** builds upon the [Q2VKPT](http://brechpunkt.de/q2vkpt) 
branch of the Quake II open source engine. Q2VKPT was created by former 
NVIDIA intern Christoph Schied, a Ph.D. student at the Karlsruhe Institute 
of Technology in Germany.

Q2VKPT, in turn, builds upon [Q2PRO](https://github.com/skullernet/q2pro), which is a 
modernized version of the Quake II engine. Consequently, many of the settings 
and console variables that work for Q2PRO also work for Quake II RTX.

This branch contains modified version Q2RTX extend with ability to save game frames and transform them to `.png` images.

## License

**Quake II RTX** is licensed under the terms of the **GPL v.2** (GNU General Public License).
You can find the entire license in the [license.txt](license.txt) file.

The **Quake II** game data files remain copyrighted and licensed under the
original id Software terms, so you cannot redistribute the pak files from the
original game.



## Submodules

* [zlib](https://github.com/madler/zlib)
* [curl](https://github.com/curl/curl)
* [SDL2](https://github.com/spurious/SDL-mirror)
* [stb](https://github.com/nothings/stb)
* [tinyobjloader-c](https://github.com/syoyo/tinyobjloader-c)
* [Vulkan-Headers](https://github.com/KhronosGroup/Vulkan-Headers)
* [glslang](https://github.com/KhronosGroup/glslang) (optional, see the `CONFIG_BUILD_GLSLANG` CMake option)
* [openal-soft](https://github.com/kcat/openal-soft)


## Image Saving Feature

To enable frame saving feature, build Q2RTX with `-DVKPT_IMAGE_DUMPS` preprocessor flag enabled:
```
mkdir build
cd build
cmake -DVKPT_IMAGE_DUMPS=1 ..
make
```
Before running `./q2rtx`, create `frames` directory in the same directory as the executable.
Then if you run Q2RTX, raw binary dumps of the frames will be saved in `frames/` directory.

To convert binary files to `*.png` images, first build converter program:
```
./build.sh
```
then run converter program:
```
./convert
```
