/*
Converting image->node[] and node[]->image
*/ 
#include "headers/converter.h"
#include <vector>
#include <iostream>
// can't use using namespace cv becuase cv has a Node object

Converter::Converter(std::string path){
    img = cv::imread(path, cv::IMREAD_COLOR);

    this->path = path;

    if(!img.data){ // check if file can be read
        throw std::logic_error("Image could not be read; check file path");
    }
    // get dimensions
    width = img.cols;
    height = img.rows;
}

// actually returns a vector but close enough
std::vector<std::vector<Node>> Converter::to2Darray(){
    std::vector<std::vector<Node>> nodes(width, std::vector<Node>(height));

    for (int i = 0; i < width; i++){ // initialization
        for (int j = 0; j < height; j++){
            nodes[i][j].setDim(i,j);
        }
    }

    const cv::Vec3b BLACK(0, 0, 0);
    const cv::Vec3b WHITE(255,255,255);

    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            cv::Vec3b pixel = img.at<cv::Vec3b>(i,j); // in BGR format, doesn't matter though
            if (pixel == BLACK){ // thank God C++ has operator overloading
                nodes[i][j].setIsWall(true);
                std::cout << "B";
            }
            else if (pixel == WHITE){
                nodes[i][j].setIsWall(false);
                std::cout << "W";
            }
            else{
                throw std::invalid_argument("Found non white or black pixel in image");
            }
        }
        std::cout << std::endl;
    }

    for (int row = 0; row < width; row++){
        for (int col = 0; col < width; col++){
            // use at().at() becuase at() throws exceptions while operator[] doesn't
            
            try {
                nodes[row][col].addNeighbor(nodes.at(row).at(col - 1)); // Node to the left
            }
            catch (const std::out_of_range& e) {
                nodes[row][col].addNeighbor(Node(-1, -1, false));
            }

            try {
                nodes[row][col].addNeighbor(nodes.at(row).at(col + 1)); // Node to the right
            }
            catch (const std::out_of_range& e) {
                nodes[row][col].addNeighbor(Node(-1, -1, false));
            }

            try {
                //    vvvvvvvvv should always work    vvvvvvvvvv might not work
                nodes[row][col].addNeighbor(nodes.at(row - 1).at(col)); // Node to the top
            }
            catch (const std::out_of_range& e) {
                nodes[row][col].addNeighbor(Node(-1, -1, false));
            }
            
            try {
                nodes[row][col].addNeighbor(nodes.at(row + 1).at(col)); // Node to the bottom
            }
            catch (const std::out_of_range& e) {
                nodes[row][col].addNeighbor(Node(-1, -1, false));
            }

            
        }
    }

    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            std::cout << "[" << i << "]" << "[" << j << "] ";
            std::vector<Node> neighbors = nodes[i][j].getNeighbors();
            for (int k = 0; k < neighbors.size(); k++){
                std::cout << neighbors[k];
            }
            std::cout << std::endl;
        }
    }
    return nodes;
}

void Converter::toImage(std::vector<std::vector<Node>> graph, std::vector<Node> solution){
    cv::Mat copy = img; // make copy of img

    std::vector<Node>::iterator it;
    for (it = solution.begin(); it < solution.end(); it++){
        cv::Vec3b &pixel = copy.at<cv::Vec3b>((*it).getRow(), (*it).getCol());
        pixel[2] = 255;
    }
    bool wrote = cv::imwrite("SOLVED.png", copy);

    if (!wrote){
        throw std::runtime_error("File not written");
    }
}

Node Converter::findEndNode(std::vector<std::vector<Node>> graph){
    for (int i = 1; i < height; i++) { // start at 1 because col 0 can never be valid start/end point
        if (!graph.at(height - 1).at(i).isWall()) {
            return graph[height - 1][i];
        }
    }
    return Node(-1, -1, false);
}

Node Converter::findStartNode(std::vector<std::vector<Node>> graph){
    for (int i = 1; i < height; i++) {
        if (!graph.at(0).at(i).isWall()) {
            return graph[0][i];
        }
    }
    return Node(-1, -1, false);
}