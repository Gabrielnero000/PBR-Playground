
<h1 align="center">PBR Playground</h1>

<img src="https://github.com/Gabrielnero000/PBR-Playground/blob/master/gallery/first.png?raw=true">

Hey, welcome! 

This project is the register of my Physical Based Rendering (PBR) study, experiences and interesting stuffs in the development process of a PBR engine. I'm starting this repository with almost any knowledge in this area, so this will be a long way down in the PBR's world. I hope you enjoy this travel and fell free to question, comment and  add knowledge! Don't miss the [gallery section](https://github.com/Gabrielnero000/PBR-Playground#gallery-images-of-experiments) to check what a PBR engine can do!

This repository is also for educational purposes in the class "Special Topics in Computing" ministered by Dr. Christian Azambuja Pagot in the  Federal University of Paraíba.

"_The cosmos is all that is, or ever was, or ever will be. Come with me_." - Carl Sagan.

## Current Features
* Render Core
	* Path Tracing
* Materials
	* Diffuse

* Cameras
	* Orthograpic Camera
	* Perspective (pinhole) Camera
	
* Primitives
	* Spheres
	* Triangles
		* *Fast, Minimum Storage Ray/Triangle Intersection* (Möller, T.; Trumbore, B.)
		* *Fast Triangle Intersection in RTRT* (Section 7.1 of the Ingo Wald's doctorate degree thesis)
	* Meshes
		* OBJ files

* Output
	* Images
		* PPM

## System Specs (for benchmark purposes)
Diferent machines can generate diferent performance results, is necessary to have a reference system to normalize all benchmarks. That system is my actual notebook: a Dell G7 with the follow specs:
* **Processor**: i7 8750H 6 cores / 12 Threads with 2.2 ~ 4.1 Ghz clock and 9 MB cache.
* **RAM**: 8 GB DDR4 with 2666 Mhz clock.
* **VGA**: Nvidia GTX 1050 Ti (not used yet).

## Discussions

This section is for educational purposes. All reports of experiments are listed here and later should be removed.

### Mark I - Triangles

<p align="center">
    <img src="https://raw.githubusercontent.com/Gabrielnero000/PBR-Playground/master/gallery/triangle.png" alt>
    <em>A simple triangle rendered</em>
</p>

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

where <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$v_1',&space;v_2',&space;v_3'$" title="$v_1', v_2', v_3'$" /> are the vertex in the 2D plane and <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$H'$" title="$H'$" /> is the hitpoint in the 2D plane as well. Rearraging the terms we have:

<p align="center">
<img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$$&space;\beta&space;=&space;\frac{b_xh_y&space;-&space;b_yh_x}{b_xc_y&space;-&space;b_yc_x},&space;\gamma&space;=&space;\frac{h_xc_y&space;-&space;h_yc_x}{b_xc_y&space;-&space;b_yc_x}&space;$$" title="$$ \beta = \frac{b_xh_y - b_yh_x}{b_xc_y - b_yc_x}, \gamma = \frac{h_xc_y - h_yc_x}{b_xc_y - b_yc_x} $$" />
<p>

where <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$b&space;=&space;v_3'&space;-&space;v_1'&space;,&space;c&space;=&space;v_2'&space;-&space;v_1'$" title="$b = v_3' - v_1' , c = v_2' - v_1'$" /> and <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$h&space;=&space;H'&space;-&space;v_1'$" title="$h = H' - v_1'$" />. Wall also provide a `struct` to store all precomputable values (normal and edges) to accelerate the calculation, witch cause an higher memory use (9 `floats` and 1 `int`, totalizing additional 40 bytes per triangle) in comparation to Möller's algorithm. But witch one is better? Let's find out.

In my benckmark, i've runned both algorithms in simplified conditions (single-thread, no C++ advanced features, no cache optimization) in seven render cases: 1, 5, 10, 50, 100, 500 and 1000 triangles. Every case was runned five times and the medium value was taken to ensure stability and constancy. Here is the results:

<p align="center" style="width: 100%;">
    <img src="https://raw.githubusercontent.com/Gabrielnero000/PBR-Playground/master/utils/Triangle%20Intersection%20Algorithms%20Performance.png" alt width="1280">
    <em>Möller vs Wald</em>
</p>

As we can see, the Wald's algorithm can be 50% faster in the simplests cases (1 and 5 triangles) to almost a twice faster in most complexes cases (500 and 1000 triangles) than Möller's algorithm, which definitely is a huge difference, but the memory use can be a problem depending on the system: 1000 triangles 40 KB more to be rendered. So I'm taking Wald as default, but is good to be noticed that the memory use can blow up.

### Mark II - Cameras
Two basic camera models are the orthograpic camera and the perspective (pinhole) camera. A orthograpic camera have the same direction in all samples but the origin of each sample is in a projection plane.

<p align="center">
    <img src="https://raw.githubusercontent.com/Gabrielnero000/PBR-Playground/master/gallery/ortho.png" alt>
    <em>Four spheres rendered with a orthograpic camera (darker means closer)</em>
</p>

It's util if the desired effect is a 2.5D view, but as it cannot provide the perspective distortion effect, have a limited use. 

A perspective camera have the same origin for all samples but the direction changes: is the vector from the origin to a point in the projection plane.

<p align="center">
    <img src="https://raw.githubusercontent.com/Gabrielnero000/PBR-Playground/master/gallery/perspective.png" alt>
    <em>Four spheres rendered with a pinhole camera (darker means closer)</em>
</p>

That makes possible to generate the perspective distortion (closer objects looks bigger). Both models can be generalized to be used in arbitrary positions.

### Mark III - Meshes

Meshes are just lots of triangles agrouped to form a complex object. So the ray-mesh intersection breaks into ray-triangles intersections. Is good to be noticed that only the CLOSEST HIT matters, to ensure a correct culling. To visualize each triangle that forms the object we can show the normal as a color:

<p align="center">
    <img src="https://raw.githubusercontent.com/Gabrielnero000/PBR-Playground/master/gallery/mesh.png" alt>
    <em>Monkey with normals</em>
</p>

Combine a mesh intersection routine with a arbitrary perspective camera, and we have a basic object viewer:

<p align="center">
    <img src="https://raw.githubusercontent.com/Gabrielnero000/PBR-Playground/master/gallery/perspective_mesh.png" alt>
    <em>Monkey with normals and arbitrary position camera</em>
</p>

### Mark IV - Path Tracing
Now it's time for a really childbirth. Instead of launch a single ray by each pixel, we will launch lots for a more accurate sampling of the scene. Those rays, if hit some object, can be scattered in some direction and with some attenuation (i.e. the surface can absorb part of the energy) until it's hit any surface that emmites energy. If the ray don't hit any emmisive surface, it does'nt carry any energy and does'nt contribuite to the final image (and you had waste computations). 

Every material can scatter rays in a particular way. Diffuse (perfectly matte) materials scatters the light equally in all directions. Perfect mirros scatters the light only and fully in the reflected direction of the incident ray. Glossy and metals scatters in some way between diffuse and mirror materials. That relation between the input/output ray is described by the *Bidirectional Refletance Distribuition Function*, a.k.a. BRDF.

The rays scatters from it's origin to a A surface, to a B surface, to a C surface and so on until it reachs the camera plane. We are going to trace back that path (that's where the *path tracing* thing cames from) from the camera to, at least, one light source. That algorithm have a recursive nature (an input ray was a output ray someware). This bring to us the beautiful *Render Equation*:

