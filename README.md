# O_o_OOS

Reads and writes O_o text models, including include trees, source comments and model parts. This official Model adapter is available as the CMake target `oor::oos`.
The standard Model distribution exposes the adapter to JavaScript / WebAssembly and native Python.

## Build and test

Requires Git, CMake 3.25 or later and a C++20 compiler. A standalone build fetches a pinned revision of the in-memory model core.

~~~sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
~~~

For offline development, point `FETCHCONTENT_SOURCE_DIR_OOR_READER` at a compatible Model checkout at configure time.
When a parent project already provides `oor::core`, add this repository with `add_subdirectory` and link
`oor::oos`. [Public C++ interface](include/oor/formats/oos.hpp) · [Round-trip example](tests/RoundTrip.cpp)

## Use from the standard Model

**JavaScript / WebAssembly**

~~~javascript
const deck = reader.readModel("/work/input.oos", { strict: true });
try {
  deck.writeModel("/work/output.oos");
} finally {
  deck.delete();
}
~~~

**Python / native C++**

~~~python
from oo_model import read_model

deck = read_model("input.oos", strict=True)
deck.write_model("output.oos")
~~~

[Model documentation](https://jcdulas.github.io/O_o_Model/) · [MIT license](LICENSE)
