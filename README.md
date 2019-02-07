
<h1 align="center">PBR Playground</h1>

<img src="https://github.com/Gabrielnero000/PBR-Playground/blob/master/gallery/first.png?raw=true">

Hey, welcome! 

This project is the register of my Physical Based Rendering (PBR) study, experiences and interesting stuffs. I'm starting this repository with almost any knowledge in this area, so this will be a long way down in the PBR's world. I hope you enjoy this travel and fell free to question, comment and  add knowledge! 

This repository is also for educational purposes in the class "Special Topics in Computing" ministered by Dr. Christian Azambuja Pagot in the  Federal University of Paraíba.

"_The cosmos is all that is, or ever was, or ever will be. Come with me_." - Carl Sagan.

## Structure
This project is subdivided in sections,   
which are listed below, wich are in constant grown (fell free to give a feedback :D ) and new sections are added constantly.

* [But What is PBR?](https://github.com/Gabrielnero000/PBR-Playground#but-what-is-pbr) - A (really basic) introduction of what is PBR.
* [Base Architecture for a Ray Tracer](https://github.com/Gabrielnero000/PBR-Playground#base-architecture-for-a-ray-tracer) - The first sketch to an object-oriented development.
* [Cameras](https://github.com/Gabrielnero000/PBR-Playground#cameras) - Camera models that creates the most different lookings.
	* [Orthogonal Camera](https://github.com/Gabrielnero000/PBR-Playground#orthogonal-camera)
	* [Perspective Camera](https://github.com/Gabrielnero000/PBR-Playground#perspective-camera)
* [Primitives](https://github.com/Gabrielnero000/PBR-Playground#primitives) - Basic objects that can be rendered.
	* [Spheres](https://github.com/Gabrielnero000/PBR-Playground#spheres)
	* [Triangles](https://github.com/Gabrielnero000/PBR-Playground#triangles)
* [Gallery: Images of Experiments](https://github.com/Gabrielnero000/PBR-Playground#gallery-images-of-experiments) - Don't know what PBR can do? Check this out!

---

## But What is PBR?
Since the prehistoric vector/CRT displays until actual pixel-based monitors with super resolutions, generate realistic images was (and still is) the main goal of the Computer Graphics (CG) research. From the efforts of lots of great professionals, today we have basically two ways to generate high quality images: **rasterization-based** methods and **physical-based** methods. The first one is the most popular method for real time rendering, specially games. Those techniques convincent results and it's computationally **fast**, but the thing is: if you look for a rasterization-generated image it's easy to know that it's an CG image. That's were physical-based techniques shines.

**Physical Based Rendering** (**PBR**) it's able to generate images extremely realistic images (check the [gallery](https://github.com/Gabrielnero000/PBR-Playground#gallery-images-of-experiments)) and it's relativelly easy to implemment, at cost of a lot of computer processing power. 

In the PBR's world the most popular techniques are **ray-based** techniques, specifically **Ray Tracing** and **Path Tracing**. Both tries to simulate the phenom of the human vision using rules from physics (that's were the "physical based" comes from).

So, to understand  how those algorithms works, we need to understand how the vision works. Every **eletromagnetic** phenom is essencially a wave (Wi-FI, TV and radio signal, light...) wich haves a **wavelength**, wich can go from a few picometeres (Gamma rays and X rays) to even hundreds of meters (AM radio waves). We are intrested in a particular interval in that range: between 370 nanometers and 750 nanometers. That's the interval that we call **Visible Spectrum of Light**, i.e. the wavelenght interval that we can see.

When the light rays colide with an object, that object absorbs part of the frequencies (part of the light, basically) and reflects the rest of it as rays as well. If the reflected rays colide with our eye, they stimulate special cells (cones and rods). The interpretation by the brain of that stimulus is what we understand as **color**. With that color information our brain builds an **image** as we know.

So, instead of shot infinite rays from every light source, Ray and Path Tracing essencially **trace back the  rays** from the eye, to the objects and to the light (that's were the "tracing" comes from) using accurate physical models.

## Base Architecture for a Ray Tracer
Here is a basic UML calass diagram that can be used as base for our Ray Tracer. Gradually it will be expanded as we add new features, so it's important to have a robust architecture in the begining. I'll be using **C++** to implementation, since we need fast computation and object-oriented features (inheritance, polymorphism, function overload, etc). I'm using the [**GLM**](https://glm.g-truc.net/0.9.9/index.html) library to abstract some vector representation and operations (for now). So there it is:

<img src="https://raw.githubusercontent.com/Gabrielnero000/PBR-Playground/master/svgs/Render-UML.png">

As we can see, we have intially four classes and two abstract classes:
 * **Class Ray** - represents the most basic element in a Ray Tracer: a **ray**. A ray, wich is a straight line, can be expressed as <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$f(t)&space;=&space;O&space;&plus;&space;tD$" title="$f(t) = O + tD$" />, were <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$O$" title="$O$" /> is **the ray's origin**, <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$D$" title="$D$" />is the **ray's direction** and <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$t$" title="$t$" /> is a real number. Variating <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$t$" title="$t$" /> we have **any point in the straight**.
 * **Class Primitive** - abstract class that represents a **primitive**. A primitive is basically anything that a ray can colide with. Most common are triangles, shperes, planes, quadrics, meshes (which just lots of triangles) and so on. Since every primitive have a diferent **intersection routine**, the ``intersect`` function must be ``virtual``.
 * **Class Output** - used to output the image. Holds a buffer feeded during the render and transforms it to fit the **PPM's format**.
 * **Class Scene** - stores all primitives in the scene. Have a intersection function that just basically calls every primitive intersection function.
 * **Class Camera** - abstract class to represents the camera. Since there is lots of camera models (orthographic, perspective, with/without lens) the routine to generate rays is variable. So the ``getRay`` function must be ``virtual`` as well.
 * **Class Render** - that's were the magic happens. The render loop is essecially two nested for loops (using output's resolution), were the rays are shooted from the camera to the scene and getting the colision information.

So, the Ray Tracing algorithm is basically generate rays from the camera and test if it's colide with some primitive then generate another ray from the primitive to a light source. If both colisions happen, the primitive is visible and we store informations about that colision (colision point, normal, material information and so on) to calculate the final output (today the pixel color). Looks simple, right? Well, this will become madness soon! :)


## System Specs
Diferent machines can generate diferent performance results, is necessary to have a reference system to normalize all benchmarks. That system is my actual notebook: a Dell G7 with the follow specs:
* **Processor**: i7 8750H 6 cores / 12 Threads with 2.2 ~ 4.1 Ghz clock and 9 MB cache.
* **RAM**: 8 GB DDR4 with 2666 Mhz clock.
* **VGA**: Nvidia GTX 1050 Ti (not used yet).

All experiments was done with the notebook in AC to maximize performance.

## Cameras
Soon :)

### Orthogonal Camera
Soon :)

### Perspective Camera
Soon :)

## Primitives
Soon :)

### Spheres
Soon :)

### Triangles
As you may know, a triangle in <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;\fn_phv&space;$R^3$" title="$R^3$" /> is a 2D structure represented by three distinct points (called **vertex**) <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$v_1,&space;v_2,v_3&space;\in&space;R^3$" title="$v_1, v_2,v_3 \in R^3$" />. Triangles are the most common primitive because they are used to form complex **meshes** and objects, so lots of efforts was (and still is) made to create algorithms that can calculate a ray-triangle intersection eficiently. Two of those algorithms are implemented here: 

* *Fast, Minimum Storage Ray/Triangle Intersection* (Möller, T.; Trumbore, B.)
* *Fast Triangle Intersection in RTRT* (Section 7.1 of the Ingo Wald's doctorate degree thesis)

Both algorithms uses baricentric coordinates, witch is a way to represent any point inside of a triangle in terms of  <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$P&space;=&space;\alpha&space;v_1&space;&plus;&space;\beta&space;v_2&space;&plus;&space;\gamma&space;v_3$" title="$P = \alpha v_1 + \beta v_2 + \gamma v_3$" /> with <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$0&space;\leq&space;\alpha,&space;\beta,&space;\gamma&space;\leq&space;1$" title="$0 \leq \alpha, \beta, \gamma \leq 1$" />  and <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$\alpha&space;&plus;&space;\beta&space;&plus;&space;\gamma&space;=&space;1$" title="$\alpha + \beta + \gamma = 1$" />, to calculate the intersection. 

The Möller's algorithim solves the equation:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$$T(u,v)&space;=&space;(1&space;-&space;\beta&space;-&space;\gamma)v_1&space;&plus;&space;\beta&space;v_2&space;&plus;&space;\gamma&space;v_3$$" title="$$T(u,v) = (1 - \beta - \gamma)v_1 + \beta v_2 + \gamma v_3$$" />
<p>

and, as <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$T(u,v)&space;=&space;O&space;&plus;tD$" title="$T(u,v) = O +tD$" />, i.e. the ray itselfs, we can rearrange the terms to the linear system:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$$&space;\begin&space;{bmatrix}-D,\space\space&space;v_2&space;-&space;v_1,\space\space&space;v_3&space;-&space;v_1&space;\end{bmatrix}&space;\begin{bmatrix}&space;t&space;\\[0.3em]&space;\beta&space;\\[0.3em]&space;\gamma&space;\end{bmatrix}&space;=&space;O&space;-&space;v_1&space;$$" title="$$ \begin {bmatrix}-D,\space\space v_2 - v_1,\space\space v_3 - v_1 \end{bmatrix} \begin{bmatrix} t \\[0.3em] \beta \\[0.3em] \gamma \end{bmatrix} = O - v_1 $$" />
<p>

The Wald's algorithm project the triangle in a 2D plane (the <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$XY$" title="$XY$" /> plane, for example) to do all calculations in 2D. So, similar to Möller algorithm, it solves

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$$&space;H'&space;=&space;\alpha&space;v_1'&space;&plus;&space;\beta&space;v_2'&space;&plus;&space;\gamma&space;v_3'&space;$$" title="$$ H' = \alpha v_1' + \beta v_2' + \gamma v_3' $$" />
<p>

where <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$v_1',&space;v_2',&space;v_3'$" title="$v_1', v_2', v_3'$" /> are the vertex in the 2D plane and $H'$ is the hitpoint in the 2D plane as well. Rearraging the terms we have:
$$
\beta = \frac{b_xh_y - b_yh_x}{b_xc_y - b_yc_x}, \gamma = \frac{h_xc_y - h_yc_x}{b_xc_y - b_yc_x}
$$
where $b = v_3' − v_1' , c = v_21 − v_1'$ and $h = H' − v_1'$. Wall also provide a `struct` to store all precomputable values (normal and edges) to accelerate the calculation, witch cause an higher memory use (9 `floats` and 1 `int`, totalizing additional 40 bytes per triangle) in comparation to Möller's algorithm. But witch one is better? Let's find out.

In my benckmark, i've runned both algorithms in simplified conditions (single-thread, no C++ advanced features, no cache optimization) in seven render cases: 1, 5, 10, 50, 100, 500 and 1000 triangles. Every case was runned five times and the medium value was taken to ensure stability and constancy. Here is the results:

As we can see, the Wald's algorithm can be 50% faster in the simplests cases (1 and 5 triangles) to almost a twice faster in most complexes cases (500 and 1000 triangles) than Möller's algorithm, which definitely is a huge difference, but the memory use can be a problem depending on the system: 1000 triangles 40 KB more to be rendered. So I'm taking Wald as default, but is good to be noticed that the memory use can blow up.

## Gallery: Images of Experiments
PBR is about genereate beautiful CG images, so here they are! The images in this section was generated using my code or existing PBR softwares. I hope you appreciate it!

<p align="center">
    <img src="https://github.com/Gabrielnero000/PBR-Playground/blob/master/gallery/first.png?raw=true" alt>
    <em>My first PBR render. Used Blender Clycles to genereate it.</em>
</p>

<p align="center">
    <img src="https://github.com/Gabrielnero000/PBR-Playground/blob/master/gallery/earth.png?raw=true" alt>
    <em>The Earth with Blender Clycles.</em>
</p>
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTE3NDgzOTg0MzcsLTIwODU2MDIyNzcsLT
IwODU2MDIyNzcsODc4OTM1MDQyLDEzNzY2MTY2NDUsOTMwNTQ1
Mjg3LC0xMjE0NjU3MTMyLDE4NTkzMTcxMjMsMTQxMDA1NzQ0Ny
wtNDU2ODI5MDYyLC0xMTEzMjM0MTM1LC03MjY1NzU4NzAsNjQy
NjY4MjQzLC0xMjE1Mzk5Nzc0LDQwNjY1NTc4MiwtMTEyNTgzMz
I4OCwxOTUxNzgyMjksMTgzMTYzNjY1Myw1NTg4NzY1NjksLTkx
ODg3MDA0NV19
-->