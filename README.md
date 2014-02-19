Initial version by Dave Caress of MBARI.

This repo is a place for Kurt Schwehr to try out some C style changes to the WASSP driver that is being used for demonstration of creating an MB-System sonar driver.

Some bits were taken from:  [Google C++ Style Guide](http:////google-styleguide.googlecode.com/svn/trunk/cppguide.xml):

The code was compiled on Mac OSX 10.9 with fink using the following commands:

    mkdir ~/src/mbsystem
    cd ~/src/mbsystem
    svn co svn://svn.ilab.ldeo.columbia.edu/repo/mb-system/trunk mb-system
    mkdir build inst
    cd build
    CFLAGS=-Wall ../mb-system/configure --with-netcdf-include=/sw/include \
       --with-gmt-lib=/sw/lib --with-gmt-include=/sw/include --with-proj-lib=/sw/lib \
       --with-proj-include=/sw/include  --prefix=$HOME/src/mbsystem/inst \
       --without-gsf
    make -j 4
    make install

See also:

[Mac OSX 10.9 Setup notes ](https://docs.google.com/document/d/1HwoFtCYRw3xY0KjqbF7Pr4E1Cu34HrDg67aGm_owBek/edit?usp=sharing)


-Kurt Schwehr
2014-Feb-19
