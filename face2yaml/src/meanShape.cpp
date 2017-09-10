#include <iostream>
#include <iomanip>
#include <vector>
#include <opencv2/opencv.hpp>
#include <dlib/matrix.h>

using namespace std;
using namespace cv;
using namespace dlib;

matrix<double> getColMatrix( string filename ) {
    FileStorage fs( filename, FileStorage::READ );
    if( !fs.isOpened() ){
        cout << "File not found : " << filename << endl;
        return ones_matrix<double>(1, 1); 
    }
    FileNode features = fs["features"];
    int num_points = features.size()*2;
    matrix<double> p( num_points, 1 );
    FileNodeIterator it_start = features.begin();
    FileNodeIterator it_end = features.end(); 
    std::vector<double> x_points, y_points;
    for( ; it_start != it_end; ++it_start ){
        double x = (double)(*it_start)["x"];
        double y = (double)(*it_start)["y"];
        x_points.push_back( x );
        y_points.push_back( y );
    }
    x_points.insert( x_points.end(), y_points.begin(), y_points.end() );
    fs.release();

    return mat(x_points);;
}

int main ( int argc, char *argv[] ) {
    matrix<double> points_pool, mean_matrix;
    int num_shape = atoi(argv[1]);
    bool init = true;
    // Initialize Points pool
    for( int i = 1; i <= num_shape; ++i ){
        string l_filename = "./dataset/"+to_string(i)+"L.yaml"; 
        string r_filename = "./dataset/"+to_string(i)+"R.yaml"; 
        matrix<double> l_p = getColMatrix( l_filename );
        matrix<double> r_p = getColMatrix( r_filename );
        bool found_left = points_pool.nr() == l_p.nr();
        bool found_right = points_pool.nr() == r_p.nr();
        if( init ){
            points_pool = join_rows( points_pool, l_p );
            init = false;
        }
        else {
            if( found_left )
                points_pool = join_rows( points_pool, l_p );

            if( found_right )
                points_pool = join_rows( points_pool, r_p );
        }
        
    }

    int pool_nr = points_pool.nr();
    int pool_nc = points_pool.nc();
    std::vector<double> mean_vector;
    for( int i = 0; i < pool_nr; ++i ){
        mean_vector.push_back( sum_cols( rowm( points_pool, i )/pool_nc ) );
    }

    // Writing MeanShape
    string fn = "./dataset/meanShape.yaml";
    FileStorage fs( fn, FileStorage::WRITE );
    fs << "filename" << fn;

    mean_matrix = mat( mean_vector );
    std::vector<Point2f> p_store;
    matrix<Point2f> mean_point;
    fs << "features" << "[";
    for( int i = 0; i < mean_matrix.nr()/2; ++i ){
            fs << "{:";
            fs << "p" << i << "x" << (int)mean_matrix(i) << "y" << (int)mean_matrix(i+68); 
            fs << "}";
        Point2f p( mean_matrix(i),  mean_matrix(i+68) );
        p_store.push_back( p );
    }
    fs << "]";
    mean_point = mat( p_store );
    cout << mean_matrix << endl;
    cout << mean_point << endl;
    return 0;
}
