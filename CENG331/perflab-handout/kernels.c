/********************************************************
 * Kernels to be optimized for the Metu Ceng Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

 /*
  * Please fill in the following team struct
  */
team_t team = {
    "Avengers",                     /* Team name */

    "Ali Şen",             /* First member full name */
    "e2264661",                 /* First member id */

    "Özcan Pektaş",                         /* Second member full name (leave blank if none) */
    "e2237782",                         /* Second member id (leave blank if none) */

    "",                         /* Third member full name (leave blank if none) */
    ""                          /* Third member id (leave blank if none) */
};

/****************
 * BOKEH KERNEL *
 ****************/

 /****************************************************************
  * Various typedefs and helper functions for the bokeh function
  * You may modify these any way you like.
  ****************************************************************/

  /* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
static void initialize_pixel_sum(pixel_sum* sum)
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/*
 * accumulate_sum - Accumulates field values of p in corresponding
 * fields of sum
 */
static void accumulate_sum(pixel_sum* sum, pixel p)
{
    sum->red += (int)p.red;
    sum->green += (int)p.green;
    sum->blue += (int)p.blue;
    sum->num++;
    return;
}

/*
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel
 */
static void assign_sum_to_pixel(pixel* current_pixel, pixel_sum sum)
{
    current_pixel->red = (unsigned short)(sum.red / sum.num);
    current_pixel->green = (unsigned short)(sum.green / sum.num);
    current_pixel->blue = (unsigned short)(sum.blue / sum.num);
    return;
}

/*
 * avg - Returns averaged pixel value at (i,j)
 */
static pixel avg(int dim, int i, int j, pixel* src)
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for (ii = max(i - 1, 0); ii <= min(i + 1, dim - 1); ii++)
        for (jj = max(j - 1, 0); jj <= min(j + 1, dim - 1); jj++)
            accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/*******************************************************
 * Your different versions of the bokeh kernel go here 
 *******************************************************/

/* 
 * naive_bokeh - The naive baseline version of bokeh effect with filter
 */
char naive_bokeh_descr[] = "naive_bokeh: Naive baseline bokeh with filter";
void naive_bokeh(int dim, pixel *src, short *flt, pixel *dst) {
  
    int i, j;

    for(i = 0; i < dim; i++) {

        for(j = 0; j < dim; j++) {
            if ( !flt[RIDX(i, j, dim)] )
                dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
            else
                dst[RIDX(i, j, dim)] = src[RIDX(i, j, dim)];
        }
    }
}

/* 
 * bokeh - Your current working version of bokeh
 * IMPORTANT: This is the version you will be graded on
 */
