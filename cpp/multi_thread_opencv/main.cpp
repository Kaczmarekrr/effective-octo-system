#include <stdio.h>
#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include <queue>
#include <chrono>
void producer_thread(std::deque<cv::Mat> *dq)
{
    // opencv stuff
    cv::VideoCapture camera(0); // in linux check $ ls /dev/video0
    if (!camera.isOpened())
    {
        std::cerr << "ERROR: Could not open camera" << std::endl;
    }

    // create a window to display the images from the webcam

    // array to hold image
    cv::Mat frame;

    // display the frame until you press a key
    for (int i = 0; i < 60; i++)
    {
        // capture the next frame from the webcam
        camera >> frame;
        dq->push_back(frame.clone());
        std::cout << "Size of dq in producer " << dq->size() << std::endl;
        cv::waitKey(30);
    }
}

void consumer_thread(std::deque<cv::Mat> *dq)
{
    cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);

    cv::Mat frame;

    if (dq->size() < 10)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    while (dq->size() > 0)
    {
        // capture the next frame from the webcam
        frame = dq->front();
        dq->pop_front();
        // show the image on the window
        cv::imshow("Webcam", frame);
        // wait (10ms) for esc key to be pressed to stop
        if (cv::waitKey(30) == 27)
            break;
        std::cout << "Size of dq in consumer " << dq->size() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void result_presentation_thread()
{
    // result and camera view
}

int main(int argc, char *argv[])
{

    std::deque<cv::Mat> dq;

    std::thread th1(producer_thread, &dq);
    std::thread th2(consumer_thread, &dq);

    th1.join();
    th2.join();
    return 0;
}


// Next steps
//
// 1. Add Mediapipe and possible TFlite to the project
// 2. Run Mediapipe landmarks if correct - This will be a good part of advancemnt
// 3. Prepare to get values around markers 
// 4. Add kissFFT
// 5. Get fft (maybe filtering too?)
// 6. Get bpm values
//