%module example
%{
 /* Includes the header in the wrapper code */
 #include "mb_define.h"
%}
 
/* Parse the header file to generate wrappers */
%include "mb_define.h"
