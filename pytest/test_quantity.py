import pytest
import importlib.util
import sys
import os
import glob

libs = glob.glob("build/pypuq*.so")
spec = importlib.util.spec_from_file_location("pypuq", libs[0])
pp = importlib.util.module_from_spec(spec)
sys.modules["pypuq"] = pp

from pypuq import Q, UnitSystem
from pypuq.systems import US, ESU, EMU

def test_init_scalars():

    # initialize with a number/string pair
    q = Q(23)    
    assert q.to_string() == "23"
    q = Q(23, 'km')    
    assert q.to_string() == "23*km"
    q = Q(23, 'ft', US)    
    assert q.to_string() == "23*ft"

    # initialize with a string
    q = Q('23*km')
    assert q.to_string() == "23*km"
    q = Q('23*ft', US)
    assert q.to_string() == "23*ft"

def test_init_arrays():

    # initialize with an list/string pair
    q = Q([2,3,4])    
    assert q.to_string() == "{2, 3, ...}"
    q = Q([2.,3.,4.], 'km')    
    assert q.to_string() == "{2, 3, ...}*km"
    q = Q([2.,3.,4.], 'ft', US)    
    assert q.to_string() == "{2, 3, ...}*ft"

    # initialize with a string
    q = Q('{2,3,4}*ft', US)
    assert q.to_string() == "{2, 3, ...}*ft"

def test_init_arrays_errors():
    
    # initialize with an list/string pair
    q = Q([2.34,3.45,4.56],[0.1,0.2,0.3], 'km')    
    assert q.to_string() == "{2.34(10), 3.45(20), ...}*km"
    
def test_init_errors():

    q = Q(23.34, 0.2)
    assert q.to_string() == "2.334(20)e+01"
    q = Q(23.34, 0.2, 'km')
    assert q.to_string() == "2.334(20)e+01*km"
    q = Q(23.34, 0.2, 'ft', US)
    assert q.to_string() == "2.334(20)e+01*ft"
    
def test_unit_system():

    q = Q('23*km')          # default unit system is used
    assert q.unit_system() == "International System of Units (SI)"
    q = Q('US_23*ft')       # unit system is defined in the expression
    assert q.unit_system() == "United States customary units (US)"
    q = Q('23*ft', US)      # explicitely defined unit system
    assert q.unit_system() == "United States customary units (US)"

    with UnitSystem(EMU) as us:  # set unit system in a context manager
        assert Q('abA').unit_system() == "Electromagnetic CGS units (EMU)"
    assert Q('km').unit_system() == "International System of Units (SI)"
        
    us = UnitSystem(ESU)    # unit system environment is applied
    q = Q('statA')    
    assert q.unit_system() == "Electrostatic CGS units (ESU)"
    us.change(US)           # change of unit system environment
    q = Q('ft')    
    assert q.unit_system() == "United States customary units (US)"
    us.close()              # unit system environment is closed
    q = Q('au')    
    assert q.unit_system() == "International System of Units (SI)"
    
def test_conversion():

    # direct conversion
    q = Q(23, 'km')    
    assert q.to_string() == "23*km"
    q = q.convert('m')
    assert q.to_string() == "23000*m"
    q = q.convert('yd', US)
    assert q.unit_system() == "United States customary units (US)"
    assert q.to_string() == "25153.1*yd"
    q = q.convert('cm', ESU, 'l')
    assert q.unit_system() == "Electrostatic CGS units (ESU)"
    assert q.to_string() == "2.3e+06*cm"

    # conversion with a quantity context
    q = Q(23, 'A')    
    q = q.convert('statA', ESU, 'I')
    assert q.unit_system() == "Electrostatic CGS units (ESU)"
    assert q.to_string() == "6.89523e+10*statA"

    q = Q(23, '<B>')    
    q = q.convert('<B>', EMU, 'B')
    assert q.unit_system() == "Electromagnetic CGS units (EMU)"
    assert q.to_string() == "230000*<B>"
    
def test_arithmetics():

    q = Q(21, 'km')    
    r = Q(3, 'm')    
    assert (q+r).to_string() == "21.003*km"
    assert (q-r).to_string() == "20.997*km"
    assert (q*r).to_string() == "63*km*m"
    assert (q/r).to_string() == "7*km*m-1"
    
