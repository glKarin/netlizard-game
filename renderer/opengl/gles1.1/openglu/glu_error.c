// from mesa 7.11.2 glu
#include "openglu1.h"
#ifdef _HARMATTAN_OPENGLES
#include <stddef.h>

struct token_string
{
   GLuint Token;
   const char *String;
};

static const struct token_string Errors[] = {
   { GL_NO_ERROR, "no error" },
   { GL_INVALID_ENUM, "invalid enumerant" },
   { GL_INVALID_VALUE, "invalid value" },
   { GL_INVALID_OPERATION, "invalid operation" },
   { GL_STACK_OVERFLOW, "stack overflow" },
   { GL_STACK_UNDERFLOW, "stack underflow" },
   { GL_OUT_OF_MEMORY, "out of memory" },
#ifdef GL_EXT_framebuffer_object
   { GL_INVALID_FRAMEBUFFER_OPERATION_EXT, "invalid framebuffer operation" },
#endif
   /* GLU */
   { GLU_INVALID_ENUM, "invalid enumerant" },
   { GLU_INVALID_VALUE, "invalid value" },
   { GLU_OUT_OF_MEMORY, "out of memory" },
   { GLU_INCOMPATIBLE_GL_VERSION, "incompatible gl version" },
   { GLU_INVALID_OPERATION, "invalid operation" },
   { ~0, NULL } /* end of list indicator */
};

const GLubyte* GLAPIENTRY
gluErrorString(GLenum errorCode)
{
    int i;
    for (i = 0; Errors[i].String; i++) {
        if (Errors[i].Token == errorCode)
            return (const GLubyte *) Errors[i].String;
    }
    return (const GLubyte *) 0;
}

#endif

