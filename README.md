# O_o_OOS

Reads and writes O_o text models, including include trees, source comments and model parts. This official Reader adapter is available as the CMake target `oor::oos`.
The standard Reader distribution exposes the adapter to JavaScript / WebAssembly and native Python.

## Build and test

Requires Git, CMake 3.25 or later and a C++20 compiler. A standalone build fetches a pinned revision of the in-memory Reader core.

~~~sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
~~~

For offline development, point `FETCHCONTENT_SOURCE_DIR_OOR_READER` at a compatible Reader checkout at configure time.
When a parent project already provides `oor::core`, add this repository with `add_subdirectory` and link
`oor::oos`. [Public C++ interface](include/oor/formats/oos.hpp) · [Round-trip example](tests/RoundTrip.cpp)

## Use from the standard Reader

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
from oo_reader import read_model

deck = read_model("input.oos", strict=True)
deck.write_model("output.oos")
~~~

[Reader documentation](https://jcdulas.github.io/O_o_Reader/) · [MIT license](LICENSE)
