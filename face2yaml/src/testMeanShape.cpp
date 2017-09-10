#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){
    FileStorage fs("./dataset/meanShape.yaml", FileStorage::READ);
    FileNode features = fs["features"];
    std::vector<Point2f> mean_points;
    for( auto mp:features ){
        Point2f p( (int)mp["x"], (int)mp["y"] );
        mean_points.push_back(p);
    }

    Mat plane( Size(512,512), CV_32FC3 );

    // Get Delaunay list
    Rect rect(0, 0, plane.cols, plane.rows);
    Subdiv2D subdiv(rect);
    subdiv.insert(mean_points);
    std::vector<Vec6f> triangle_list;
    subdiv.getTriangleList(triangle_list);

    // transform delaunay Vec6f to points index<Vec3f>
    std::vector<Vec3f> index_triangle;
    for(auto p:triangle_list){
        Vec3f store = {-1, -1, -1};
        Point2f tri[3];
        tri[0] = Point2f( p[0], p[1]);
        tri[1] = Point2f( p[2], p[3]);
        tri[2] = Point2f( p[4], p[5]);
        for(int i = 0; i < mean_points.size(); ++i) {
            if( rect.contains(tri[0]) && rect.contains(tri[1]) && rect.contains(tri[2]) ){
                if( tri[0] == mean_points[i] )
                    store[0] = i;
                else if( tri[1] == mean_points[i] )
                    store[1] = i;
                else if( tri[2] == mean_points[i] )
                    store[2] = i;
            }
            if( store[0] > -1 && store[1] > -1 && store[2] > -1 )
                break;
        }
        if( store[0] != -1 && store[1] != -1 && store[2] != -1 ){
            index_triangle.push_back(store); 
            cout << store << endl;
        }
            
    }
    
    for( auto it:index_triangle){
        line(plane, mean_points[it[0]], mean_points[it[1]], Scalar(0,0,255), 1);
        line(plane, mean_points[it[1]], mean_points[it[2]], Scalar(0,0,255), 1);
        line(plane, mean_points[it[2]], mean_points[it[0]], Scalar(0,0,255), 1);
    }
        
    
    imshow("Mean Shape", plane);
    waitKey(0);

    return 0;
}