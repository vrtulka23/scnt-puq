#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "../../src/quantity.h"

namespace py = pybind11;

std::string convert(std::string s1, std::string s2) {
  puq::Quantity q(s1);
  return q.convert(s2).to_string();
}

PYBIND11_MODULE(pypuq, m) {
    m.doc() = "pybind11 quantity plugin"; // optional module docstring
    
    m.def("convert", &convert, "Convert quantities");

    // Exposing all unit systems
    auto sys = m.def_submodule("systems", "Unit systems");
    auto e = py::enum_<puq::SystemType>(sys, "SystemType");
    for (auto sys: puq::SystemMap) {
      e.value(sys.second->SystemAbbrev.c_str(), sys.first);
    }
    e.export_values();

    // Exposing quantity object
    py::class_<puq::Quantity>(m, "Q")
      .def("convert", py::overload_cast<std::string, const puq::SystemType, const std::string&>(&puq::Quantity::convert, py::const_),
	   py::arg("expression"), py::arg("system")=puq::SystemType::NONE, py::arg("quantity")="")
      .def("to_string", &puq::Quantity::to_string, py::arg("precision") = 6)
      .def("__repr__", &puq::Quantity::to_string, py::arg("precision") = 6)
      .def(py::self + py::self)
      .def(py::self - py::self)
      .def(py::self * py::self)
      .def(py::self / py::self)
      .def(py::init<std::string>())
      .def(py::init<std::string, puq::SystemType>())
      .def(py::init<double>())
      .def(py::init<double, std::string>())
      .def(py::init<double, std::string, puq::SystemType>());

}
