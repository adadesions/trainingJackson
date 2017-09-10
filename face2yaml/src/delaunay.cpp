#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
  
std::vector<Point2f> getShape( std::string filename, int *num_shapes );

int main(int argc, char *argv[]) {
    std::vector<Point2f> shape;
    std::vector<std::vector<Point2f>> adj_vector;
    int num_shapes = 139*2;
    int num_shapes_filename = 139;
    for(int i = 1; i <= num_shapes_filename; ++i ) {
        string filename1 = "./dataset/"+ to_string(i) + "L.yaml";
        string filename2 = "./dataset/"+ to_string(i) + "R.yaml";
        std::vector<Point2f> shape1 = getShape(filename1, &num_shapes);
        std::vector<Point2f> shape2 = getShape(filename2, &num_shapes);
        adj_vector.push_back(shape1);
        adj_vector.push_back(shape2);
    }
    std::vector<std::vector<Point2f>> mean_shape(1, adj_vector[0]);
    
    for(int i = 1; i < num_shapes; ++i){
        for(int j = 0; j < adj_vector[0].size(); ++j){
            mean_shape[0][j] += adj_vector[i][j];
        }
    }
    
    return 0;
}

std::vector<Point2f> getShape( std::string filename, int *num_shapes ) {
    std::vector<Point2f> zeros( 68, Point2f(0, 0) );
    std::vector<Point2f> point_list;
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    if( !fs.isOpened() ){
        cout << "File not found - " << filename << endl;
        *num_shapes = *num_shapes - 1;
        return zeros; 
    }

    cv::FileNode point_node = fs["features"];
    cv::FileNodeIterator it = point_node.begin();
    cv::FileNodeIterator it_end = point_node.end();

    for(; it != it_end; ++it){
        Point2f point( (*it)["x"], (*it)["y"] );
        point_list.push_back(point);
    }

    return point_list;
}