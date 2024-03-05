// be gin − adder . h −−−−−−−−−−−−

// The f o l l o w i n g two l i n e s p r e v en t adder . h from bein g i n cl u d e d
// more than once i n any s o u r c e ( . cpp ) f i l e . I f t h i s were t o happen
// i t would c au se problems i n the c ompile p r o c e s s but i t i s d i f f i c u l t t o
// p re ve n t manually i n l a r g e p r o j e c t s . These #i f n d e f , #d e f i n e and #e n d i f
// commands f o r an ” i n cl u d e guard” and a r e t y p e s o f c om pil e r d i r e c t i v e .
// The i n cl u d e guard c o n t ai n s an ID f o r t h i s f i l e ”MATHSLIB ADDER H” , t h i s i s
// a r b i t r a r y but must be unique wi t hi n the p r o j e c t .
#ifndef MATHSLIB_ADDER_H
    #define MATHSLIB_ADDER_H

// We need t o p r e f i x our f u n c ti o n names with an a d d i t i o n a l
// keyword which i s d i f f e r e n t depending on the o p e r a ti n g
// system we a r e u sin g , and whether we a r e u si n g o r c r e a t i n g the
// l i b r a r y .
// The v a r i a b l e s ”maths EXPORTS” must be d e fi n e d a t b uil d time i f
// we a r e b uil di n g the l i b r a r y , but not i f we a r e u si n g i t .
    #if defined (WIN32) | defined (_WIN32 )
        #ifdef maths_STATIC
// dont add any keywords i f b uil di n g a s t a t i c l i b r a r y
            #define MATHSLIB_API
        #else
            #ifdef maths_EXPORTS
                #define MATHSLIB_API __declspec ( dllexport )
            #else
                #define MATHSLIB_API __declspec ( dllimport )
            #endif
        #endif
    #else
// MATHSLIB API i s d e fi n e d a s n o thin g i f were not on Windows
        #define MATHSLIB_API
    #endif

// The above w i l l i n cl u d e one o f :
// d e c l s p e c ( d l l e x p o r t )
// d e c l s p e c ( dllim p o r t )
// b e f o r e d e c l a r a t i o n s . This i s a Mi c r o s o f t s p e c i f i c
// e x t e n si o n t o C/C++

// p r o t o t y p e f o r the f u n c ti o n i n c l u d i n g a d d i t i o n a l keyword
    MATHSLIB_API int add ( int a , int b ) ;
#endif

// end − adder . h −−−−−−−−−−−−