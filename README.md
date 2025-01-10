# FeedTheBeast
A Murder Drones fangame, written in C++ using SFML

# Dependencies
FeedTheBeast relies on [Simple and Fast Multimedia Library](https://www.sfml-dev.org/), which is included as a Git submodule.
After checking out the repository, run `git submodule update --init` to pull SFML's source code.

Finally, make sure you have both Meson and CMake installed and available in your PATH.

On Linux, SFML requires at least the following libraries (might be a few others too):
- `libvorbis`
- `libflac`


# Compilation/Installation guide
This project uses `meson`, a build tool that automatically handles compilation and linking.

In order to build FeedTheBeast and run it, you must ensure that you have `meson` (and all its dependencies, notably `ninja`) on your system. It is recommended that you do this through your distro's package manager, but it can also be done through `pip`. See [Meson's installation page](https://mesonbuild.com/Getting-meson.html) for more information.

Once you have Meson installed, clone and `cd` into this repository, then run `meson setup builddir` to create a build directory on your system. Once it's there, `cd` into it and run `meson compile` or `ninja` (either one works, `ninja` is faster, but `meson compile` must be used if you are using a different backend. If you don't know what backend you're using, assume you're using `ninja`). After the project is finished building, you'll see the binary in the build directory.

SFML needs CMake in order to compile - if you're seeing errors related to CMake, make sure it's installed and up-to-date.

Quick reference:
- Clone the repository
- `git submodule update --init` to pull SFML
- Install CMake and Meson
- (Optional) Install dependencies (Vorbis and FLAC)
- `meson setup builddir && cd builddir`
- `meson compile`
- `./FeedTheBeast`
