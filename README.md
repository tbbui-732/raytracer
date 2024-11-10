# Ray Tracer

## Description
Implementation of a basic ray tracer technique to generate realistic images on the CPU (followed along from the text: Ray Tracing in One Weekend).
Features:
   - Anti-aliasing
   - Different material types
     - Diffuse (matte)
     - Metal/mirror (with fuzzy reflection)
     - Dielectrics (glass) using Schlick's approximation
   - Positionable camera
   - Defocus blur

## Rendered Images
A sphere shaded by its normal vector, in all of its un-antialiased goodness.

![first sphere](https://github.com/tbbui-732/raytracer/blob/main/images_png/sphere-background.png)

A glass sphere with an airbubble inside of it rendered with Schlick's approximation algorithm.

![glass sphere with schlick approximation](https://github.com/tbbui-732/raytracer/blob/main/images_png/schlick-spheres.png)

The same spheres before but the camera is distanced away.

![positionable camera](https://github.com/tbbui-732/raytracer/blob/main/images_png/far-spheres.png)

A bunch of spheres rendered everywhere. This one took 8-10 hours to render!

![final scene](https://github.com/tbbui-732/raytracer/blob/main/images_png/final-scene.png)

## Takeaways
Ray tracing is quite an amazing technique. The idea behind ray tracing is quite simple, but how those rays interact with 
different objects is what made this project so challenging. 

Furthermore, I've learnt of the importance of computing on the CPU vs. the GPU. The final scene I rendered took about 8-10 hours.
Many modern games with ray-tracing have to re-render a scene many times. So, unless you enjoy playing games with a blazingly fast 2 frames per day,
having a GPU would take care of the graphics pipeline much faster.
