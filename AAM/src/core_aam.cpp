#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <dlib/matrix.h>


using namespace std;
using namespace cv;
using namespace dlib;

std::vector<Point2f> get_points( std::string filename, int &num_shape ) {
    std::vector<Point2f> points_set;    
    FileStorage fs( filename, FileStorage::READ );
    if( !fs.isOpened() ) {
        cout << "File not found at get_points: " << filename << endl;
        num_shape--;
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
std::vector<std::vector<Point2f>> get_delaunay( std::string filename, int &num_shape ) {
    std::vector<Point2f> init(68, Point2f(0, 0));
    std::vector<std::vector<Point2f>> delaunay_set;
    std::vector<Point2f> points = get_points( filename, num_shape );
    FileStorage fs( filename, FileStorage::READ );
    if( !fs.isOpened() ) {
        cout << "File not found at delaunay: " << filename << endl;
        num_shape--;
        return delaunay_set;
    }
    FileNode delaunay = fs["delaunay_index"];
    for( auto t:delaunay ){
        Vec3i v_index;
        std::vector<Point2f> v_points;
        t["index"] >> v_index;
        v_points.push_back( points[ v_index[0] ] );
        v_points.push_back( points[ v_index[1] ] );
        v_points.push_back( points[ v_index[2] ] );
        delaunay_set.push_back( v_points );
    }

    return delaunay_set;
}

void point_drawing( Mat& plane, std::vector<Point2f> points, double scale, Scalar& color ) {
    for( auto p:points ){
        circle( plane, p, 1, color, -1);
    }
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
    int num_shape = atoi(argv[1]);
    std::string mean_filename = "../face2yaml/dataset/meanShape.yaml";
    Mat plane = Mat::zeros( Size(512,512), CV_32FC3 );
    std::vector<std::vector<Point2f>> shape_store;
    std::vector<std::vector<Point2f>> delaunay = get_delaunay( mean_filename, num_shape );
    std::vector<Point2f>  mean_points = get_points( mean_filename, num_shape );
    Scalar red_color = Scalar( 0, 0, 255 );
    Scalar blue_color = Scalar( 255, 0, 0 );
    Scalar green_color = Scalar( 0, 255, 0 );

    for(int i = 1; i <= num_shape; ++i) {
        std::vector<Point2f> left_shape_points = get_points("../face2yaml/dataset/"+ to_string(i) +"L.yaml", num_shape);
        
        // Centroid(x, y)
        cv::Vec2f cg;
        double scale = 0;
        int left_num_shape = left_shape_points.size();
        for(int i = 0; i < left_num_shape; ++i){
            cg[0] += left_shape_points[i].x;
            cg[1] += left_shape_points[i].y;
        }
        cg[0] = cg[0]/left_num_shape;
        cg[1] = cg[1]/left_num_shape;
        
        std::vector<Point2f> left_shape_mean;

        for( int i = 0; i < left_num_shape; ++i ){
            int offset = 256;
            float tx_point = left_shape_points[i].x - cg[0];
            float ty_point = left_shape_points[i].y - cg[1];
            scale += tx_point*tx_point + ty_point*ty_point;
            Point2f left_s( tx_point + offset, ty_point + offset);
            left_shape_mean.push_back(left_s);
        }

        scale = sqrt(scale/left_num_shape);
        cout << "Scale : " << scale << endl;

        point_drawing( plane, left_shape_mean, scale, green_color );

        if( i%5 == 0 ){
            float percentage = ( (float)i/num_shape )*100;
            if( percentage == 100 )
                break;
            cout << "processing ";
            cout <<  setprecision(2) << "[ " << percentage << " \% ]" << endl;
        }
    }
    // delaunay_drawing( plane, delaunay, red_color );
    cout << "Num_shape: " << num_shape << endl;
    imshow ("Plane", plane );
    cout << "[ 100\% Done ], " << num_shape << " Faces" << endl;
    waitKey(0);

    return 0;
}



