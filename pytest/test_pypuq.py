import pytest
import importlib.util
import sys
import os
import glob

libs = glob.glob("build/pypuq*.so")
spec = importlib.util.spec_from_file_location("pypuq", libs[0])
pp = importlib.util.module_from_spec(spec)
sys.modules["pypuq"] = pp
#spec.loader.exec_module(pp)
from pypuq import Q
from pypuq.systems import US, ESU

def test_initialization():

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
    q = Q('{2,3,4}*ft', US)
    assert q.to_string() == "{2, 3, ...}*ft"
    
def test_conversion():

    # direct conversion
    q = Q(23, 'km')    
    assert q.to_string() == "23*km"
    q = q.convert('m')
    assert q.to_string() == "23000*m"
    q = q.convert('yd', US)
    assert q.to_string() == "25153.1*yd"
    q = q.convert('cm', ESU, 'l')
    assert q.to_string() == "2.3e+06*cm"

    # conversion with a quantity context
    q = Q(23, 'A')    
    q = q.convert('statA', ESU, 'I')
    assert q.to_string() == "6.89523e+10*statA"

def test_arithmetics():

    q = Q(21, 'km')    
    r = Q(3, 'm')    
    assert (q+r).to_string() == "21.003*km"
    assert (q-r).to_string() == "20.997*km"
    assert (q*r).to_string() == "63*km*m"
    assert (q/r).to_string() == "7*km*m-1"
    
