#ifndef MAT_ACCESS_PIXEL_H
#define MAT_ACCESS_PIXEL_H
#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include "simple_timer.h"

//---------------------CUDA头文件----------------
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <cuda_device_runtime_api.h>
//---------------------CUDA头文件----------------

using namespace cv;
using namespace std;
#define EXEC_CLONE


// uchar *data = img.ptr<uchar>(row_id);  data[col_id]
void ptr_access(Mat & img, int div=64)
{
#ifdef EXEC_CLONE
    Mat tmp = img.clone();
#else
    Mat tmp = img;
#endif

    int nr= tmp.rows;
    int nc= tmp.cols * tmp.channels();
    for (int j=0; j<nr; j++) {
        uchar* data= tmp.ptr<uchar>(j);
        for (int i=0; i<nc; i++) {
                data[i]= data[i]/div*div + div/2;
          }
    }
}

// img.at<cv::Vec3b>(i,j)[ch] i行 j列元素 bgr
void at_access(Mat & img, int div=64)
{
#ifdef EXEC_CLONE
    Mat tmp = img.clone();
#else
    Mat tmp = img;
#endif
    for(int i = 0; i < tmp.rows; ++i)  {
        for(int j= 0; j< tmp.cols; ++j)  {
            tmp.at<cv::Vec3b>(i, j)[0] = tmp.at<cv::Vec3b>(i, j)[0]/div*div + div/2;
            tmp.at<cv::Vec3b>(i, j)[1] = tmp.at<cv::Vec3b>(i, j)[1]/div*div + div/2;
            tmp.at<cv::Vec3b>(i, j)[2] = tmp.at<cv::Vec3b>(i, j)[2]/div*div + div/2;
        }
    }
}


// uchar *data = img.ptr<uchar>(row_id);  *data++
void ptrXX_access(cv::Mat &img, int div=64)
{
#ifdef EXEC_CLONE
    Mat tmp = img.clone();
#else
    Mat tmp = img;
#endif
    int nr= tmp.rows; // number of rows
    int nc= tmp.cols * tmp.channels(); // total number of elements per line
    for (int j=0; j<nr; j++) {
        uchar* data= tmp.ptr<uchar>(j);
        for (int i=0; i<nc; i++) {
             *data++= *data/div*div + div/2;
        } // end of row
    }
}


// using Mat_ iterator
void matIter_access(cv::Mat &img, int div=64)
{
#ifdef EXEC_CLONE
    Mat tmp = img.clone();
#else
    Mat tmp = img;
#endif
      // get iterators
      cv::Mat_<cv::Vec3b>::iterator it= tmp.begin<cv::Vec3b>();
      cv::Mat_<cv::Vec3b>::iterator itend= tmp.end<cv::Vec3b>();
      for ( ; it!= itend; ++it) {
        (*it)[0]= (*it)[0]/div*div + div/2;
        (*it)[1]= (*it)[1]/div*div + div/2;
        (*it)[2]= (*it)[2]/div*div + div/2;
      }
}

// using .ptr and []
void colorReduce0(cv::Mat &image, int div=64) {
      int nr= image.rows; // number of rows
      int nc= image.cols * image.channels(); // total number of elements per line
      for (int j=0; j<nr; j++) {
          uchar* data= image.ptr<uchar>(j);
          for (int i=0; i<nc; i++) {
                  data[i]= data[i]/div*div + div/2;
            }
      }
}


void compare_access_pixel(Mat img)
{
    int cnt = 1000;
    // 1. ptr 指针和[]访问
    {
        SimpleTimer timer("ptr_access");
        for (int i=0; i<cnt; ++i)
            ptr_access(img, 32);
    }

    // 2. img.at<cv::Vec3b>(i, j)[ch] 访问
    {
        SimpleTimer timer("at_access");
        for (int i=0; i<cnt; ++i)
            at_access(img, 32);
    }

    // 3. ptr 指针和*data++
    {
        SimpleTimer timer("ptrXX_access");
        for (int i=0; i<cnt; ++i)
            ptrXX_access(img, 32);
    }

    // 4. cv::Mat_<cv::Vec3b>::iterator 或cv::MatIterator_<uchar>
    {
        SimpleTimer timer("matIter_access");
        for (int i=0; i<cnt; ++i)
            matIter_access(img, 32);
    }
}

#include "simple_timer.h"
void img_normalization(Mat img)
{

    Mat img_float;
    img.convertTo(img_float, CV_32F);

    Mat scale(img_float.rows, img_float.cols, CV_32FC3, Scalar(255,255,255));

    vector<float> data_src;
    data_src.assign((float*)img_float.datastart, (float*)img_float.dataend);

    cout << "before " << endl;
    for(int i=0; i<100; ++i)
        cout << data_src[i] << "    ";
    cout << "\n";
    Mat tmp;
    {
        SimpleTimer timer("cpu");
        divide(img_float, scale, tmp);
    }

    cuda::GpuMat scaleGpu, tmpGpu, imgGpu;
    scaleGpu.upload(scale);
    imgGpu.upload(img_float);

    {
        SimpleTimer timer("gpu");
        cuda::divide(imgGpu, scaleGpu, tmpGpu);
    }
    Mat tmp2;
    tmpGpu.download(tmp2);

    data_src.assign((float*)tmp2.datastart, (float*)tmp2.dataend);
    cout << "after " << endl;
    for(int i=0; i<100; ++i)
        cout << data_src[i] << "    ";



}



#endif // MAT_ACCESS_PIXEL_H
