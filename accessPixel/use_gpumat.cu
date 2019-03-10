#include "mat_access_pixel.h"

//---------------------CUDA头文件----------------
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <cuda_device_runtime_api.h>
//---------------------CUDA头文件----------------

__global__ void VecAdd(float* A)
{
    int i = threadIdx.x;
    A[i] = A[i] /16;
}
void add(cv::cuda::GpuMat gpuimg)
{
    VecAdd<<<1, 30>>>(gpuimg.data);
}
