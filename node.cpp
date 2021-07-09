/*
For storing Node data
*/
#include <vector>
#include "headers/node.h"

Node::Node(int r, int c, bool isWall){
    row = r;
    col = c;
    isAWall = isWall;
}

Node::Node(){} // for the Node 2D array

bool operator==(const Node& lhs, const Node& rhs){
    return lhs.getRow() == rhs.getRow() && lhs.getCol() == rhs.getCol();
}

bool operator!=(const Node& lhs, const Node& rhs){
    return !(lhs==rhs);
}

std::ostream& operator<< (std::ostream &out, const Node &n){ // here for testing
    out << "Node(" << n.getRow() << ", " << n.getCol() << ", " << n.isWall() << ")";
    return out;
}

int Node::getRow() const{
    return row;
}

int Node::getCol() const{
    return col;
}

double Node::getF() {
    return f;
}

double Node::getG() {
    return g;
}

double Node::getH() {
   return h;
}

void Node::setF(double f) {
    this->f = f;
}

void Node::setG(double g) {
    this->g = g;
}

void Node::setH(double h) {
    this->h = h;
}

bool Node::isWall() const{
    return isAWall;
}

void Node::setIsWall(bool isWall) {
    this->isAWall = isWall;
}

void Node::addNeighbor(Node b) {
    neighbors.push_back(b);
}

void Node::setPrevious(Node n) {
    previous = &n;
}

Node Node::getPrevious() {
    return *previous;
}

void Node::setDim(int r, int c){
    row = r;
    col = c;
}

std::vector<Node> Node::getNeighbors(){
    return neighbors;
}