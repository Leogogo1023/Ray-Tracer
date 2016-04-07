# Ray-Tracer

This is a half-semester project in COMS 4160, Computer Graphics, lectured by Micheal Reed (Blue Sky studio). The project is divided into six parts, which are accumulative and built upon each other. The code here is the final code.

To run this project, we need to have .txt source file, which defines basic configurations and geometry setting, including sphere, plane, triangle. Also, for sophisticated images, we need .obj files. Some sample files has been provided. 

Below is the requirements for each part:

Milestone1: 

In theme 1, you will be writing, testing, and evaluating a raytracing renderer named raytra.
Eventually, this will be a well-featured renderer, but for this week you should just get the
basic framework working. Implement only the most basic functionality:


scene file read (we provide a parser outline for you!)
camera & image setup
primary ray generation
ray/sphere intersection (note: there may be multiple spheres)
image write
no: shading, materials, lights, etc.

Your raytra should read in the scene file, build the camera model and set up the image, and
generate rays - 1 for each pixel. For any pixel, if there is a ray-sphere intersection, the color
for that pixel should be red. If there is no ray ray-sphere intersection, the color of that pixel
should be black. After rendering all the pixels, the OpenEXR image file should be saved and
the program should exit.

raytra takes one arguments - the name of a scene file to read. The scene file is documented

in the "Resources" section, and typically has a ".txt" extension. A basic parser is supplied in

the "Resources" section as well.

For this part of the assignment, only the camera command and the sphere command need
to be working (from the scene file format).

Some test scenes will be posted, but we suggest you make your own as well.


Milestone2: Shading

For the second milestone, you will extend your renderer so that it computes some reasonable shading model for each intersection point on the sphere: you will use the blinn-phong model that is described in the class notes and textbook chapter 4.5.

Now, your code will not only have to see if the ray through a pixel intersects a sphere, but it must determine *which* of the possible intersections (if there is more than one) is the closest. And for that closest intersection, you will need to retain the intersection point, the surface normal, and the material associated with the intersected Surface (sphere). You can then compute the blinn-phong shading at the intersection point and use that value for your image RGB value (instead of just red as you did before.

The information you need to use to compute the Blinn-Phong shading is:
  the surface normal at the (closest) intersection point
  the normalized vector from the intersection point to the light
  the normalized vector that is opposite the camera ray direction vector
  the diffuse & specular coefficients of the material, and its phong exponent

From these values, you can compute the diffuse contribution and specular contribution to the shading at the intersection point. Add them together to get the color for the associated pixel.

In order to accomplish this, your parser will need to start recognizing material definitions, as assign them to each geometric primitive defined subsequently. [In the structure we discussed in class, this would mean that your Surface class had either a material definition as a data member, or a pointer to a material definition]. Your parser will also have to read in any light defined in the scene file - for this milestone, it will only be a single point light. Lights do NOT go on the Surface list - they are not usually intersected by rays in the scene - they are only used for lighting calculations.

Finally, please add the ability to render the "plane" geometric entity (see the scene file description for details).

Good luck - once this works you will start to see some good images.


Milestone3:  Triangles

For this assignment, you are to extend raytra's capabilities, both in both geometry and lighting.

You are to implement a new surface classe: triangles. The scene file format document describes how this entity is defined in the scene file. Use the ray/triangle intersection described in the book, which will also be discussed in class. (The one in the book gives you barycentric coordinates, which will be useful when we start to texture map our renders).

In addition to adding triangles, please also add the ability to have multiple light sources, and true shadows - by using a ray starting from the hit point to the light source to see if there is an occluding object between the hit point and light. So, for example, there might be three point lights, but not every hit point in the scene receives light from every source - luckily for us, this behavior is linear and we can just sum contributions form each (visible) light source.

So, 3 new capabilities: triangles, multiple light sources, and shadow rays. These are all discussed in your reading, but we will discuss them again in class.

 

 

I will add that this means your renderer will be "throwing" a lot more rays: 1 primary ray for every pixel, and an additional number of rays (one for each light source) at every hit point. We aren't yet at the point where this will be computationally taxing, but we are getting close...keep your code tight and efficient.


Milestone4: Reflections, ambient and OBJ files

For this assignment, you are to extend raytra's capabilities to permit true specular reflections. To do this, you will implement recursive ray-tracing as discussed in class and at the end of the text's chapter 4. You may choose whatever program architecture you wish, but it is suggested that you consider implementing it in the manner discussed in class - as a function that returns the radiance (spectral energy) along a ray, and which recursively calls itself.

The material definitions in the scene file contain a third triple (after the phong exponent) which specifies the coefficient for the ideal reflective rays (K_m in the book) - when these are [0 0 0] there is no need to call the recursive function (as it wold be weighted by zero in any case).

This assignment should require very little (or none!) low-level code - it's really an architectural change that will give you this capability.

Also: add the capability for an ambient light (note: at most 1 light in the scene will be an ambient light)

In addition, for loading in a file full of triangles, we introduce a new scene file command "w", and associated file format: WaveFront (OBJ) format) [*1]. If the first character in a scene file is "w", it will be followed by a file name of an OBJ file that describes one or more triangles (e.g. "w mywavfrontfile.obj"). The OBJ file format is quite simple (for this case): it's a series of "v" statements (much like our scene file description) that denote vertices, followed by a series of "f" statements, each of which defines a triangle by specifying the 3 (integer) indices into the list of vertices for the 3 vertices of the triangle. A parser sketch for this will be posted on Friday night - it will make an array of 3xN floats (for N vertices) and an associated array of integer indices, 3 for each triangle. It will be up to you to construct the necessary Triangle objects and put them in the surface list, etc. Example OBJ files will be posted.

