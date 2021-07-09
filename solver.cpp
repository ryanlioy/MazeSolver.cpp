/*
Responsible for solving maze
*/
#include <cmath>
#include <iostream>
#include "headers/solver.h" // node is included here
#include <opencv4/opencv2/core.hpp>

Node NULL_NODE = Node(-1, -1, false);

Solver::Solver(std::vector<std::vector<Node>> nodeGraph){
    graph = nodeGraph;
}

std::vector<Node> Solver::aStar(Node start, Node finish){
    // Because C++ doesn't allow for objects to be set 
    // to null, I can't just return null here. So, I have
    // to use a null node instead.
    if (start == NULL_NODE || finish == NULL_NODE ){ // make sure start and finish exist
        std::vector<Node> tmp = std::vector<Node>(1);
        tmp[0] = NULL_NODE;
        return tmp;
    }
    std::vector<Node> closedSet = std::vector<Node>();
    std::vector<Node> openSet = std::vector<Node>();
    std::vector<Node> path;

    openSet.push_back(start);
    int i = 0;
    while(openSet.size() > 0){
        std::cout << i << std::endl;
        std::cout << "Closed: ";
        for (Node n : closedSet){
            std::cout << n << " ";
        }
        std::cout << std::endl;
        std::cout << "open: ";
        for (Node n : openSet){
            std::cout << n << " ";
        }
        std::cout << std::endl;

        int bestF = 0;
        for (int i = 0; i < openSet.size(); i++){
            if (openSet.at(i).getF() < openSet.at(bestF).getF()){
                bestF = i;
                std::cout << "bestF = " << openSet.at(i) << " " << openSet.at(i).getF() << std::endl;
            }
        }

        Node current = openSet.at(bestF);
        std::cout << "Current node: " << current << std::endl;

        if (current == finish){
            std::cout << "Path found" << std::endl;
            Node tmp = current;
            path.push_back(tmp);
            while (tmp.getPrevious() != NULL_NODE){
                path.push_back(tmp.getPrevious());
                tmp = tmp.getPrevious();
            }
            return path;
        }

        std::vector<Node>::iterator it = std::find(openSet.begin(), openSet.end(), current); // for finding the index to remove
        openSet.erase(openSet.begin()+std::distance(openSet.begin(), it)); // because erase(index) is too much
        closedSet.push_back(current);
        
        std::cout << "Current after erase: " << current << std::endl;
        std::vector<Node> neighbors = current.getNeighbors();
        std::cout << "Number of neighbors to current: " << neighbors.size() << std::endl;
        std::cout << "Neighbors: ";
        for (Node n : neighbors){
            std::cout << n << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < neighbors.size(); i++){
            std::cout << "neighbors " << i << std::endl;
            Node n = neighbors.at(i);
            if (n != NULL_NODE) {
                // std::find returns the length of the vector if element is not found
                if ( !(std::find(closedSet.begin(), closedSet.end(), n) != closedSet.end()) && !n.isWall()){
                    double tmpG = current.getG() + heuristic(current, n);
                    if ( !(std::find(openSet.begin(), openSet.end(), n) != openSet.end())){
                        std::cout << "Neighbor of " << current << " found at " << n << std::endl;
                        openSet.push_back(n);
                    }
                    else if (tmpG >= n.getG()){ // pretty sure this isn't need but that's for later
                        continue;
                    }
                    n.setPrevious(current);
                    n.setG(tmpG);
                    n.setF(n.getG() + heuristic(n, finish));
                }
            }
        }
        i++;
    }
    std::vector<Node> tmp = std::vector<Node>(1);
    tmp[0] = NULL_NODE;
    return tmp;
}

double Solver::heuristic(Node end, Node finish){
    int y1 = end.getCol();
    int x1 = end.getRow();
    int y2 = finish.getCol();
    int x2 = finish.getRow();
    return std::abs(x2 - x1) + std::abs(y2 - y1); // taxicab distance
    //return std::sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)); // Euclidean distance
}