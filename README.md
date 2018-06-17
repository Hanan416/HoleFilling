# HoleFilling
Hole filling application for detecting a single hole in an image and fill it with a given weight function

This projecy was made using opencv-3.2.0-vc14

This application was made to detect a (single) hole in a given B&W image and fill it according to a given weight formula
described in <i>WEIGHT</i> in holeFilling.h, one can change the values of <i>EPSILON, POW_Z, APPROX_ITERS</i> to get different results,
Also <i>WEIGHT</i> function to try different formulas.


<b>NOTE</b>: the original project is very large ~1GB!! due to including openCV inside $(solutionDir) in a folder called
             External Libraries. In order to run the project please change the solution properties:
             C/C++ > General > Additional Libraries.              <b>change location to your openCV lib files</b>
             Linker > General > Additional Library Directories.   <b>change location to your openCV build\x64\vcXX\lib folder</b>
             Linker > Input > Additional Dependencies.            <b>change names to your openCV lib relevant files</b>


<b>How to Use</b>: Just give the relevant command line arguments for the program which should be <imageName.extention> <k-connection>

<br><br><br>
### HoleFilling basic algorithm:
  Main idea was given a hole in a picture with n pixels, first find the hole boundry pixels and for each <i>holePixel</i>
  compute the intensity as a function of the sum of the boundry pixels intensity multiply by each <i>boundryPixel</i> intensity
  normalized by the total sum of intensities.
  
  <b>Complexity</b>
  If we have <i>n</i> pixels inside the hole and <i>m</i> boundry pixels, this naive approach calculates each <i>holePixel</i> p_i
  its intensity based on all <i>m</i> boundry pixels, thus a total of <b>O(m*n)</b>.
  In worst case scenario <i>m</i> > <i>n</i>, consider a long thin line of hole in a given picture, therefore the complexity 
  is <b>O(n^2)</b>

<br><br><br>
### HoleFillingApprox algorithm:
  Main idea was once we found a <i>holePixel</i> p_i we can set all of its k-connected neighbors and ignore the boundry of the hole.
  For a given <i>holePixel</i> p_i its new intensity value will be computed according to its neighbors, for each neighbor of 
  p_i compute I(p_i) new value by using <i>WEIGHT</i> function with all neighbors which are <b>not</b> holes as well.
  In order to make the approximation accurate one must run the algorithm <i>APPROX_ITERS</i> times, for larger number the
  approximation is more accurate.
 
  <b>Complexity</b>
  If we have <i>n</i> pixels inside the hole and <i>k</i> neighbor pixels, this approximation approach calculates each holePixel 
  p_i its intensity based on all <i>k</i> neighbor pixels, k is a constant equal to 4 or 8, thus a total of <b>O(n)</b>.
  
<br><br>
### Results

values:
  POW_Z = 5,  APPROX_ITERS = 50
  <br>
<a href="http://tinypic.com?ref=2jamdfc" target="_blank"><img src="http://i65.tinypic.com/2jamdfc.jpg" border="0" alt="Image and video hosting by TinyPic" width="75%"></a>
<br><br>
values:
  POW_Z = 50,  APPROX_ITERS = 5
<br>
<a href="http://tinypic.com?ref=5kiyhs" target="_blank"><img src="http://i64.tinypic.com/5kiyhs.jpg" border="0" alt="Image and video hosting by TinyPic" width="75%"></a>
<br><br>
values:
  POW_Z = 10,  APPROX_ITERS = 100
<br>
<a href="http://tinypic.com?ref=24xnwaw" target="_blank"><img src="http://i64.tinypic.com/24xnwaw.jpg" border="0" alt="Image and video hosting by TinyPic" width="75%"></a>
<br><br>
values:
  POW_Z = 100,  APPROX_ITERS = 10
<br>
<a href="http://tinypic.com?ref=1231g5h" target="_blank"><img src="http://i64.tinypic.com/1231g5h.jpg" border="0" alt="Image and video hosting by TinyPic" width="75%"></a>

