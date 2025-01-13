# FeedTheBeast
A Murder Drones fangame, written in C++ using SFML

# Dependencies
FeedTheBeast relies on [Simple and Fast Multimedia Library](https://www.sfml-dev.org/). You may use a systemwide installation of SFML, but this project also provides SFML as a Git submodule in case you are unable (or do not want to) install SFML systemwide. Instructions on how to use a systemwide SFML install and how to use the Git subproject are provided below (using a systemwide SFML install will make the compile time of this project much faster).

(LINUX ONLY) If you intend to use the Git submodule for SFML, you need to install all of SFML's dependencies, which allow SFML to be compiled. Here's what you need:
- `libxrandr-dev`
- `libxcursor-dev`
- `libudev-dev`
- `libflac-dev`
- `libvorbis-dev`
- `libgl1-mesa-dev`
- `libegl1-mesa-dev`
- `libdrm-dev`
- `libgbm-dev`
(I imagine that the non-dev versions of all of these packages work as well). Use your distro's package manager to install all of these. (On Windows, I'm pretty sure SFML uses packages that are shipped with the OS, so you don't need to install anything additional).

Finally, make sure you have both Meson and CMake installed and available in your PATH. 

# Compilation/Installation guide
This project uses `meson`, a build tool that automatically handles compilation and linking.

In order to build FeedTheBeast and run it, you must ensure that you have `meson` (and all its dependencies, notably `ninja`) on your system. It is recommended that you do this through your distro's package manager, but it can also be done through `pip`. See [Meson's installation page](https://mesonbuild.com/Getting-meson.html) for more information.

## If you have a systemwide SFML install
- Make sure Meson, CMake, and SFML are all installed
- Clone and `cd` into this repository
- Run `meson setup builddir -DuseSystemSFML=true`
- Run `cd builddir`
- Run `meson compile`
- The executable should now be in the build directory. To run it, run `./FeedTheBeast`

## If you want to use the SFML submodule
- Make sure Meson, CMake, and SFML are all installed
- Clone and `cd` into this repository
- Run `meson setup builddir`
- Run `cd builddir`
- Run `meson compile`
- The executable should now be in the build directory. To run it, run `./FeedTheBeast`

# Additional Notes
As of right now, the executable requires the user to create a `level.txt` file in the same directory as the executable in order for the exeuctable to run. This can be done with `echo "10.0 -0.5 10.0 0.5" > level.txt` in Bash while you're inside the `builddir`, for example. This will likely be changed in the future. 
