//nvcc 2039281_Task3_B.cu lodepng.cpp -o task3_B 
//task3_B hck.png
#include "lodepng.h"
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime_api.h>
__device__ unsigned int width;
__device__ unsigned int height;
__device__ unsigned char getRed(unsigned char *image, unsigned int row, unsigned int col){
  unsigned int i = (row * width * 4) + (col * 4);
  return image[i];
}

__device__ unsigned char getGreen(unsigned char *image, unsigned int row, unsigned int col){
  unsigned int i = (row * width * 4) + (col * 4) +1;
  return image[i];
}

__device__ unsigned char getBlue(unsigned char *image, unsigned int row, unsigned int col){
  unsigned int i = (row * width * 4) + (col * 4) +2;
  return image[i];
}

__device__ unsigned char getAlpha(unsigned char *image, unsigned int row, unsigned int col){
  unsigned int i = (row * width * 4) + (col * 4) +3;
  return image[i];
}

__device__ void setRed(unsigned char *image, unsigned int row, unsigned int col, unsigned char red){
  unsigned int i = (row * width * 4) + (col * 4);
  image[i] = red;
}

__device__ void setGreen(unsigned char *image, unsigned int row, unsigned int col, unsigned char green){
  unsigned int i = (row * width * 4) + (col * 4) +1;
  image[i] = green;
}

__device__ void setBlue(unsigned char *image, unsigned int row, unsigned int col, unsigned char blue){
  unsigned int i = (row * width * 4) + (col * 4) +2;
  image[i] = blue;
}

__device__ void setAlpha(unsigned char *image, unsigned int row, unsigned int col, unsigned char alpha){
  unsigned int i = (row * width * 4) + (col * 4) +3;
  image[i] = alpha;
}

__global__ void cudaBlur(unsigned char* img_in, unsigned char* newImage){
    if(blockIdx.x == 0 || threadIdx.x == 0 ){

    }
    else{
        float filter[3][3] = {
  { 1.0/16, 2.0/16, 1.0/16 },
  { 2.0/16, 4.0/16, 2.0/16 },
  { 1.0/16, 2.0/16, 1.0/16 }};

    unsigned redTL,redTC, redTR;
    unsigned redL, redC, redR;
    unsigned redBL,redBC, redBR;
    unsigned newRed;

    unsigned greenTL,greenTC, greenTR;
    unsigned greenL, greenC, greenR;
    unsigned greenBL,greenBC, greenBR;
    unsigned newGreen;

    unsigned blueTL,blueTC, blueTR;
    unsigned blueL, blueC, blueR;
    unsigned blueBL,blueBC, blueBR;
    unsigned newBlue;

    int row = threadIdx.x;
    int col = blockIdx.x;

      setGreen(newImage, row, col, getGreen(img_in, row, col));
      setBlue(newImage, row, col, getBlue(img_in, row, col));
      setAlpha(newImage, row, col, 255);		

      redTL = getRed(img_in, row-1, col-1);
      redTC = getRed(img_in, row-1, col);
      redTR = getRed(img_in, row-1, col+1);

      redL = getRed(img_in, row, col-1);
      redC = getRed(img_in, row, col);
      redR = getRed(img_in, row, col+1);

      redBL = getRed(img_in, row+1, col-1);
      redBC = getRed(img_in, row+1, col);
      redBR = getRed(img_in, row+1, col+1);

      newRed = redTL*filter[0][0] + redTC*filter[0][1] + redTR*filter[0][2]
             + redL*filter[1][0]  + redC*filter[1][1]  + redR*filter[1][2]
             + redBL*filter[2][0] + redBC*filter[2][1] + redBR*filter[2][2];
 
      setRed(newImage, row, col, newRed);

      greenTL = getGreen(img_in, row-1, col-1);
      greenTC = getGreen(img_in, row-1, col);
      greenTR = getGreen(img_in, row-1, col+1);

      greenL = getGreen(img_in, row, col-1);
      greenC = getGreen(img_in, row, col);
      greenR = getGreen(img_in, row, col+1);

      greenBL = getGreen(img_in, row+1, col-1);
      greenBC = getGreen(img_in, row+1, col);
      greenBR = getGreen(img_in, row+1, col+1);

      newGreen = greenTL*filter[0][0] + greenTC*filter[0][1] + greenTR*filter[0][2]
             + greenL*filter[1][0]  + greenC*filter[1][1]  + greenR*filter[1][2]
             + greenBL*filter[2][0] + greenBC*filter[2][1] + greenBR*filter[2][2];
 
      setGreen(newImage, row, col, newGreen);

      blueTL = getBlue(img_in, row-1, col-1);
      blueTC = getBlue(img_in, row-1, col);
      blueTR = getBlue(img_in, row-1, col+1);

      blueL = getBlue(img_in, row, col-1);
      blueC = getBlue(img_in, row, col);
      blueR = getBlue(img_in, row, col+1);

      blueBL = getBlue(img_in, row+1, col-1);
      blueBC = getBlue(img_in, row+1, col);
      blueBR = getBlue(img_in, row+1, col+1);

      newBlue = blueTL*filter[0][0] + blueTC*filter[0][1] + blueTR*filter[0][2]
             + blueL*filter[1][0]  + blueC*filter[1][1]  + blueR*filter[1][2]
             + blueBL*filter[2][0] + blueBC*filter[2][1] + blueBR*filter[2][2];
 
      setBlue(newImage, row, col, newBlue);        
    }
    
}

__global__ void setDimentions(unsigned int givenWidth, unsigned int givenHeight){
    width = givenWidth;
    height = givenHeight;
    
}

int main(int argc, char **argv){
    unsigned char *image;
    unsigned int w;
    unsigned int h;
    const char* filename = argv[1];
    const char* img_output = "generated.png";
    unsigned char* output_raw;
    cudaError_t error;
    
    lodepng_decode32_file(&image, &w, &h, filename);
    
    printf("width = %d height = %d\n", w, h);

    setDimentions<<<1,1>>>(w, h);

    unsigned char * d_image;
    const int ARRAY_BYTES = h*w*4 * sizeof(unsigned char);

    output_raw = (unsigned char *)malloc(ARRAY_BYTES);

    cudaMalloc((void**) &d_image, ARRAY_BYTES);
    cudaMemcpy(d_image, image, ARRAY_BYTES, cudaMemcpyHostToDevice);

    unsigned char * d_out;
    cudaMalloc((void**) &d_out, ARRAY_BYTES);

    cudaBlur<<<w-1, h-1>>>(d_image, d_out);
    //Declaration of cuda thread synchronize
    error = cudaGetLastError();
    if(error){
      fprintf(stderr, "Kernel launch returned %d %s\n", error,
        cudaGetErrorString(error));
      exit(1);
    }
    cudaDeviceSynchronize();

    cudaMemcpy(output_raw, d_out, ARRAY_BYTES, cudaMemcpyDeviceToHost);

    
    lodepng_encode32_file(img_output, output_raw, w, h);

    free(image);

    return 0;
}