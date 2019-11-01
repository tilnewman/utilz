All the c++17 I'll never have to re-write again!


The goal is to keep the "utilz" directory:
 * flat (no sub-directories)
 * clean (hpp/cpp ONLY) (no hidden git/clang/cmake/etc)
 * dependency free (all you need is already there)
 * cross-platform (at least the big three: msvc/linux/macos)
 * open-source (simple and permissive like MIT or Beerware)
 * tested (cmake, make, ctest) or (open the folder in VisualStudio and RunAllTests)
 
So you can use any of it by simply:
 * #include <utilz/...>
 * copying individual headers
 * copying the whole damn utilz folder
 * cmake add_subdiretory(utilz)

-and everything just works.
zTn