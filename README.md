
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

As we can see, we have intially four classes and two abstract classes:
 * **Class Ray** - represents the most basic element in a Ray Tracer: a **ray**. A ray, wich is a straight line, can be expressed as <img alt="$f(t) = O + tD$" src="svgs/6b08fd0c1a52a05ee040797dee182ff0.png" align="middle" width="103.545585pt" height="24.6576pt"/>, were <img alt="$O$" src="svgs/9afe6a256a9817c76b579e6f5db9a578.png" align="middle" width="12.995565pt" height="22.46574pt"/> is **the ray's origin**, <img alt="$D$" src="svgs/78ec2b7008296ce0561cf83393cb746d.png" align="middle" width="14.06625pt" height="22.46574pt"/> is the **ray's direction** an <img alt="$t$" src="svgs/4f4f4e395762a3af4575de74c019ebb5.png" align="middle" width="5.9361555pt" height="20.22207pt"/> is a real number. Variating <img alt="$t$" src="svgs/4f4f4e395762a3af4575de74c019ebb5.png" align="middle" width="5.9361555pt" height="20.22207pt"/> we have **any point in the straight**.
 * **Class Primitive** - abstract class that represents a **primitive**. A primitive is basically anything that a ray can colide with. Most common are triangles, shperes, planes, quadrics, meshes (which just lots of triangles) and so on. Since every primitive have a diferent **intersection routine**, the ``intersect`` function must be ``virtual``.
 * **Class Output** - used to output the image. Holds a buffer feeded during the render and transforms it to fit the **PPM's format**.
 * **Class Scene** - stores all primitives in the scene. Have a intersection function that just basically calls every primitive intersection function.
 * **Class Camera** - abstract class to represents the camera. Since there is lots of camera models (orthographic, perspective, with/without lens) the routine to generate rays is variable. So the ``getRay`` function must be ``virtual`` as well.
 * **Class Render** - that's were the magic happens. The render loop is essecially two nested for loops (using output's resolution), were the rays are shooted from the camera to the scene and getting the colision information.

Looks simple, right? Well, this will become madness soon! :)


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
eyJoaXN0b3J5IjpbMjA4MTQzMTkxNiw0MDA1OTg0Miw5MjAxNz
c1MzQsLTEzODQwNjc1NTYsLTE2MTMzOTkzNjAsMjEyODU5MDM4
NywtMTUzNTcwNDE2NiwxNjg0MzMyNDczLC0xODI1NTA4NzYyLC
0xNjI1NjMzMTQ3LDEyODQzNTA1MzksLTE2ODA0ODkwMjksLTI1
NzA2NjU3NSwxODU4NDkxMTY4LDE2MzM4NzMxNDBdfQ==
-->
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTgxMDk4NjM1MSw1NTg4NzY1NjksLTkxOD
g3MDA0NSwyMDgxNDMxOTE2LDQwMDU5ODQyLDkyMDE3NzUzNCwt
MTM4NDA2NzU1NiwtMTYxMzM5OTM2MCwyMTI4NTkwMzg3LC0xNT
M1NzA0MTY2LDE2ODQzMzI0NzMsLTE4MjU1MDg3NjIsLTE2MjU2
MzMxNDcsMTI4NDM1MDUzOSwtMTY4MDQ4OTAyOSwtMjU3MDY2NT
c1LDE4NTg0OTExNjgsMTYzMzg3MzE0MF19
-->