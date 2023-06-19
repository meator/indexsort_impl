# Indexsort
Indexsort is a collection of algorithms implementing "index sort". These algorithms
sort the input and they return the permutation index.

For example, with this input:
```
values = {7, 45, 18, 33, 77, 96, 83, 80, 4, 51}
```

the result would be:
```
values = {7, 45, 18, 33, 77, 96, 83, 80, 4, 51}
index = {8, 0, 2, 3, 1, 9, 4, 7, 6, 5}
```

## Dependencies
- [Boost](https://www.boost.org/)
- [Doxygen](https://www.doxygen.nl/) (optional)
- [meson](https://mesonbuild.com/) (build system)

## Usage
A builddir must be set up first:
```sh
meson setup builddir
cd builddir
```

You can run benchmarks with:
```sh
meson test tests --benchmark -v
```

You must be in the builddir.

If you have doxygen, you can generate documentation with:
```sh
meson compile docs
```
The documentation will be located at `builddir/docs/html/index.html`
