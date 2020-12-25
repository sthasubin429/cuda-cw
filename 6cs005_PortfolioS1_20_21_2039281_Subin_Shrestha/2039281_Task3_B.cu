#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#include "lodepng.h"

__global__ void calc(unsigned char* img, int* height, int* width){
    int a = threadIdx.x; //height
    int b = blockIdx.x; //width
    int c = blockDim.x; //dimentions
    int count = blockDim.x * threadIdx.x + blockIdx.x;
    
    printf("a: %d, b: %d, c: %d, count: %d ,height: %d, width: %d \n", a,b,c,count, height,width);
}

int main(int argc, char **argv){

  cudaError_t cudaError;
	unsigned int error;
	//unsigned int encError;
	unsigned char* image;
	unsigned int width;
	unsigned int height;
	const char* filename = "hck.png";
  //const char* newFileName = "generated.png";

  
	error = lodepng_decode32_file(&image, &width, &height, filename);

  unsigned char r[height*width];
	unsigned char g[height*width];
	unsigned char b[height*width];
	unsigned char t[height*width]; //transparency
	
  if(error){
		printf("error %u: %s\n", error, lodepng_error_text(error));
  }

   printf("width = %d height = %d\n", width, height);
    for(int i = 0; i<height*width*4; i=i+4){
      r[i/4] = image[i];
      g[i/4] = image[1+i];
      b[i/4] = image[2+i];
      t[i/4] = image[3+i];
    }
  const int ARRAY_BYTES = height*width * sizeof(unsigned char);

  //declare GPU memopry height and width
  unsigned int * d_height, d_width;
  //allocate GPU memory for height and width
  cudaMalloc((void**) &d_height, sizeof(int));
  cudaMalloc((void**) &d_width, sizeof(int));
  //Memory copy for height and weidth
  cudaMemcpy(d_height, &height, sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(d_width, &width, sizeof(int), cudaMemcpyHostToDevice);

  // declare GPU memory pointers for rgbt arrays
  unsigned char * d_red;
  unsigned char * d_red_out;

  // allocate GPU memory For rgbt arrays
  cudaMalloc((void**) &d_red, ARRAY_BYTES);
  cudaMalloc((void**) &d_red_out, ARRAY_BYTES);

  //Memory copy
  cudaMemcpy(d_red, r, ARRAY_BYTES, cudaMemcpyHostToDevice);
  //<<<blockid.x,threadid.x >>>
  calc<<<width, height>>>(d_red);
  //calc<<<1, 1>>>(d_red, d_height, d_width);

  cudaDeviceSynchronize();
  cudaError = cudaGetLastError();
  
  if(cudaError){
    fprintf(stderr, "Kernel launch returned %d %s\n", 
    cudaError, cudaGetErrorString(cudaError));
    return 1;
  } else {
    fprintf(stderr, "Kernel launch successful.\n");
  }     
      
	return 0;
}