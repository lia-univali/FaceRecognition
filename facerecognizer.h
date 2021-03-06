
/* 
 * File:   FaceRecognizer.h
 * Author: viniciusas
 *
 * Created on 30 de Novembro de 2016, 13:28
 */

#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H

#include <vector>
#include <map>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
using namespace cv;

#include "queueface.h"
#include "recognizedfaceslist.h"

class FaceRecognizer {

public:
    enum InitType { LOAD, TRAIN };

    FaceRecognizer();
    FaceRecognizer(RecognizedFacesList *recognizedList);
    bool init(FaceRecognizer::InitType initType);
    void recognize(QueueFace &face);
    
private:
    const int num_components = 80;
    const double threshold = DBL_MAX;
    Ptr<face::FaceRecognizer> recognizer;
    
    RecognizedFacesList *recognizedList;

    int im_width = 300; //0;
    int im_height = 300; //0
    const std::string imagesize_train_file = "./train/imagesize-train.yml";
    const std::string train_file = "./train/train.yml";
    const std::string labels_file = "./labels.csv";
    const std::string faces_file = "./faces.csv";
    void loadNamesFile();
    void loadFacesDatabaseFile();
    void normalizeImages();
    bool cropFace(Mat &image);

    vector<cv::Mat> images;
    vector<int> labels;
    map<int,std::string> names;
    
};

#endif /* FACERECOGNIZER_H */

