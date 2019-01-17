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
Here is a basic UML calass diagram that can be used as base for our Ray Tracer. Gradually it will be expanded as we add new features, so it's important to have a robust architecture in the begining. I'll be using C++ to implementation, since we need fast computation and object-oriented features (inheritance, polymorphism, function overload, etc). I'm using the [GLM](https://glm.g-truc.net/0.9.9/index.html) library to abstract some vector representation and operations (for now). So there it is:

As we can see, we have intially four classes and two abstract classes:
 * **Class Ray** - represents the most basic element in a Ray Tracer: a ray. A ray, wich is a 


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
eyJoaXN0b3J5IjpbLTE3NDcwNTc0NTUsNDAwNTk4NDIsOTIwMT
c3NTM0LC0xMzg0MDY3NTU2LC0xNjEzMzk5MzYwLDIxMjg1OTAz
ODcsLTE1MzU3MDQxNjYsMTY4NDMzMjQ3MywtMTgyNTUwODc2Mi
wtMTYyNTYzMzE0NywxMjg0MzUwNTM5LC0xNjgwNDg5MDI5LC0y
NTcwNjY1NzUsMTg1ODQ5MTE2OCwxNjMzODczMTQwXX0=
-->