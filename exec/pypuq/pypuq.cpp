#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "../../src/quantity.h"

namespace py = pybind11;

std::string convert(std::string s1, std::string s2) {
  puq::Quantity q(s1);
  return q.convert(s2).to_string();
}

// Adding Python context manager methods to UnitSystem
class UnitSystem: public puq::UnitSystem {
  using puq::UnitSystem::UnitSystem;
public:
  UnitSystem& enter() {return *this;}
  void exit(const py::object& exc_type, const py::object& exc_value, const py::object& traceback) {close();}
};

PYBIND11_MODULE(pypuq, m) {
    m.doc() = "Physical Units and Quantities"; 
    
    m.def("convert", &convert, "Convert quantities");

    // Exposing all unit systems
    auto sys = m.def_submodule("systems", "Unit systems");
    auto e = py::enum_<puq::SystemType>(sys, "SystemType");
    for (auto sys: puq::SystemMap) {
      e.value(sys.second->SystemAbbrev.c_str(), sys.first);
    }
    e.export_values();

    // Expose UnitSystem
    py::class_<puq::UnitSystem>(m, "UnitSystemBase")
      .def(py::init<const puq::SystemType>())
      .def("change", &puq::UnitSystem::change)      
      .def("close", &puq::UnitSystem::close)      
      ;

    py::class_<UnitSystem, puq::UnitSystem>(m, "UnitSystem")
      .def(py::init<const puq::SystemType>())
      .def("enter", &UnitSystem::enter)
      .def("exit", &UnitSystem::exit)  
      .def("__enter__", &UnitSystem::enter)
      .def("__exit__", &UnitSystem::exit)
      ;
    
    // Exposing quantity object
    py::class_<puq::Quantity>(m, "Q")
      .def(py::init<std::string>())
      .def(py::init<std::string, puq::SystemType>())
      .def(py::init<double>())
      .def(py::init<double, std::string>())
      .def(py::init<double, std::string, puq::SystemType>())
      .def(py::init<double, double>())
      .def(py::init<double, double, std::string>())
      .def(py::init<double, double, std::string, puq::SystemType>())
      .def(py::init<puq::ArrayValue>())
      .def(py::init<puq::ArrayValue, std::string>())
      .def(py::init<puq::ArrayValue, std::string, puq::SystemType>())
      .def(py::init<puq::ArrayValue, puq::ArrayValue>())
      .def(py::init<puq::ArrayValue, puq::ArrayValue, std::string>())
      .def(py::init<puq::ArrayValue, puq::ArrayValue, std::string, puq::SystemType>())
      .def("convert", py::overload_cast<std::string, const puq::SystemType, const std::string&>(&puq::Quantity::convert, py::const_),
	   py::arg("expression"), py::arg("system")=puq::SystemType::NONE, py::arg("quantity")="")
      .def("unit_system", &puq::Quantity::unit_system)
      .def("to_string", &puq::Quantity::to_string, py::arg("precision") = 6)
      .def("__repr__", &puq::Quantity::to_string, py::arg("precision") = 6)
      .def(py::self + py::self)
      .def(py::self - py::self)
      .def(py::self * py::self)
      .def(py::self / py::self)
      ;
    	
}
