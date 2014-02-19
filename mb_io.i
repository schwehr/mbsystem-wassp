%module example
%{
 /* Includes the header in the wrapper code */
 #include "mb_io.h"
%}
 
/* Parse the header file to generate wrappers */
%include "mb_io.h"