char bokeh_descr[] = "bokeh: Current working version";
void bokeh(int dim, pixel *src, short *flt, pixel *dst) 
{
    //naive_bokeh(dim, src, flt, dst);
    ///*
    pixel* srcptr;
    pixel* dstptr;
    short* fltptr;
    int leftTop = -dim - 1;
    int top = -dim;
    int rightTop = -dim + 1;
    int left = - 1;
    int right = + 1;
    int leftBottom = dim - 1;
    int bottom = dim;
    int rightBottom = dim + 1;
    int dimplus = dim + 1;
    pixel* finalptr;
    pixel* pfinalptr;
    pixel* selfLeftTop;
    pixel* selfTop;
    pixel* selfRightTop;
    pixel* selfLeft;
    pixel* selfRight;
    pixel* selfLeftBottom;
    pixel* selfRightBottom;
    pixel* selfBottom;
    // Corners
    srcptr = src;
    dstptr = dst;
    fltptr = flt;
    if (*fltptr) {
        *dstptr = *srcptr;
    }
    else {
        selfRight = srcptr + right;
        selfRightBottom = srcptr + rightBottom;
        selfBottom = srcptr + bottom;
        dstptr->red = ((srcptr)->red + (selfRight)->red + (selfRightBottom)->red + (selfBottom)->red) / 4;
        dstptr->green = ((srcptr)->green + (selfRight)->green + (selfRightBottom)->green + (selfBottom)->green) / 4;
        dstptr->blue = ((srcptr)->blue + (selfRight)->blue + (selfRightBottom)->blue + (selfBottom)->blue) / 4;
    }
    srcptr += leftBottom;
    dstptr += leftBottom;
    fltptr += leftBottom;
    if (*fltptr) {
        *dstptr = *srcptr;
    }
    else {
        selfLeft = srcptr + left;
        selfLeftBottom = srcptr + leftBottom;
        selfBottom = srcptr + bottom;
        dstptr->red = ((srcptr)->red + (selfLeft)->red + (selfLeftBottom)->red + (selfBottom)->red) / 4;
        dstptr->green = ((srcptr)->green + (selfLeft)->green + (selfLeftBottom)->green + (selfBottom)->green) / 4;
        dstptr->blue = ((srcptr)->blue + (selfLeft)->blue + (selfLeftBottom)->blue + (selfBottom)->blue) / 4;
    }
    srcptr += dim*leftBottom;
    dstptr += dim*leftBottom;
    fltptr += dim*leftBottom;
    if (*fltptr) {
        *dstptr = *srcptr;
    }
    else {
        selfTop = srcptr + top;
        selfLeftTop = srcptr + leftTop;
        selfLeft = srcptr + left;
        dstptr->red = ((srcptr)->red + (selfTop)->red + (selfLeftTop)->red + (selfLeft)->red) / 4;
        dstptr->green = ((srcptr)->green + (selfTop)->green + (selfLeftTop)->green + (selfLeft)->green) / 4;
        dstptr->blue = ((srcptr)->blue + (selfTop)->blue + (selfLeftTop)->blue + (selfLeft)->blue) / 4;
    }
    srcptr -= leftBottom;
    dstptr -= leftBottom;
    fltptr -= leftBottom;
    if (*fltptr) {
        *dstptr = *srcptr;
    }
    else {
        selfRight = srcptr + right;
        selfTop = srcptr + top;
        selfRightTop = srcptr + rightTop;
        dstptr->red = ((srcptr)->red + (selfRight)->red + (selfRightTop)->red + (selfTop)->red) / 4;
        dstptr->green = ((srcptr)->green + (selfRight)->green + (selfRightTop)->green + (selfTop)->green) / 4;
        dstptr->blue = ((srcptr)->blue + (selfRight)->blue + (selfRightTop)->blue + (selfTop)->blue) / 4;
    }

    // Top
    srcptr = src+1;
    dstptr = dst+1;
    fltptr = flt+1;
    finalptr = srcptr + dim - 2;
    while(srcptr < finalptr){
        if (*fltptr) {
                *dstptr = *srcptr;
        }
        else{
            selfRight = srcptr + right;
            selfRightBottom = srcptr + rightBottom;
            selfBottom = srcptr + bottom;
            selfLeft = srcptr + left;
            selfLeftBottom = srcptr + leftBottom;
            dstptr->red = ((srcptr)->red + (selfLeft)->red + (selfRight)->red + (selfLeftBottom)->red + (selfBottom)->red + (selfRightBottom)->red) / 6;
            dstptr->green = ((srcptr)->green + (selfLeft)->green + (selfRight)->green + (selfLeftBottom)->green + (selfBottom)->green + (selfRightBottom)->green) / 6;
            dstptr->blue = ((srcptr)->blue + (selfLeft)->blue + (selfRight)->blue + (selfLeftBottom)->blue + (selfBottom)->blue + (selfRightBottom)->blue) / 6;
        }
        srcptr++;
        dstptr++;
        fltptr++;
    }

    // Left
    srcptr = src+dim;
    dstptr = dst+dim;
    fltptr = flt+dim;
    finalptr = srcptr + dim*(dim-2);
    while(srcptr < finalptr){
        if (*fltptr) {
                *dstptr = *srcptr;
        }
        else{
            selfRight = srcptr + right;
            selfRightBottom = srcptr + rightBottom;
            selfBottom = srcptr + bottom;
            selfTop = srcptr + top;
            selfRightTop = srcptr + rightTop;
            dstptr->red = ((srcptr)->red + (selfTop)->red + (selfRightTop)->red + (selfRight)->red + (selfRightBottom)->red + (selfBottom)->red) / 6;
            dstptr->green = ((srcptr)->green + (selfTop)->green + (selfRightTop)->green + (selfRight)->green + (selfRightBottom)->green + (selfBottom)->green) / 6;
            dstptr->blue = ((srcptr)->blue + (selfTop)->blue + (selfRightTop)->blue + (selfRight)->blue + (selfRightBottom)->blue + (selfBottom)->blue) / 6;
        }
        srcptr+=dim;
        dstptr+=dim;
        fltptr+=dim;
    }

    // Right
    srcptr = src+dim+leftBottom;
    dstptr = dst+dim+leftBottom;
    fltptr = flt+dim+leftBottom;
    finalptr = srcptr + dim*(dim-2);
    while(srcptr < finalptr){
        if (*fltptr) {
                *dstptr = *srcptr;
        }
        else{
            selfBottom = srcptr + bottom;
            selfLeft = srcptr + left;
            selfLeftBottom = srcptr + leftBottom;
            selfTop = srcptr + top;
            selfLeftTop = srcptr + leftTop;
            dstptr->red = ((srcptr)->red + (selfBottom)->red + (selfLeft)->red + (selfLeftBottom)->red + (selfTop)->red + (selfLeftTop)->red) / 6;
            dstptr->green = ((srcptr)->green + (selfBottom)->green + (selfLeft)->green + (selfLeftBottom)->green + (selfTop)->green + (selfLeftTop)->green) / 6;
            dstptr->blue = ((srcptr)->blue + (selfBottom)->blue + (selfLeft)->blue + (selfLeftBottom)->blue + (selfTop)->blue + (selfLeftTop)->blue) / 6;
        }
        srcptr+=dim;
        dstptr+=dim;
        fltptr+=dim;
    }

    // Bottom
    srcptr = src+dim*leftBottom+1;
    dstptr = dst+dim*leftBottom+1;
    fltptr = flt+dim*leftBottom+1;
    finalptr = srcptr + dim - 2;
    while(srcptr < finalptr){
        if (*fltptr) {
                *dstptr = *srcptr;
        }
        else{
            selfRight = srcptr + right;
            selfLeft = srcptr + left;
            selfTop = srcptr + top;
            selfLeftTop = srcptr + leftTop;
            selfRightTop = srcptr + rightTop;
            dstptr->red = ((srcptr)->red + (selfRight)->red + (selfLeft)->red + (selfTop)->red + (selfLeftTop)->red + (selfRightTop)->red) / 6;
            dstptr->green = ((srcptr)->green + (selfRight)->green + (selfLeft)->green + (selfTop)->green + (selfLeftTop)->green + (selfRightTop)->green) / 6;
            dstptr->blue = ((srcptr)->blue + (selfRight)->blue + (selfLeft)->blue + (selfTop)->blue + (selfLeftTop)->blue + (selfRightTop)->blue) / 6;
        }
        srcptr++;
        dstptr++;
        fltptr++;
    }

    // Middle
    
    srcptr = src + dimplus;
    dstptr = dst + dimplus;
    fltptr = flt + dimplus;
    finalptr = src + dim * leftBottom - 2;
    pfinalptr = srcptr + leftBottom-1;
    while (srcptr <= finalptr) {
        while (srcptr < pfinalptr) {
            if (*fltptr) {
                *dstptr = *srcptr;
            }
            else {
                selfRight = srcptr + right;
                selfRightBottom = srcptr + rightBottom;
                selfBottom = srcptr + bottom;
                selfLeft = srcptr + left;
                selfLeftBottom = srcptr + leftBottom;
                selfTop = srcptr + top;
                selfLeftTop = srcptr + leftTop;
                selfRightTop = srcptr + rightTop;
                dstptr->red = ((srcptr)->red + (selfRight)->red + (selfRightBottom)->red + (selfBottom)->red + (selfLeft)->red + (selfLeftBottom)->red + (selfTop)->red + (selfLeftTop)->red + (selfRightTop)->red)/9;
                dstptr->green = ((srcptr)->green + (selfRight)->green + (selfRightBottom)->green + (selfBottom)->green + (selfLeft)->green + (selfLeftBottom)->green + (selfTop)->green + (selfLeftTop)->green + (selfRightTop)->green)/9;
                dstptr->blue = ((srcptr)->blue + (selfRight)->blue + (selfRightBottom)->blue + (selfBottom)->blue + (selfLeft)->blue + (selfLeftBottom)->blue + (selfTop)->blue + (selfLeftTop)->blue + (selfRightTop)->blue)/9;
            }
            srcptr++;
            dstptr++;
            fltptr++;
        }
        srcptr += 2;
        dstptr += 2;
        fltptr += 2;
        pfinalptr += dim;
    }
    //*/

}

