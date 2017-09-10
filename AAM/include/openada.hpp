#ifndef OPENADA_HPP
#define OPENADA_HPP

#include <iostream>
#include <dlib/matrix.h>
#include <opencv2/opencv.hpp>

namespace opa {
    void test() {
        std::cout << "Yo\n";
    }
    std::vector<cv::Vec6f> getDelaunayVec6f( std::string filename ) {
        cv::FileStorage fs(filename, cv::FileStorage::READ);
        std::vector<cv::Vec6f> vertices;

        if( !fs.isOpened() ){
            std::cout << "File not found at getDelaunay: " << filename << std::endl;
            return vertices;
        }
            
        cv::FileNode delaunay = fs["delaunay"];
        
        for( auto p:delaunay ){
            cv::Vec6f v;
            p["points"] >> v;
            vertices.push_back(v);
        }

        fs.release();
        return vertices;
    }

    cv::Mat getTexture( std::string filename ) {
        cv::Mat image;
        cv::FileStorage fs(filename, cv::FileStorage::READ);
        if( !fs.isOpened() ){
            std::cout << "File not found at getTexture: " << filename << std::endl;
            return image;
        }
        cv::FileNode fn = fs["image"];
        fs["image"] >> image;
        return image;

        
    }
    std::vector<cv::Point2f> getTrianglePiece( int index, std::vector<cv::Vec6f> vertices ) {
        cv::Vec6f v = vertices[index];
        int cgx = (v[0] + v[2] + v[4])/3;
        int cgy = (v[1] + v[3] + v[5])/3;
        // cgx = 0;
        // cgy = 0;
        std::vector<cv::Point2f> p;
        cv::Point2f cg = cv::Point2f( cgx, cgy );
        p.push_back( cv::Point2f( v[0], v[1] ) );
        p.push_back( cv::Point2f( v[2], v[3] ) );
        p.push_back( cv::Point2f( v[4], v[5] ) );
        p[0] = p[0] - cg;
        p[1] = p[1] - cg;
        p[2] = p[2] - cg;
    
        return p;
    }
}
#endif