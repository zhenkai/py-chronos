#include <boost/python.hpp>
//#include "py_boost_function.hpp"
#include <sync/sync-app-socket.h>
#include <sync/sync-logic.h>
#include <sync/sync-ccnx-wrapper.h>
#include <sync-seq-no.h>
#include "simple-chronos-socket.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(chronos)
{
  class_<SimpleChronosSocket>("SimpleChronosSocket", init<const std::string, object>())
    .def("publish", &SimpleChronosSocket::publishString)
    .def("remove", &SimpleChronosSocket::remove)
  ;
}
