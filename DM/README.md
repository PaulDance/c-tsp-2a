### Compilation

This project uses the CMake build system along with the Clang compiler. In
the current directory, run `cmake -DCMAKE_C_COMPILER=/usr/bin/clang -B bin`
to create the build files in the "bin" directory which can be something else
of your choice of course. Then, to actually compile a certain target, run
`cmake --build bin --target <target-name>`.
If you don't have Clang installed or don't want to install it, you may use
gcc or cc but you might have to change the warning options activated in the
CMakeLists.txt file.

### Running tests

Compile with `cmake --build bin --target tests` and then run `./bin/tests`.
