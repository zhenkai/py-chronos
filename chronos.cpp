#include <boost/python.hpp>
#include "simple-chronos-socket.h"

using namespace boost::python;


BOOST_PYTHON_MODULE(chronos)
{
  class_<SimpleChronosSocket>("SimpleChronosSocket", init<std::string, object>())
    .def("publish", &SimpleChronosSocket::publishString)
    .def("remove", &SimpleChronosSocket::remove)
  ;
}
