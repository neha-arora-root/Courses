#ifndef NODE_H_
#define NODE_H_

#include <iostream>

class Node {
  private:
    std::string id_;
  public:
    Node(const std::string id=""): id_(id) {}
    const std::string& Id() const { return id_; }
};

#endif /* NODE_H_ */