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

    py::class_<puq::Quantity>(m, "quantity")
      .def("convert", py::overload_cast<std::string, const std::string&>(&puq::Quantity::convert, py::const_), py::arg("expression"), py::arg("quantity")="")
      .def("to_string", &puq::Quantity::to_string, py::arg("precision") = 6)
      .def("__repr__", &puq::Quantity::to_string, py::arg("precision") = 6)
      .def(py::self + py::self)
      .def(py::self - py::self)
      .def(py::self * py::self)
      .def(py::self / py::self)
      .def(py::init<std::string>())
      .def(py::init<double, std::string>())
      .def(py::init<double, std::string, puq::SystemDataType&>());

    //auto sys = m.def_submodule("systems", "Unit systems");
    //sys.def("SI", puq::SystemData::SI, py::return_value_policy::reference);

}
