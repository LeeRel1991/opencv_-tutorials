#ifndef MAT_VS_VECTOR_H
#define MAT_VS_VECTOR_H
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void print(int x)
{
    cout << x << endl;
}

void Swap(vector<string>& source, vector<string>& dest)
{
//    DebugUtility temp;
    dest.swap(source);
}

void Assign(vector<string>& source, vector<string>& dest)
{
//    DebugUtility temp;
    dest.assign(source.begin(), source.end());
}


void mat_vec_convert(Mat img)
{

    vector<uchar> vec_uchar;
    vec_uchar.assign ( ( uchar* )img.datastart, ( uchar* )img.dataend );

    Mat img_float;
    img.convertTo(img_float, CV_32FC3);
    vector<float> vec_float;
    vec_float.assign( (float*)img_float.datastart, (float*)img_float.dataend);
    vec_float[0] = 255;
    vec_float[2] = 0;

    float p0 = img_float.ptr<float>(0)[0];
    float p2 = img_float.ptr<float>(0)[2];


    vector<string> source(10, "90");
    vector<string> destination(1, "abc");


}

#include "simple_timer.h"
void mat_tmplete_vector(Mat img)
{
    int cnt = 1000;
    int num = 65536;
    Mat_<Point2f> matrix(num, 1);
    vector<Point2f> vec_point(num);

    // 访问 与赋值
    {
        SimpleTimer timer("mat_ access");
        for(int k = 0; k < cnt; ++k){
            for(int i=0; i< num; ++i) {
                float* data = matrix.ptr<float>(i);
                for(int j =0; j < matrix.cols; ++j){
                    *data++ = 255;
                }
            }
        }
    }
    vector<Point2f> tmp;
    tmp =  matrix;
    for(auto p:tmp){
        cout<< "point " << p << "\n";// << p.y << endl;
    }

    {
        SimpleTimer timer("vec_point access");
        for(int k = 0; k < cnt; ++k){
            for(auto &p:vec_point) {
                p.x = 255;
                p.y = 255;
//                p.z = 255;
//                p.width = 255;
//                p.height = 255;
            }
        }
    }

    Mat_<float> matrix1(num, 4);
    vector<Rect2f> vec_point1(num);

    // 访问 与赋值
    {
        SimpleTimer timer("mat_ access");
        for(int k = 0; k < cnt; ++k){
            for(int i=0; i< num; ++i) {
                float* data = matrix1.ptr<float>(i);
                for(int j =0; j < 4; ++j){
                    *data++ = 255;
                }
            }
        }
    }
    {
        SimpleTimer timer("vec_point access");
        for(int k = 0; k < cnt; ++k){
            for(auto &p:vec_point1) {
                p.x = 255;
                p.y = 255;
                p.width = 255;
                p.height = 255;
            }
        }
    }
}





#endif // MAT_VS_VECTOR_H