<p align="center">
<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{150}&space;$$L_o(\omega_r)&space;=&space;L_e(\omega_r)&space;&plus;&space;\int_\Omega&space;f_r(\omega_i,&space;\omega_r)L_i(\omega_i)cos(\theta)d\omega_i$$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{150}&space;$$L_o(\omega_r)&space;=&space;L_e(\omega_r)&space;&plus;&space;\int_\Omega&space;f_r(\omega_i,&space;\omega_r)L_i(\omega_i)cos(\theta)d\omega_i$$" title="$$L_o(\omega_r) = L_e(\omega_r) + \int_\Omega f_r(\omega_i, \omega_r)L_i(\omega_i)cos(\theta)d\omega_i$$" /></a>
</p>

Translating: the output energy of a reflected ray it's the sum of the emissive energy of the hitted surface and the contribuiton of all the rays comming from all directions in the upper hemysphere of the hit point. That contribution is the sum (integration!) of all possibles reflection proportions for every pairs of incident/reflected rays attenuated by the angle of incident. Sounds spooky and really is. That integral is analytically unsolvable, so we need to use numerical methods to solve it. Specifically, Monte Carlo integration.

The idea is SAH (simple as hell): evaluate the integral N times randomically, sum everything and divide by N. So, if the *randomically* occurs with a uniform distribuition, probabilistically we will approximate the integral value. The thing is: we need a lot of samples to reach a reasonable approximation.

So, we have two elements to play now:
* Number of bounces that each ray can suffer (our recursion-end condition).
* Number of samples.

Few bounces can make the scence darker (the ray may could reach a emissive surface if it had suffered more bounces). More bounces generate a more accurate result (in the real world, the rays suffers infinite bounces) but the computational cost will be higher.

Few samples per pixel generate noise (a bad approximation for the integral). More samples, again, generate a better approximation (again, in the real world occurs infinite sampling) but you'll need infinite time to compute it.

<p align="center">
    <img src="https://github.com/Gabrielnero000/PBR-Playground/blob/master/gallery/path_tracing.png?raw=true" alt>
</p>
<p align="center">
    <em>My first Path Traced image. A white diffuse box with a white squa</em>
</p>

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
eyJoaXN0b3J5IjpbLTE4ODA0ODYwNjgsOTM2Njc1NDY0LDkyMT
AwNDc0OSwtMTcwNDE0Mjg3MSwxMTM1OTIxMTE1LC0xNDQ3Mjk3
NDU3LDEwNzgwMzAxMTgsMTEwOTI2NTk0NiwtNDk4OTI4NTE1LC
0yNDAwNTkyMjUsMTA1NTA5OTIzNywxNjE1MDc1MTI1LC0xNjI5
NDM0NTY5LC0xMDQ5NDAzMzY0LC0yMDg1NjAyMjc3LC0yMDg1Nj
AyMjc3LDg3ODkzNTA0MiwxMzc2NjE2NjQ1LDkzMDU0NTI4Nywt
MTIxNDY1NzEzMl19
-->