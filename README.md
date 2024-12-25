# FeedTheBeast
A Murder Drones fangame, written in C++ using SFML

# Dependencies
FeedTheBeast relies on [Simple and Fast Multimedia Library](https://www.sfml-dev.org/). Install it, either through your distro's package manager, or by building it from source, before attempting to build FeedTheBeast. Make sure you're installing version 3.0.0 or later, because older versions do not work (some distro package managers have not yet updated to include the latest version, in which case you'll have to build yourself).

# Compilation/Installation guide
This project uses `meson`, a build tool that automatically handles compilation and linking. 

In order to build FeedTheBeast and run it, you must ensure that you have `meson` (and all its dependencies, notably `ninja`) on your system. It is recommended that you do this through your distro's package manager, but it can also be done through `pip`. See [Meson's installation page](https://mesonbuild.com/Getting-meson.html) for more information.

Once you have Meson installed, clone and `cd` into this repository, then run `meson setup builddir` to create a build directory on your system. Once it's there, `cd` into it and run `meson compile` or `ninja` (either one works, `ninja` is faster, but `meson compile` must be used if you are using a different backend. If you don't know what backend you're using, assume you're using `ninja`). After the project is finished building, you'll see the binary in the build directory.  
