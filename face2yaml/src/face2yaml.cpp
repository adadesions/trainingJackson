#include <iostream>
#include <regex>
#include <string>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/image_transforms.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>

using namespace std;
using namespace cv;
using namespace dlib;

// Function Prototype
std::vector<int> getPointIndex( Vec6f v, std::vector<Point2f> store, Rect bounding );

int main(int argc, char *argv[]) {
  if( argc == 1 ){
    cout << "Need more arguments...Please ask Ada" << endl;
    return -1;
  }
  // Initialize
  // string img_filename = "./public/images/1L.jpg";
  string img_filename = argv[1];
  string sp_filename = "./public/shape_predictor_68_face_landmarks.dat";
  shape_predictor sp;
  deserialize(sp_filename) >> sp;
  array2d<dlib::bgr_pixel> rs(512, 512);
  array2d<dlib::bgr_pixel> img;

  // Load and prepare image
  load_image(img, img_filename);
  resize_image(img, rs);
  // pyramid_up(rs);

  // Setup detector and predictor
  frontal_face_detector detector = get_frontal_face_detector();
  std::vector<dlib::rectangle> dets = detector(rs);
  full_object_detection shape = sp(rs, dets[0]);

  // OPENCV PART
  Mat cvImg = dlib::toMat(rs);
  if( !cvImg.data ){
    cout << "Image not found!!" << endl;
    return -1;
  }  
  // resize( cvImg, cvImg, Size(512, 512) );

  // // Painting circles on face
  // for( int i = 0; i < shape.num_parts(); ++i ){
  //   int x = shape.part(i).x();
  //   int y = shape.part(i).y();
  //   circle(cvImg, cv::Point(x, y), 2, cv::Scalar(0,0,255), -1);
  //   putText(cvImg, to_string(i), cv::Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255));
  // }
  // namedWindow( img_filename , WINDOW_AUTOSIZE);
  // imshow( img_filename, cvImg);
  // waitKey(0);
  // END PAINTING OPENCV PART

  // Writing YAML
  std::smatch match;
  std::regex e("\\w+(?=.jpg)");
  std::regex digits("\\d*[0-9]");
  std::regex_search (img_filename, match, e);
  cout << match[0] << " ";
  string yaml_path = "./dataset/" + match[0] + ".yaml";
  FileStorage fs(yaml_path, FileStorage::WRITE);
  string filename = match[0];
  fs << "filename" << filename;
  fs << "path" << img_filename;
  fs << "originRows" << (int)img.nr();
  fs << "originCols" << (int)img.nc();
  std::regex_search ( filename, match, digits);

  if( filename.find("L") != std::string::npos ) // Not left image
    fs << "paired" << match[0]+"R.jpg";
  else
    fs << "paired" << match[0]+"L.jpg";

  // Features
  std::vector<int> left_eye, right_eye, left_eyebrow, right_eyebrow;
  std::vector<int> face, mouth, nose;

  fs << "features" << "[";
  for( int i = 0; i < shape.num_parts(); ++i ){
      int x = shape.part(i).x();
      int y = shape.part(i).y();
    fs << "{:" << "p" << i << "x" << x << "y" << y << "z" << 0 << "}";
    if( i >= 0 && i <= 16) face.push_back(i);
    else if( i >= 17 && i <= 21) left_eyebrow.push_back(i);
    else if( i >= 22 && i <= 26) right_eyebrow.push_back(i);
    else if( i >= 27 && i <= 35) nose.push_back(i);
    else if( i >= 36 && i <= 41) left_eye.push_back(i);
    else if( i >= 42 && i <= 47) right_eye.push_back(i);
    else if( i >= 48 && i <= 67) mouth.push_back(i);
  }
  fs << "]";

  // Sub-features
  fs << "left_eye" << left_eye;
  fs << "right_eye" << right_eye;
  fs << "left_eyebrow" << left_eyebrow;
  fs << "right_eyebrow" << right_eyebrow;
  fs << "face" << face;
  fs << "nose" << nose;
  fs << "mouth" << mouth;

  //Delaunay Triangular
  // std::vector<Point2f> vertex;
  // for(int i = 0; i < shape.num_parts(); ++i){
  //   float x = shape.part(i).x();
  //   float y = shape.part(i).y();
  //   vertex.push_back( cv::Point2f(x, y) );
  // }
  // Rect rect(0 ,0 , cvImg.cols, cvImg.rows);
  // Subdiv2D subdiv(rect);
  // subdiv.insert(vertex);
  // std::vector<Vec6f> triangleList;
  // subdiv.getTriangleList(triangleList);
  // int numOfDelaunay = triangleList.size();
  // std::vector<std::vector<int>> point_list;

  // for( auto triangle : triangleList ){
  //   std::vector<int> points = getPointIndex( triangle, vertex, rect );
  //   if( points[0] < 0 || points[1] < 0 || points[2] < 0)
  //     continue;
  //   point_list.push_back(points);
  // }
  // for( auto list:point_list ){
  //   for( auto p:list)
  //     cout << p << " ";
  //   cout << endl;
  // }

  // fs << "numOfDelaunay" << numOfDelaunay;
  // fs << "delaunay" << "[";
  // for( int i = 0; i < triangleList.size(); ++i ){
  //   fs << "{:";
  //   fs << "t" << i << "points" << triangleList[i];
  //   fs << "}";
  // }
  // fs << "]";

  fs << "image" << cvImg;
  fs.release();

  cout << "[ Done ]" << endl;

  return 0;
}

// Functions
std::vector<int> getPointIndex( Vec6f v, std::vector<Point2f> store, Rect bounding ) {
  std::vector<int> pointIndex(3, -1);
  std::vector<Point2f> vt(3, Point2f(0, 0));
  vt[0] = Point2f( v[0], v[1] );
  vt[1] = Point2f( v[2], v[3] );
  vt[2] = Point2f( v[4], v[5] );
 
 for(int i = 0; i < store.size(); ++i) {
   if( bounding.contains(vt[0]) && bounding.contains(vt[1]) && bounding.contains(vt[2]) ){
    if( vt[0] == store[i] )
      pointIndex[0] = i;
    else if( vt[1] == store[i] )
      pointIndex[1] = i;
    else if( vt[2] == store[i] )
      pointIndex[2] = i;
   }

   if( pointIndex[0]  > -1 && pointIndex[1] > -1 && pointIndex[2] > -1)
    break;
 } 
 return pointIndex;
}
