# MiniRT

In 2021 I started learning programming. At the programming school 42 School we had our first graphics project called **MiniRT**. The goal of the project was to implement the simplest version of ray tracing on the CPU using the **MinilibX** library, which allowed setting the color of a single pixel in the framebuffer. The project originally ran only on macOS.

GIF BEFORE and GIF AFTER

In 2025 I decided to return to this project and see how much it could be improved while keeping the original constraints — all computations must happen strictly on the CPU, and no external rendering libraries or engines can be used for any part of the project.

The first step was to make the project cross-platform. I ported it to SDL to simplify running it on macOS and Linux, and used the standard **windows.h** API for Windows.

To run the project on macOS or Linux you first need to install the SDL development kit:

`sudo  apt  install libsdl2-dev`  
`brew install sdl2`

Originally the project was built using **Make**, but the build process took about 15 seconds. I replaced it with a **unity build**, which reduced compilation time to about half a second.

To build the project you can use one of the `unity_build*.sh/bat` scripts. However, I know that many people prefer not to run scripts, so I will also provide the build commands directly here:

```
MacOS Build Command
clang -Werror -Wall -Wextra -std=c11 -march=native -O3 `sdl2-config --cflags` -DRT_LINUX -DMAC_OS -DTHREADS_MAX=10 srcs/main.c -lm `sdl2-config --libs` -o MiniRT
```  
```
Linux Build Command
clang -Werror -Wall -Wextra -std=c11 -march=native -O3 `sdl2-config --cflags` -DRT_LINUX -DTHREADS_MAX=12 srcs/main.c -lm `sdl2-config --libs` -o MiniRT
```  
```
Windows Build Command
clang -Werror -Wall -Wextra -O3 -std=c11 -march=native -DRT_WIN32 -DTHREADS_MAX=12 srcs/main.c -luser32 -lgdi32 -lkernel32 -o MiniRT.exe
```  

Compared to the original version, I removed thread recreation. Now everything runs in a single thread pool that is recreated only when a next scene is opened. The argument that controls the number of threads in the build configuration is: `THREAD_MAX`.

After that, I eliminated scattered geometry primitives collection that were spread across different memory pages because of strategy of allocation memory . All `malloc` calls were replaced with an **arena allocator** interface and an only dynamic allocation wrapped in an arena. As a result, all primitives that every ray from every pixel iterates over are stored in one continuous, cache-friendly memory layout. This also removed many unnecessary allocations and deallocations — the arena is simply cleared when switching scenes and then filled with new objects.

I also attempted to rewrite all math operations using SIMD, but benchmarks showed a performance regression. Since the goal was to make the project faster, I checked the generated assembly on Compiler Explorer (Godbolt) and noticed that the compiler was already generating better SIMD instructions than my manual implementation.

However, I realized that if functions are located far apart in memory, calling them may result in jumping to code that has already been evicted from the TLB cache or resides on another memory page, which negatively affects the CPU prefetcher. To solve this, I moved all math operations into headers and marked them as force inline. This improved performance by roughly fifteen percent, now all operations are prefetched more optimally and compile into efficient SIMD code with `-O3` optimization.

But that still was not enough. Rendering a scene with 3–4 thousand triangles and three directional light sources still took around 14 seconds.

At this point it was time for algorithmic improvements. I studied how BVH trees work and implemented the simplest version of it. During this process planes, spheres, and cylinders were removed, leaving only triangles because building AABB for them was the easiest, but the complexity of ray hit finding improved from linear to logarithmic.

Scenes that were previously static and required tens of seconds to render were now rendered in 20–30 milliseconds. Because of that improvement I added anti-aliasing (four jittered samples using an accumulation approach) and reflections (up to four ray bounces)

For a speed comparison:
`GIF BEFORE` `GIF AFTER`

Camera controls are relatively free:
-   **WASD** — movement in space
-   **Arrow keys** — camera rotation (works correctly only if the initial view direction is aligned with the Z axis; the gimbal lock issue was not addressed because it was outside the scope of performance improvements)

I also found an article about software rendering of debug text, which inspired the idea of adding a menu. To visually separate menu and scene states, I also implemented a very simple blur effect that activates when the menu is open.

`MENU SCREEN`

All scenes shown in the menu are files located in the `assets` directory. This directory should not be removed or renamed. Adding new content there is currently difficult because only the original scene file format from the initial project is supported. Parsing `.obj` files was not implemented.
Menu navigation:
-   **ESC** — open the menu
-   **ESC in menu** — exit the application
-   **Up/Down arrows** — navigate the menu
-   **Enter** — load the selected scene.
