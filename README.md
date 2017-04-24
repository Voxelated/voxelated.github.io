# Voxel Documentation Repository

This repository builds and supplies the documentation for the Voxel's
libraries. It uses Jekyll to build the static documenation content and uses
[Materialize](http://materializecss.com/) for formatting.

There are a few changes which have been made to Materialize to produce a more
customized look. They are the following:

## Css Additions:

In the **_sass/components** folder, there have been numerous minor changes to
colors etc, while the most notable additions are the **syntax.scss**,
**voxel.scss**, and **doxygen.scss** files. The doxygen scss file doesn't
change much for this site, however, it allows a css file to be generated which
can be used to create doxygen API documentation with the same look. To compile
a css file, do the following:

```bash
sass _sass/materialize.scss outputStylesheet.css
```

which can then be used with Doxygen to create the same look. For more
information on how this is done, see
[MaterialDoxygen](https://github.com/Voxelated/DoxyFormat).

## Javascript Additions:

The only real javascript addition is the script which makes a dynamic table of
contents for large screens: see __js/makeToc.js__. This just looks through the
page content and finds the headings.

## Reuse:

If you like the look of the documentation, please feel free to use it, with the
appropriate changes. 

## Todo:

Add instructions for how to modify the parameters to create a custom look.


