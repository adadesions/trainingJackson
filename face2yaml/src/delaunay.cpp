#include <iostream>
#include <opencv2/opencv.hpp>
#include <dlib/matrix.h>

using namespace std;
using namespace cv;
using namespace dlib;
  
std::vector<Point2f> getShape( std::string filename, int& num_shapes ) {
    std::vector<Point2f> zeros( 68, Point2f(0, 0) );
    std::vector<Point2f> point_list;
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    if( !fs.isOpened() ){
        cout << "File not found - " << filename << endl;
        num_shapes = num_shapes - 1;
        return zeros; 
    }

    cv::FileNode point_node = fs["features"];
    cv::FileNodeIterator it = point_node.begin();
    cv::FileNodeIterator it_end = point_node.end();

    for(; it != it_end; ++it){
        Point2f point( (*it)["x"], (*it)["y"] );
        point_list.push_back(point);
    }
    fs.release();

    return point_list;
}

int main(int argc, char *argv[]) {
    std::vector<Point2f> shape;
    std::vector<std::vector<Point2f>> adj_vector;
    int num_shapes = 5*2;
    int num_shapes_filename = 5;
    for(int i = 1; i <= num_shapes_filename; ++i ) {
        string left_filename = "./dataset/"+ to_string(i) + "L.yaml";
        string right_filename = "./dataset/"+ to_string(i) + "R.yaml";
        std::vector<Point2f> left_shape = getShape(left_filename, num_shapes);
        std::vector<Point2f> right_shape = getShape(right_filename, num_shapes);
        adj_vector.push_back(left_shape);
        adj_vector.push_back(right_shape);
    }
    matrix<std::vector<Point2f>> d_mat = dlib::mat(adj_vector);
    matrix<std::vector<Point2f>, 1, 68> mean_mat;
    for( int i = 0; i < d_mat.nr(); ++i ){
        cout << d_mat(i) << endl;
    }
    cout << mean_mat << endl;
  
    // std::vector<Point2f> sum_shape;
    // Point2f sum_point;
    
    // for(int i = 0; i < num_shapes; ++i){
    //     sum_point = Point2f( 0, 0) ;
    //     for(int j = 0; j < adj_vector[0].size(); ++j)
    //         sum_point += adj_vector[i][j];

    //     sum_shape.push_back( sum_point/num_shapes );
    // }
    // cout << sum_shape << endl;

    // // Writing Points
    // int index = 0;
    // std::vector<Point2f> mean_shape;
    // string filename = "./dataset/meanShape.yaml"; 
    // FileStorage fs( filename, FileStorage::WRITE );
    // fs << "filename" << filename;
    // fs << "features" << "[";
    //     for(auto point:sum_shape){
    //         Point2f mp( point.x, point.y );
    //         mean_shape.push_back(mp);
    //         fs << "{:" << "p" << index++;
    //         fs << "x" << (int)mp.x;
    //         fs << "y" << (int)mp.y;
    //         fs << "z" << 0 << "}";
    //     }
    // fs << "]";
    

    // // Get Delaunay list
    // Mat plane( Size(512,512), CV_32FC3 );
    // Rect rect(0, 0, plane.cols, plane.rows);
    // Subdiv2D subdiv(rect);
    // subdiv.insert( mean_shape );
    // std::vector<Vec6f> triangle_list;
    // subdiv.getTriangleList(triangle_list);

    // std::vector<Vec3i> index_triangle;
    // for(auto p:triangle_list){
    //     Vec3i store = {-1, -1, -1};
    //     Point2f tri[3];
    //     tri[0] = Point2f( p[0], p[1]);
    //     tri[1] = Point2f( p[2], p[3]);
    //     tri[2] = Point2f( p[4], p[5]);
    //     for(int i = 0; i < mean_shape.size(); ++i) {
    //         if( rect.contains(tri[0]) && rect.contains(tri[1]) && rect.contains(tri[2]) ){
    //             if( tri[0] == mean_shape[i] )
    //                 store[0] = i;
    //             else if( tri[1] == mean_shape[i] )
    //                 store[1] = i;
    //             else if( tri[2] == mean_shape[i] )
    //                 store[2] = i;
    //         }
    //         if( store[0] > -1 && store[1] > -1 && store[2] > -1 )
    //             break;
    //     }
    //     if( store[0] != -1 && store[1] != -1 && store[2] != -1 )
    //         index_triangle.push_back(store); 
    // }

    // // Writing Points index in Triangle 
    // int t = 0;
    // fs << "delaunay" << "[";
    //     for( auto p_index:index_triangle ){
    //         fs << "{:" << "t" << t++;
    //         fs << "point_index" << p_index;
    //         fs << "}";
    //     }
    // fs << "]";

    // fs.release();
    return 0;
}