[*1] more on the OBJ file format here: http://en.wikipedia.org/wiki/Wavefront_.obj_file (Links to an external site.) . You only need a very limited subset of it's commands: "v" to denote a vertex, and "f" to denote a face (followed by 3 ints). (Also, "#" for comment.)



Optional: for this assignment, you may optionally implement *refraction* for spheres. Because of the behavior of refraction, it is only implementable on closed volumes, and since the only closed objects you have implemented are spheres, limit yourself to that (later in the course, if you wish to extend it to other objects, you can try to then). The only remaining detail is to consider how to add the specific material attributes: you will need to add (in addition to the usual material parameters) the index of refraction (a single scalar) and the attenuation constant "a" (an rgb triple on (0 1] ). You can do this by adding optional parameters to your material specification "m" in the scene file language (just make sure it will still read the regular scene files for testing), or you may use the "o" designation for optional parameters (see the scene file description document). [note: if you choose to do this, please use the derivation of Beer's law in the class slides (to compute I(s) - the intensity after transmission through the refractive material) - the book has a mistake in the sign of the exponent.


Milestone5: Acceleration structures

Now that we are rendering more complex scenes, and adding more features that both improve the image quality and significantly extend the processing time, we need to do something to eliminate the O(n) comparison for every single ray we generate.

The solution to this is a scene-wide acceleration structure, based on bounding boxes (that, themselves, accelerate ray/surface intersection testing for individual pieces of geometry).

First, you are to implement fast bounding box intersection tests, as described in your textbook. Although, by themselves, bounding boxes only do a little to speed up renders based on spheres and triangles, they are the basis for BVH trees and other acceleration techniques which allow efficient ray tracing of millions of elements, and so knowledge of them is very worthwhile.

You are to implement axis-aligned bounding boxes for all scene geometry, each represented by two points (one containing the minimum x,y & z, and the other the maximum x,y, and z). In the usual implementation, each surface object has a bounding box, and these bounding boxes would be used to quickly reject ray-surface intersection tests - in the surface ::intersect() method, *first* the ray is tested against the bounding box - if it misses then ::intersect() returns a miss immediately. As each surface subclass will need such a bounds, you would typically put the bbox as a member in the surface class (or your equivalent). Then the constructor for each surface subclass would, in addition to its regular duties, set the bbox to the correct dimensions/placement. (Remember the bboxes are axis-aligned). And, to repeat, each surface subclass will perform, as the first part of its intersection test, a test to see if the bbox is hit - if no, then it returns a "miss", otherwise the intersection test continues it's "usual" code (full intersection for ray/triangle, ray/sphere, ray/plane, etc).

Bounding bboxes should be rendered in the material for the geometric element they are bounding.

To test this, we will have another mode for the renderer : an optional 3rd argument. When there 3 arguments:

raytra scene_file output_image flag_render_bboxes

The third argument can have 4 values ({0,1,2,3}), or not be present.

If the third argument is zero, you are to render as "normal". If the 3rd argument is 1, you are to render the boxes ONLY: i.e., if there is a hit on a bbox, you should return the t value of that hit, along with the normal, as you typically would for the actual surface. Note that the normal can only be one of 6 directions (+/- X, +/- Y, or +/- Z). If there is no 5th argument, you renderer should use the bboxes as usual: i.e. as a rejection test for ray/surface intersection, which (if it passes) continues on to the usual ray/surface intersection code.

In other words, if there is a 3rd argument to raytra, your scene should render as a bunch of rectangular, axis-aligned boxes.Otherwise, render normally, using the bboxes as quick rejection tests in the ::intersect() methods.

I look forward to seeing the bbox'ed scenes

Secondly, you are to implement a scene-wide BVH tree, which will accelerate your renderer by one-to-two orders of magnitude. The current architecture of raytra does not allow high-performance rendering, because it is testing every surface for intersection on every primary, shadow, and reflected ray. To accelerate this process, the scene geometry gets split up so that rays only have to consider geometric elements that they are "near" as they propagate through the scene. The most common technique is the Bounding Volume Hierarchy, which is a tree structure that turns the O(n) search for intersection on every ray into a Lg(n) search. BVH trees are discussed in your book thoroughtly. They can be implemented simply, but it is a somewhat sophisticated piece of code to do so, so please start on this early. I will discuss them in the next class.

The use of the BVH tree should be controlled by the 3rd argument - if it is "2", render the (leaf) bounding boxes only (as above), but using the BVH tree. If the thrid argument is 3, OR if it is not present, render the actual surfaces using the BVH tree.

 Addendum: to make this (slightly) easier, the scene files for this, and the remaining, assignments will not include plane primitives (they will be replaced, when needed, with two very large triangles to form a ground plane). This will make is so that you do not need a separate list of planes, in addition to the geometry that can be bounded by a bounding box.
 
 
 Milestone6: Monte-Calro ray tracing
 
 In this assignment, you are going to extend your raytra program to be a monte-carlo ray tracer, which will produce beautiful images. You will implement stratified sampling of primary rays, and area light sources.

The simplest part of the assignment is to use multiple primary rays per pixel: you should have a constant that controls the number of samples you use per-pixel, so that you can easily experiment with larger and smaller values (this value should be the square root of the number of samples, i.e. 1 gives 1 sample, 2 gives 4 samples, 3 gives 9 samples, etc). You should implement jittered random primary rays, as described in class and in your text (chapter 13). However many primary rays you generate per pixel, you must remember to divide the final, summed radiance by that number to normalize it.

Slightly more difficult than that is a simple implementation of area lights: when a shadow ray is constructed, the area light's position is queried: if the area light returns a random position across its area, an "ok" image will be made that has soft shadows.

To make a *good* soft shadow, either a full sampling of shadow rays must be made across the area of the light, per lighting calculation (this is expensive) OR the primary rays and shadow rays must have their stratification correlated - this too was discussed in class and is described in the text.

The area light is described by a new light type, using the scenefile description:

l s x y z nx ny nz ux uy uz len r g b

describes a square area light, with center at [x y z], pointing in (normalized) direction [nx ny nz], with normalized u-direction [ux uy uz], and with the length of each side given by "len" - all these values are floats. The u-direction specifies one axis of the square, the same way it does for the image plane (see pg. 75). The v-direction is just the u-direction crossproduct the pointing direction. [r g b] specifies the color and magnitude of the radiant exitance of the source, as it does for all the light source types.

For example: "l s 0 10 0 0 -1 0 1 0 0 2 .5 .5 1." describes a 2mmx2mm square area light, located 10 units above the XZ plane, pointing straight downwards (down Y that is), and with u-direction aligned with the X axis (and so the V direction is going to be aligned with the Z axis). It is blueish in color.

When you add an area light class to your code, you will have to develop a simple way to generate samples on its surface. As an example, if you were ignoring stratification, given two random parameters (ru, rv) on [0 1], the corresponding sample on the light is:

XYZ + (ru - .5)*U*len + (rv - .5)*V*len

where xyz = [x y z], U=[ux uy uz], and V=[vx vy vz].

The random parameters can be generated by a call to rand(). To improve this to use stratified sampling, you should use a technique similar to the way primary rays are stratified: by splitting the area into square sub-domains, and sampling there. Each "shadow ray" represents 1/N times the light's radiant exitance, for example if you are taking 4 shadow rays, each one contributes 1/4 of the light's emission. Each shadow ray's contribution should be scaled, as before, by the cosine of the angle between the surface normal and the direction to the specific light sample.

To make this testable (and allow you the flexibiltiy of testing it yourself), raytra should now use bounding boxes and BVH tree by default: a new third and fourth argument for raytra 1.6 control the sampling. The third argument specifies the square root of the number of primary rays per-pixel (i.e. "1" for 1 primary ray, "2" for 4 primary rays, "3" for 9 primary rays etc), and the fourth argument specifies the square root of the number of shadow rays per primary ray (i.e. "1" means 1 shadow ray per primary ray, "2" means 4 shadow rays per primary ray, "3" means 9 shadow rays per ray intersection)

So, for example, for a scene with 1 diffuse sphere and 1 area light, "1 1" is just regular old-style ray-tracing. "2 1" will use 4 rays through the pixel, and 1 shadow ray PER PRIMARY RAY, so 4 shadow rays. "2 2" means 4 rays through the pixel, and 4 shadow rays PER RAY intersection, so 16 total shadow rays.

If the scene has some reflection in it, and all the rays through a pixel bounce twice before missing everything in the scene, a "2 3" specification would mean: 4 primary rays through the pixel, and for each of them: 9 shadow rays at the first intersection, and then 9 *more* shadow rays for each of them at the second intersection, for a total of 4+4*9+4*9) = 72 rays.

FYI for testing, a good starting point is "3 1" - and start this homework by implmenting stratified sampling of the primary rays first.

Good luck, I look forward to see the results from this, the final assignment in raytracing).
