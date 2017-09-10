#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

std::vector<Point2f> get_points( std::string filename ) {
    std::vector<Point2f> points_set;    
    FileStorage fs( filename, FileStorage::READ );
    if( !fs.isOpened() ) {
        cout << "File not found : " << filename << endl;
        return points_set;
    }
    
    FileNode features = fs["features"];
    for( auto point:features ){
        Point2f p2f( point["x"], point["y"] );
        points_set.push_back( p2f );
    }
    fs.release();

    return points_set;
}
std::vector<std::vector<Point2f>> get_delaunay( std::string filename ) {
    std::vector<std::vector<Point2f>> delaunay_set;
    std::vector<Point2f> points = get_points( filename );
    FileStorage fs( filename, FileStorage::READ );
    if( !fs.isOpened() ) {
        cout << "File not found : " << filename << endl;
        return delaunay_set;
    }
    FileNode delaunay = fs["delaunay"];
    for( auto t:delaunay ){
        Vec3i v_index;
        std::vector<Point2f> v_points;
        t["point_index"] >> v_index;
        v_points.push_back( points[ v_index[0] ] );
        v_points.push_back( points[ v_index[1] ] );
        v_points.push_back( points[ v_index[2] ] );
        delaunay_set.push_back( v_points );
    }

    return delaunay_set;
}

void point_drawing( Mat& plane, std::vector<Point2f> points, Scalar& color ) {
    for( auto p:points )
        circle( plane, p, 1, color, -1);
}
void delaunay_drawing( Mat& plane, std::vector<std::vector<Point2f>> vertices, Scalar& color ) {
    float line_weight = 1.5;
    for( auto v:vertices ){
        line(plane, v[0], v[1], color, line_weight);
        line(plane, v[1], v[2], color, line_weight);
        line(plane, v[2], v[0], color, line_weight);
    }
}

int main( int argc, char *argv[] ) {
    std::string mean_filename = "../face2yaml/dataset/meanShape.yaml";
    Mat plane = Mat::zeros( Size(512,512), CV_32FC3 );
    std::vector<std::vector<Point2f>> shape_store;
    std::vector<std::vector<Point2f>> delaunay = get_delaunay( mean_filename );
    std::vector<Point2f>  mean_points = get_points( mean_filename );
    Scalar red_color = Scalar( 0, 0, 255 );
    Scalar blue_color = Scalar( 255, 0, 0 );
    Scalar green_color = Scalar( 0, 255, 0 );

    int num_shape = atoi(argv[1]);
    for(int i = 1; i <= num_shape; ++i) {
        std::vector<Point2f> left_shape_points = get_points("../face2yaml/dataset/"+ to_string(i) +"L.yaml");
        std::vector<Point2f> right_shape_points = get_points("../face2yaml/dataset/"+ to_string(i) +"R.yaml");
        point_drawing( plane, left_shape_points, green_color );
        point_drawing( plane, right_shape_points, blue_color );
        if( i%5 == 0 ){
            float percentage = ( (float)i/num_shape )*100;
            if( percentage == 100 )
                break;
            cout << "processing ";
            cout <<  setprecision(2) << "[ " << percentage << " \% ]" << endl;
        }
    }
    delaunay_drawing( plane, delaunay, red_color );

    imshow ("Plane", plane );
    cout << "[ 100\% Done ], " << argv[1] << " Faces" << endl;
    waitKey(0);

    return 0;
}



