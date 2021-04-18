
#ifndef _PX_CONF__H
#define _PX_CONF__H 1
/*!
    Put your customizations here.
    This file is included in "px.h" after standard headers.
*/

/*!
    These are default values of customizable macro definitions. Redefine them according to your requirements.
      PX_NESTING_CATCH_LIMIT 100
      PX_OBJ_TYPEDEF int
      PX_UNCAUGHT_EXCEPTION_EXIT_CODE 11

    Note: if PX_OBJ_TYPEDEF is to be a non-scalar type, provide it with a name declared with typedef, e.g.:
            typedef struct px_obj {...} px_obj_t;
            
            #define PX_OBJ_TYPEDEF px_obj_t
          or
            #define PX_OBJ_TYPEDEF struct px_obj
*/

/*! 
    These are feature compile flags, that can be defined with any value to be interpreted of being set them on.
      PX_DEBUG
      PX_NO_MULTITHREADING
*/


#endif

