---
layout: page
title: 
image:
  feature: about.jpg
  credit: WeGraphics
  creditlink: http://wegraphics.net/downloads/free-ultimate-blurred-background-pack/
comments: false
modified: 2016-02-01
---

This is essentially an online journal.

The posts will be tutorial-like explaining something I may have come across and 
which took me a while to understand, setup guides or general thoughts. I have 
found that trying to explain something in a clear, simple way, tests my 
understanding. The blogs posts are thus also a way to help myself and 
hoperfully some of the posts will be useful to other people as well.

My main interests are in software development, specifically in distributed
computing, parallelism, and optimisation, and how these can be used to solve 
real world problems.

I'm currently doing an MPhil in Scientific Computing at the University of
Cambridge. My work involves looking at how to optimally make use of
computational hardware to accelerate solving multi-physics problems, and how
such techniques can be incorporated into software libraries with clear
interfaces, allowing anyone to reap the benefits.

I try to work personal projects to explore new areas, when I have some extra
tome, and I try to document and maintain them well so that others can learn 
from them. If any of the projects interest you, send me an email and I'd be 
happy to work with you to take the project further. Here is a list of some of 
them:

## Projects

* ___```Jolt:```___ An expression template library for array manipulation. The
  library provides a clear interface to the user, where the appearance of
  operations look as close as possible to their formal mathematical
  representation. The aim is to support a CPU and GPU backend, and to provide
  performance comparable with the Blitz++ CPU array library, and the Thrust GPU
  library.

* ___```Meta:```___  A metaprogramming library which provides various
  compile-time functionality. This is a constantly evolving project, and
  whenever I require some compile-time functionality, or think of something
  which may be generally useful,

* ___```Parahaplo:```___ A parallel implementation of the minimum 
  error-correction individual haplotype assembly problem -- an NP-hard problem
  --using a parallel graph-based GPU search. The project in its current 
  implementation can achieved a 50x performance improvement over existing 
  (non-parallel) algortihms on generated DNA datasets. The accuracy is slightly
  less than the best solutions in existing research. I'm sure that the cause of
  the rediced accuracy is a software bug, and will hopefully fix it when I get 
  a chance. The codebase also needs to be refactored, which I'll do once I've
  finished with some of the other library's which are designed to make the
  development of this kind of an application much simpler. 
  [Parahaplo Repository](https://github.com/robclu/parahaplo)

## Publications

The following is a list of papers I have written (hopefully this will grow):

R. Clucas and S. Levitt, CAPP: A C++ Aspect-Oriented Based Framework for Parallel Programming with OpenCL, in Proceedings of the 2015 Annual Research Conference on South African Institute of Computer Scientists and Information Technologists, ser. SAICSIT 15. New York, NY, USA: ACM, 2015, pp. 10:110:10. [Online]. Available: [http://doi.acm.org/10.1145/2815782.2815818](http://doi.acm.org/10.1145/2815782.2815818) [Camera ready draft- [[1]](https://github.com/robclu/capp/blob/master/documentation/final_version/Capp.pdf)]

[1] : [https://github.com/robclu/capp/blob/master/documentation/final_version/Capp.pdf](https://github.com/robclu/capp/blob/master/documentation/final_version/Capp.pdf)  