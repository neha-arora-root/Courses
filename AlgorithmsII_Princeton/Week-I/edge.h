#ifndef EDGE_H_
#define EDGE_H_

#include <iostream>

class Edge {
  private:
    const std::string from_;
    const std::string to_;
    const int weight_;
  public:
    Edge(const std::string from, const std::string to, const int weight): from_(from), to_(to), weight_(weight) {}
    const std::string from() const { return from_; }
    const std::string to() const { return to_; }
    const int weight() const { return weight_; }
    void PrintEdge() const { std::cout << from_ << " -> " << to_ << " : (" << weight_ << ")" << std::endl; }
};

#endif /* EDGE_H_ */