<br/>
<h1>
<p align="center">
    <img src="icon.jpg" alt="Logo" width="110" height="110">
    <br>Mather
<div align="center">

[![GitHub Actions](https://github.com/carbone13/mather/actions/workflows/cmake.yml/badge.svg)](https://github.com/carbone13/mather/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

</div>

</h1>
  <p align="center">
    A library to draw 2D primitives shapes quickly and efficiently.
    <br/>
    </p>
</p>
<p align="center">
  <a href="#about-the-project">About The Project</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#examples">Examples</a> • 
  <a href="#dependencies">Dependencies</a> 
</p>  

## About The Project

Mather is a library that allow you to quickly create a windows and to draw simple 2D Shapes.

Currently supporting :

- Line
- Poly Line
- Circle
- Rect
- Polygon

## How to Use

### Importing

Add the library as a dependencies, the most elegant way is to clone it as a git submodule :

```sh
git submodule add https://github.com/Carbone13/mather.git
git submodule update --init --recursive
```

Then add it to your CMakeLists.txt and link to your executable :

```cmake
add_subdirectory(path/to/mather)
...
target_link_libraries(your_project mather)
```

### Usage

```cpp
#include "mather.hpp"

int main()
{
    mather::Context ctx = mather::Context(WIDTH, HEIGHT); // Create the context
    
    // your draw loop
    {
        ctx.clear();
        ctx.line(-620, -350, 620, 350, 3.0f, LineCap::Round, colors::white);
        ctx.circle(550, -200, 100, colors::cyan);
        ctx.roundedRect(700, 500, 80, 50, 10, colors::olive);
        
        // now draw with your favorite api
        drawPixels(WIDTH, HEIGHT, ctx.getInternalBuffer()); 	
    }
	
    return 0;
}
```

## Examples

See [main.cpp](demo/main.cpp) in [demo](demo/) for an integration with GLFW and OpenGL.

TODO Example with more backends

## Dependencies

This project depend on 2 libraries :

- [GLFW](https://github.com/glfw/glfw) for windowing and creating the surface
- [AGG](https://github.com/Carbone13/agg) for sub-pixel anti-aliasing