/*********************************************************************
 * register_bokeh_functions - Register all of your different versions
 *     of the bokeh kernel with the driver by calling the
 *     add_bokeh_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_bokeh_functions() 
{
    add_bokeh_function(&naive_bokeh, naive_bokeh_descr);   
    add_bokeh_function(&bokeh, bokeh_descr);   
    /* ... Register additional test functions here */
}

/***************************
 * HADAMARD PRODUCT KERNEL *
 ***************************/

/******************************************************
 * Your different versions of the hadamard product functions go here
 ******************************************************/

/* 
 * naive_hadamard - The naive baseline version of hadamard product of two matrices
 */
char naive_hadamard_descr[] = "naive_hadamard The naive baseline version of hadamard product of two matrices";
void naive_hadamard(int dim, int *src1, int *src2, int *dst) {

    int i, j;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[RIDX(i, j, dim)] = src1[RIDX(i, j, dim)] * src2[RIDX(i, j, dim)];
}

/* 
 * hadamard - Your current working version of hadamard product
 * IMPORTANT: This is the version you will be graded on
 */

char hadamard_descr[] = "hadamard: Current working version";
void hadamard(int dim, int *src1, int *src2, int *dst) 
{
    int* src1ptr = src1;
    int* src2ptr = src2;
    int* dstptr = dst;
    int* finalptr = dst + dim * dim;
    while (dstptr < finalptr) {

        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);
        *dstptr++ = (*src1ptr++) * (*src2ptr++);

    }
}
/*********************************************************************
 * register_hadamard_functions - Register all of your different versions
 *     of the hadamard kernel with the driver by calling the
 *     add_hadamard_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_hadamard_functions() 
{
    add_hadamard_function(&naive_hadamard, naive_hadamard_descr);   
    add_hadamard_function(&hadamard, hadamard_descr);   
    /* ... Register additional test functions here */
}

