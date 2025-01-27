# Sausage64 Sample Library

This library contains a single .c and .h file which you can drag and drop into your N64 project in order to have support for Sausage64 models converted by the [Sample Parser](../Sample%20Parser) tool.

The library is, currently, very basic. It can be expanded in the future in order to add more features, such as animation speed and blending. 

With this implementation of the library, matrix transformations are done on the CPU in order to reduce the memory footprint. This does mean that the CPU will be doing a bit more work, but that will probably not be too much of a problem given that most games are fillrate limited. Rotations are also performed with Euler angles, which is not very efficient but allows for keeping of angle rollover. This will be changed to quaternions in a future date. Animations are also expected to playback at 30 frames per second.

A tutorial on how to use the library is available [in the wiki](../../../wiki/4%29-Sample-library-tutorial). You also have an example implementation available in the [Sample ROM](../Sample%20ROM) folder.

<details><summary>Included functions list</summary>
<p>
    
```c
/*==============================
    sausage64_initmodel
    Initialize a model helper struct
    @param The model helper to initialize
    @param The model data 
    @param An array of matrices for each mesh part
==============================*/
extern void sausage64_initmodel(s64ModelHelper* mdl, s64ModelData* mdldata, Mtx* matrices);

/*==============================
    sausage64_set_predrawfunc
    Set a function that gets called before any mesh is rendered
    @param The model helper pointer
    @param The pre draw function
==============================*/
extern void sausage64_set_anim(s64ModelHelper* mdl, u16 anim);

/*==============================
    sausage64_set_postdrawfunc
    Set a function that gets called after any mesh is rendered
    @param The model helper pointer
    @param The post draw function
==============================*/
extern void sausage64_set_predrawfunc(s64ModelHelper* mdl, void (*predraw)(u16));

/*==============================
    sausage64_update_anim
    Updates the animation frame index based on the animation 
    tick
    @param The model helper pointer
==============================*/
extern void sausage64_set_postdrawfunc(s64ModelHelper* mdl, void (*postdraw)(u16));

/*==============================
    sausage64_advance_anim
    Advances the animation tick. Assumes model is animated
    at 30FPS, and that this model has animations.
    @param The model helper pointer
==============================*/
extern void sausage64_advance_anim(s64ModelHelper* mdl);

/*==============================
    sausage64_drawmodel
    Renders a Sausage64 model
    @param A pointer to a display list pointer
    @param The model helper data
==============================*/
extern void sausage64_drawmodel(Gfx** glistp, s64ModelHelper* mdl);
```
</p>
</details>
</br>
