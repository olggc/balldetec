#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{

    // Create a VideoCapture object and open the input file
    // If the input is the web camera, pass 0 instead of the video file name
    VideoCapture cap(argv[1]);

    // Check if camera opened successfully
    if (!cap.isOpened())
    {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    CascadeClassifier cascade;
    cascade.load("cascade.xml");

    Mat frame_gray;
    //Mat frame_hsv;
    std::vector<Rect> balls;
    //Mat hsv_channels[3];
    Mat resized_frame(Size(320, 240), CV_8UC3);
    Mat frame;


    while (1)
    {
        // Capture frame-by-frame
        cap >> frame;

        resize(frame, resized_frame, resized_frame.size());
        frame = resized_frame.clone();


        //cvtColor(frame, frame_hsv, CV_BGR2HSV);

        //imshow("hsv", frame_hsv);

        //split(frame_hsv, hsv_channels);
        //frame_gray = hsv_channels[2];
        //imshow("gray", frame_gray);
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        imshow("gray",frame_gray);
        //inRange(frame, Scalar(38, 50, 50), Scalar(75, 255, 255), frame_gray); //problemas aqui


        //cvtColor(frame_hsv, frame, CV_HSV2BGR);
        cascade.detectMultiScale(frame_gray, balls, 1.3, 5, 8, Size(16, 16)); // Rinobot
        //cascade.detectMultiScale(frame_gray, balls, 1.1, 5, 8, Size(16, 16));

        if (balls.size() == 0)
        {
           // cout << "Nao achou nada" << endl;
        }
        else
        {
            double raio = balls[0].width / 2.0f;
            Point pt(balls[0].x + raio, balls[0].y + raio);
           // cout << "Encontrado: " << pt << " [ " << raio << " ] " << endl;
            circle(frame, pt, raio, Scalar(0, 0, 255), CV_FILLED);
        }

        imshow("frame", frame);

        // Press  ESC on keyboard to exit
        char c = (char)waitKey(25);
        if (c == 27)
            break;
    }

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    destroyAllWindows();

    return 0;
}