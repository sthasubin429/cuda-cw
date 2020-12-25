#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#include "lodepng.h"

__global__ void gaussian_red(unsigned char* img_in, unsigned char* img_out){
    int a = threadIdx.x; //height
    int b = blockIdx.x; //width
    int c = blockDim.x; //dimentions
    int count = blockDim.x * threadIdx.x + blockIdx.x;

    int weight_mat[9] = {1,2,1,2,4,2,1,2,1};
    int sum;
    
    signed int num[9][2];
    num[0][0] = a-1;
    num[0][1] = b-1;
    num[1][0] = a-1;
    num[1][1] = b;
    num[2][0] = a-1;
    num[2][1] = b+1;
    num[3][0] = a;
    num[3][1] = b-1;
    num[4][0] = a;
    num[4][1] = b;
    num[5][0] = a;
    num[5][1] = b+1;
    num[6][0] = a+1;
    num[6][1] = b-1;
    num[7][0] = a+1;
    num[7][1] = b;
    num[8][0] = a+1;
    num[8][1] = b+1;

    int mat[9];
    for(int i =0;i<9;i++){
        if(num[i][0] < 0 || num[i][1] < 0 || num[i][0] > 3|| num[i][1]>3){
            mat[i] = -1;
        }
        else{
            mat[i] = num[i][0] + c*num[i][1];
        }
    }
    sum=0;
    for(int i=0;i<9;i++){
        if(mat[i] == -1){
            sum = sum + (0*weight_mat[i]);
        }
        else{
            
            sum = sum + (img_in[mat[i]]*weight_mat[i]);
        }
    }
    sum = sum/16;

    img_out[4*count] = sum;

    //printf("%d ", sum);
    //printf("a: %d, b: %d, c: %d, count: %d \n", a,b,c,count);
}
__global__ void gaussian_green(unsigned char* img_in, unsigned char* img_out){
    int a = threadIdx.x; //height
    int b = blockIdx.x; //width
    int c = blockDim.x; //dimentions
    int count = blockDim.x * threadIdx.x + blockIdx.x;

    int weight_mat[9] = {1,2,1,2,4,2,1,2,1};
    int sum;
    
    signed int num[9][2];
    num[0][0] = a-1;
    num[0][1] = b-1;
    num[1][0] = a-1;
    num[1][1] = b;
    num[2][0] = a-1;
    num[2][1] = b+1;
    num[3][0] = a;
    num[3][1] = b-1;
    num[4][0] = a;
    num[4][1] = b;
    num[5][0] = a;
    num[5][1] = b+1;
    num[6][0] = a+1;
    num[6][1] = b-1;
    num[7][0] = a+1;
    num[7][1] = b;
    num[8][0] = a+1;
    num[8][1] = b+1;

    int mat[9];
    for(int i =0;i<9;i++){
        if(num[i][0] < 0 || num[i][1] < 0 || num[i][0] > 3|| num[i][1]>3){
            mat[i] = -1;
        }
        else{
            mat[i] = num[i][0] + c*num[i][1];
        }
    }
    sum=0;
    for(int i=0;i<9;i++){
        if(mat[i] == -1){
            sum = sum + (0*weight_mat[i]);
        }
        else{
            
            sum = sum + (img_in[mat[i]]*weight_mat[i]);
        }
    }
    sum = sum/16;

    img_out[(4*count)+1] = sum;

    //printf("%d ", sum);
    //printf("a: %d, b: %d, c: %d, count: %d \n", a,b,c,count);
}
__global__ void gaussian_blue(unsigned char* img_in, unsigned char* img_out){
    int a = threadIdx.x; //height
    int b = blockIdx.x; //width
    int c = blockDim.x; //dimentions
    int count = blockDim.x * threadIdx.x + blockIdx.x;

    int weight_mat[9] = {1,2,1,2,4,2,1,2,1};
    int sum;
    
    signed int num[9][2];
    num[0][0] = a-1;
    num[0][1] = b-1;
    num[1][0] = a-1;
    num[1][1] = b;
    num[2][0] = a-1;
    num[2][1] = b+1;
    num[3][0] = a;
    num[3][1] = b-1;
    num[4][0] = a;
    num[4][1] = b;
    num[5][0] = a;
    num[5][1] = b+1;
    num[6][0] = a+1;
    num[6][1] = b-1;
    num[7][0] = a+1;
    num[7][1] = b;
    num[8][0] = a+1;
    num[8][1] = b+1;

    int mat[9];
    for(int i =0;i<9;i++){
        if(num[i][0] < 0 || num[i][1] < 0 || num[i][0] > 3|| num[i][1]>3){
            mat[i] = -1;
        }
        else{
            mat[i] = num[i][0] + c*num[i][1];
        }
    }
    sum=0;
    for(int i=0;i<9;i++){
        if(mat[i] == -1){
            sum = sum + (0*weight_mat[i]);
        }
        else{
            
            sum = sum + (img_in[mat[i]]*weight_mat[i]);
        }
    }
    sum = sum/16;

    img_out[(4*count)+2] = sum;

    //printf("%d ", sum);
    //printf("a: %d, b: %d, c: %d, count: %d \n", a,b,c,count);
}
__global__ void gaussian_transparent(unsigned char* img_in, unsigned char* img_out){
    int a = threadIdx.x; //height
    int b = blockIdx.x; //width
    int c = blockDim.x; //dimentions
    int count = blockDim.x * threadIdx.x + blockIdx.x;

    int weight_mat[9] = {1,2,1,2,4,2,1,2,1};
    int sum;
    
    signed int num[9][2];
    num[0][0] = a-1;
    num[0][1] = b-1;
    num[1][0] = a-1;
    num[1][1] = b;
    num[2][0] = a-1;
    num[2][1] = b+1;
    num[3][0] = a;
    num[3][1] = b-1;
    num[4][0] = a;
    num[4][1] = b;
    num[5][0] = a;
    num[5][1] = b+1;
    num[6][0] = a+1;
    num[6][1] = b-1;
    num[7][0] = a+1;
    num[7][1] = b;
    num[8][0] = a+1;
    num[8][1] = b+1;

    int mat[9];
    for(int i =0;i<9;i++){
        if(num[i][0] < 0 || num[i][1] < 0 || num[i][0] > 3|| num[i][1]>3){
            mat[i] = -1;
        }
        else{
            mat[i] = num[i][0] + c*num[i][1];
        }
    }
    sum=0;
    for(int i=0;i<9;i++){
        if(mat[i] == -1){
            sum = sum + (0*weight_mat[i]);
        }
        else{
            
            sum = sum + (img_in[mat[i]]*weight_mat[i]);
        }
    }
    sum = sum/16;

    img_out[(4*count)+3] = sum;

    //printf("%d ", sum);
    //printf("a: %d, b: %d, c: %d, count: %d \n", a,b,c,count);
}
int main(int argc, char **argv){

  cudaError_t cudaError;
	unsigned int error;
	unsigned int encError;
	unsigned char* image;
	unsigned int width;
	unsigned int height;
	const char* filename = "4x4.png";
  const char* newFileName = "generated.png";

  
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

  printf("\n");
  const int ARRAY_BYTES = height*width * sizeof(unsigned char);
  unsigned char h_output[height*width*4];


  // declare GPU memory pointers for rgbt arrays
  unsigned char * d_red;
  unsigned char * d_green;
  unsigned char * d_blue;
  unsigned char * d_transparent;

  unsigned char * d_output;

  // allocate GPU memory For rgbt arrays
  cudaMalloc((void**) &d_red, ARRAY_BYTES);
  cudaMalloc((void**) &d_green, ARRAY_BYTES);
  cudaMalloc((void**) &d_blue, ARRAY_BYTES);
  cudaMalloc((void**) &d_transparent, ARRAY_BYTES);

  cudaMalloc((void**) &d_output, ARRAY_BYTES);

  //Memory copy
  cudaMemcpy(d_red, r, ARRAY_BYTES, cudaMemcpyHostToDevice);
  cudaMemcpy(d_green, g, ARRAY_BYTES, cudaMemcpyHostToDevice);
  cudaMemcpy(d_blue, b, ARRAY_BYTES, cudaMemcpyHostToDevice);
  cudaMemcpy(d_transparent, t, ARRAY_BYTES, cudaMemcpyHostToDevice);

  //<<<blockid.x,threadid.x >>>
  gaussian_red<<<width, height>>>(d_red, d_output);
  gaussian_red<<<width, height>>>(d_green, d_output);
  gaussian_red<<<width, height>>>(d_blue, d_output);
  gaussian_red<<<width, height>>>(d_transparent, d_output);

  cudaDeviceSynchronize();
  // copy back the result array to the CPU
  cudaMemcpy(h_output, d_output, ARRAY_BYTES, cudaMemcpyDeviceToHost);
  
  for(int i = 0; i<height*width*4; i=i+4){
      printf("%d %d %d %d\n", h_output[i], h_output[i+1], h_output[i+2], h_output[i+3]);
  }
  cudaError = cudaGetLastError();
  
  if(cudaError){
    fprintf(stderr, "Kernel launch returned %d %s\n", 
    cudaError, cudaGetErrorString(cudaError));
    return 1;
  } else {
    fprintf(stderr, "Kernel launch successful.\n");
  }
  encError = lodepng_encode32_file(newFileName, h_output, width, height);
	if(encError){
		printf("error %u: %s\n", error, lodepng_error_text(encError));
	}
       
      
	return 0;
}