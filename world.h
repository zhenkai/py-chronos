#ifndef TEST_WORLD_H
#define TEST_WORLD_H
#include <boost/python.hpp>
#include <string>
#include <iostream>

using namespace boost::python;

class World
{
  public:
    World(std::string phrase, object obj);
    ~World(){}
    void say();
  private:
    std::string m_phrase;
    object m_obj;
};

#endif //TEST_WORLD_H
