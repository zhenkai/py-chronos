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

World::World(std::string phrase, object obj): m_phrase(phrase), m_obj(obj) {}

void
World::say()
{
  std::cout << m_phrase << std::endl;
}

BOOST_PYTHON_MODULE(world)
{
  class_<World>("World", init<std::string, object>())
    .def("say", &World::say)
    ;
}
