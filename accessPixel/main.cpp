#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include "mat_vs_vector.h"
#include "mat_access_pixel.h"
#include <fstream>

using namespace cv;
using namespace std;


void add(cv::cuda::GpuMat gpuimg);


#define matNormalize(img) \
{\
    int nr = img.rows; \
    int nc = img.cols * img.channels(); \
    for(int i = 0; i < nr; ++i) \
    { \
        float* data = img.ptr<float>(i); \
        for(int j= 0; j< nc; ++j) \
        { \
            data[j]=  data[j]/255.f; \
        } \
    }\
}

#define matUnnormalize(img) \
{\
    int nr = img.rows; \
    int nc = img.cols * img.channels(); \
    for(int i = 0; i < nr; ++i) \
    { \
        float* data = img.ptr<float>(i); \
        for(int j= 0; j< nc; ++j) \
        { \
            data[j]=  data[j]*255.f; \
        } \
    }\
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    struct timeval st_tm, end_tm;
    static float total_time = 0.0;

    string filename = "as中问";
    fstream fin("/media/lirui/软件备份/公共数据库/DataSet/Synthetic_Chinese_String_Dataset/char_std_5990.txt", ios::in|ios::binary);
    string line;
    std::vector<string> labels;
    while (std::getline(fin, line))
    {
        labels.push_back(string(line));
        cout << line << " ";
    }

//    Mat img = imread("/media/lirui/Program/Datas/bmi_face/0725_prnet/pic_0_crop.jpg");

//    int step = img.step;            // 一行像素总数
//    int elem_size = img.elemSize(); //  element size in byte
//    int depth = img.depth();

//    cout << "step " << step << " elem_size " << elem_size << " depth " << depth << endl;

//    mat_vec_convert(img);

//    compare_access_pixel(img);

//    mat_tmplete_vector(img);
//    img.convertTo(img, CV_32FC3);
//    matNormalize(img);
//    matUnnormalize(img);
//    img.convertTo(img, CV_8UC3);
//    imshow("src", img);
//    waitKey(1);
//    img_normalization(img);

    return a.exec();
}

