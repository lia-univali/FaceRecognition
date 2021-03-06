/* 
 * File:   main.cpp
 * Author: viniciusas
 *
 * Created on 25/11/2016, 16:11
 *
 *
 * May need for some cameras:
 * LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libv4l/v4l2convert.so  ./compiled_file
 *
 *
 */

#include <glibmm-2.4/glibmm/refptr.h>
using namespace Glib;

#include <gtkmm-3.0/gtkmm/application.h>
using namespace Gtk;

#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "appwindow.h"
#include "facerecognizer.h"

void initServices(AppWindow *appWindow, bool *appRunning){
    cv::VideoCapture capture;
    
    if ( !capture.open( 0 ) ){
        printf("Error opening video capture\n");
        return;
    }
    
    cv::Mat frame;
    while ( capture.read(frame) && *appRunning )
    {
        if (frame.empty()){
            printf("No captured frame\n");
            break;
        }
        appWindow->setFrame(frame);
    }
    capture.release();
}

int justTrain(){
    FaceRecognizer faceRecognition;
    if (!faceRecognition.init(FaceRecognizer::InitType::TRAIN)){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char**argv) {

    if ( argc > 1 && strcmp(argv[1],"train") == 0 ){
        return justTrain();
    }

    bool isRunning = true;
    
    RefPtr<Application> app = Application::create( "br.univali.lia.FaceRecognition" );
    AppWindow appWindow;
    
    std::thread services( initServices, &appWindow, &isRunning );
    int ret = app->run( appWindow, argc, argv );
    
    isRunning = false;
    services.join();
    appWindow.finish();
    
    return ret;
}
