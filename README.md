# HoleFilling
Hole filling application for detecting a single hole in an image and fill it with a given weight function


This application was made to detect a (single) hole in a given B&W image and fill it according to a given weight formula
described in WEIGHT in holeFilling.h, one can change the values of EPSILON, POW_Z, APPROX_ITERS to get different results,
Also WEIGHT function to try different formulas.


<b>NOTE</b>: the original project is very large ~1GB!! due to including openCV inside $(solutionDir) in a folder called
             External Libraries. In order to run the project please change the solution properties:
             C/C++ > General > Additional Libraries.              <b>change location to your openCV lib files</b>
             Linker > General > Additional Library Directories.   <b>change location to your openCV build\x64\vcXX\lib folder</b>
             Linker > Input > Additional Dependencies.            <b>change names to your openCV lib relevant files</b>


<b>How to Use</b>: Just give the relevant command line arguments for the program which should be <imageName.extention> <k-connection>

<br><br><br>
### HoleFilling basic algorithm:
  Main idea was given a hole in a picture with n Pixels, first find the hole boundry Pixels and for each holePixel 
  compute the Intensity as a function of the sum of the boundry pixels Intensity multiply by each boundryPixel intensity
  normalized by the total sum of intensities.
  
  <b>Complexity</b>
  If we have <i>n</i> pixels inside the hole and <i>m</i> boundry pixels, this naive approach calculates each holePixel p_i
  its intensity based on all <i>m</i> boundry points, thus a total of <b>O(m*n)</b>.
  In worst case scenario <i>m</i> > <i>n</i>, consider a long thin line of hole in a given picture, therefore the complexity 
  is <b>O(n^2)</b>

