#ifndef __OPERATION__HPP__
#define __OPERATION__HPP__

#include <iostream>

class Operation {
  public:
    /**
     * Perform the operation
     */
    virtual bool perform() = 0;
    /**
     * Add dependecy to the operation
     */
    virtual void addDependency(const std::unique_ptr<Operation>& operation) {
      dependencies.push_back(std::move(operation));
    }
    virtual ~Operation() = default;
  protected:
    /**
     * Dependecy of the operation
     */
    std::vector<std::unique_ptr<Operation>> dependencies;
};
#endif
