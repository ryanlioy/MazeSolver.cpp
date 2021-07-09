#ifndef NODE_H
#define NODE_H

#include <vector>
#include <ostream>

class Node{
    private:
        double f, g, h;
        int row, col;
        bool isAWall;
        std::vector<Node> neighbors;
        Node *previous;

    public:
        Node(int r, int c, bool isWall);
        Node();
        friend bool operator==(const Node& lhs, const Node& rhs);
        friend bool operator!=(const Node& lhs, const Node& rhs);
        friend std::ostream& operator<< (std::ostream &out, const Node &n);
        int getRow() const;
        int getCol() const;
        double getF();
        double getG();
        double getH();
        void setF(double f);
        void setG(double g);
        void setH(double h);
        bool isWall() const;
        void setIsWall(bool isWall);
        void addNeighbor(Node b);
        void setPrevious(Node n);
        Node getPrevious();
        void setDim(int r, int c);
        std::vector<Node> getNeighbors();
};
#endif