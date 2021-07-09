#include <iostream>
#include <vector>
#include "headers/converter.h"
#include "headers/solver.h" // Node.h is included in this header

int main(int argc, char *argv[]){
    if (argc == 1){ // check if exe is only argument
        std::cout << "FATAL: Image path must be specified" << std::endl;
    }
    else{
        std::string path = argv[1]; // anything past the second arg is ignored
        Converter convert(path); 
        std::vector<std::vector<Node>> nodes = convert.to2Darray(); // convert image to something Solver can use
        std::cout << std::endl;
        for (std::vector<Node> vec : nodes){
            for (Node n : vec){
                if (n.isWall()){
                    std::cout << "W";
                }
                else{
                    std::cout << "P";
                }
            }
            std::cout << std::endl;
        }
        Solver solve(nodes);
        Node start = convert.findStartNode(nodes);
        Node end = convert.findEndNode(nodes);
        std::cout << "START: " << start << "\n";
        std::cout << "END: " << end << "\n";
        if (start == Node(-1, -1, false) || end == Node(-1, -1, false)){
            std::logic_error("Start or end node does not exist\n");
        }
        std::vector<Node> solution = solve.aStar(start, end); // solve
        if (solution.at(0) == Node(-1, -1, false)){
            std::cout << "No solution found" << std::endl;
        }
        else{
            convert.toImage(nodes, solution);
        }
    }
}