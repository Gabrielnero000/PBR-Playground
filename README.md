
<h1 align="center">PBR Playground</h1>

<img src="https://github.com/Gabrielnero000/PBR-Playground/blob/master/gallery/first.png?raw=true">

Hey, welcome! 

This project is the register of my Physical Based Rendering (PBR) study, experiences and interesting stuffs in the development process of a PBR engine. I'm starting this repository with almost any knowledge in this area, so this will be a long way down in the PBR's world. I hope you enjoy this travel and fell free to question, comment and  add knowledge! Don't miss the [gallery section](https://github.com/Gabrielnero000/PBR-Playground#gallery-images-of-experiments) to check what a PBR engine can do!

This repository is also for educational purposes in the class "Special Topics in Computing" ministered by Dr. Christian Azambuja Pagot in the  Federal University of Paraíba.

"_The cosmos is all that is, or ever was, or ever will be. Come with me_." - Carl Sagan.

## Current Features
* Render Core
	* Ray Casting mode
* Cameras
	* Perspective Camera
* Primitives
	* Spheres
	* Triangles
		* *Fast, Minimum Storage Ray/Triangle Intersection* (Möller, T.; Trumbore, B.)
		* 
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

<p align="center">
    <img src="https://raw.githubusercontent.com/Gabrielnero000/PBR-Playground/master/utils/Triangle%20Intersection%20Algorithms%20Performance.png" alt>
    <em>Möller vs Wald</em>
</p>

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
eyJoaXN0b3J5IjpbLTk1NjM2NTU1NywxMDU1MDk5MjM3LDE2MT
UwNzUxMjUsLTE2Mjk0MzQ1NjksLTEwNDk0MDMzNjQsLTIwODU2
MDIyNzcsLTIwODU2MDIyNzcsODc4OTM1MDQyLDEzNzY2MTY2ND
UsOTMwNTQ1Mjg3LC0xMjE0NjU3MTMyLDE4NTkzMTcxMjMsMTQx
MDA1NzQ0NywtNDU2ODI5MDYyLC0xMTEzMjM0MTM1LC03MjY1Nz
U4NzAsNjQyNjY4MjQzLC0xMjE1Mzk5Nzc0LDQwNjY1NTc4Miwt
MTEyNTgzMzI4OF19
-->