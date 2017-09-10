#include <iostream>
#include <opencv2/opencv.hpp>
#include <openada.hpp>


using namespace std;
// using namespace dlib;
using namespace cv;

int main(int argc, char *argv[]) {
    Mat plane, mean_plane;
    plane = Mat(Size(512,512)*2, CV_64FC3);
    mean_plane = Mat(Size(512,512), CV_64FC3);

    std::vector<Vec6f> vertices;
    std::vector<Point2f> mean(3, Point2f(0,0));
    Scalar color(0, 0, 255);
    int numShapes = 3;

    for(int m = 1; m <= numShapes; ++m){
        char orientation = m%2 == 0 ? 'L' : 'R';
        string filename = to_string(m)+'L';
        
        vertices = opa::getDelaunayVec6f("../face2yaml/dataset/"+filename+".yaml");
        if( vertices.size() == 0 ){
            cout << filename << endl;
            continue;
        }
        // plane = opa::getTexture("../face2yaml/dataset/"+filename+".yaml");
        for(int i = 0; i < vertices.size(); ++i){
           std::vector<Point2f> v = opa::getTrianglePiece(i, vertices);
           Rect rect(0,0, plane.rows, plane.cols);
           if( rect.contains(v[0]) &&  rect.contains(v[1]) && rect.contains(v[2]) ){
            line(plane, v[0], v[1], color);
            line(plane, v[1], v[2], color);
            line(plane, v[2], v[0], color);  
           }
        }
        imshow("Plane: "+to_string(m), plane);
        plane = Mat::zeros( plane.size(), plane.type() );
    }
    // imshow("Test", plane);
    
    waitKey(0);
    return 0;
}