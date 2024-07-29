#ifndef PUQ_QUANTITIES_H
#define PUQ_QUANTITIES_H

struct QuantityStruct {
  std::string symbol;
  std::string definition;
  std::string conversion;
};
typedef std::vector<QuantityStruct> QuantityListType;

typedef std::map<std::string, std::string> QuantityNamesType;
const QuantityNamesType QuantityNames = {
  // base quantities
  {"l",      "length"                      },
  {"m",      "mass"                        },
  {"t",      "time"                        },
  {"T",      "temperature"                 },
  {"I",      "current"                     },
  {"Iv",     "luminous intensity"          },
  {"n",      "amount of substance"         },
  {"the",    "angular displacement"        },

  // mechanics 
  {"vel",    "velocity"                    },
  {"acc",    "acceleration"                },
  {"jerk",   "jerk"                        },
  {"snap",   "snap"                        },  
  {"crac",   "crackle"                     },
  {"pop",    "pop"                         },
  
  {"rho",    "density"                     },
  {"rho_A",  "area density"                },
  {"rho_l",  "linear density"              },

  {"rho_E",  "energy density"              },
  
  {"A",      "area"                        },
  {"V",      "volume"                      },

  {"p_mom",  "momentum"                    },
  {"I_mom",  "moment of inertia"           },
  
  {"ome",    "angular velocity"            },
  {"a_ome",  "angular acceleration"        },
  {"L_ome",  "angular momentum"            },
  
  {"Force",  "force"                       },
  {"freq",   "frequecy"                    },
  
  {"J_i",    "impulse"                     },
  {"Abs",    "absement"                    },
  
  // material properties
  {"nu",     "viscosity"                   },
  {"eps_s",  "strain"                      },
  {"sig_s",  "stress"                      },
  {"E_Y",    "Young's modulus"             },
  {"k_s",    "spring constant"             },
  {"gam",    "surface tension"             },
  {"tau",    "torque"                      },
    
  // thermodynamics
  {"E",      "energy"                      },
  {"S",      "entropy"                     },
  {"p",      "pressure"                    },
  {"mu_c",   "chemical potential"          },  
  {"W",      "work"                        },
  {"P",      "power"                       },
  
  {"E_sp",   "specific energy"             },
  {"C_sp",   "specific heat capacity"      },
  {"V_sp",   "specific volume"             },

  {"C_mol",  "molar concentration"         },
  {"E_mol",  "molar energy"                },
  {"c_mol",  "molar heat capacity"         },
  
  {"rr",     "reaction rate"               },
  
  {"Q",      "heat"                        },
  {"C_p",    "head capacity"               },
  {"phi_Q",  "heat flux density"           },
  
  {"kap",    "thermal conductance"         },
  {"lam_t",  "thermal conductivity"        },
  {"R_t",    "thermal resistance"          },
  {"R_l",    "thermal resistivity"         },
  
  {"Q_vol",  "volumetric flow rate"        },
  
  // electromagetism
  {"q",      "electric charge"             },
  {"rho_q",  "electric charge density"     },
  {"p_e",    "electric dipole moment"      },
  {"D_e",    "electric displacement field" },
  {"E_e",    "electric field strength"     },
  {"G_e",    "electrical conductance"      },
  {"sig_e",  "electrical conductivity"     },
  {"phi_e",  "electric potential"          },
  {"R_e",    "electrical resistance"       },
  {"rho_e",  "electrical resistivity"      },
 
  {"Mag",    "magnetization"               },
  {"H_m",    "magnetic field strenght"     },
  {"phi_m",  "magnetic flux"               },
  {"B_m",    "magnetic flux density"       },
  {"m_m",    "magnetic moment"             },

  {"mu",     "permeability"                },
  {"eps",    "permittivity"                },
  
  {"Ca",     "capacitance"                 },
  {"J_c",    "current density"             },
  {"Z",      "impedance"                   },
  {"L_i",    "inductance"                  },
  {"Rel",    "reluctance"                  },

  // wave and optics
  {"P_o",    "optical power"               },
  {"lam_w",  "wavelength"                  },
  {"k_n",    "wavenumber"                  },
  {"k_v",    "wavevector"                  },

  // radiation
  {"E_il",   "illuminance"                 },
  {"E_ir",   "irradiance"                  },
  {"F_l",    "luinous flux"                },
  {"In",     "intensity"                   },  
  {"L_r",    "radiance"                    },
  {"I_r",    "radiant intensity"           },
  
  // radioactivity
  {"D_a",    "absorbed dose rate"          },
  {"H_de",   "dose equivalent"             },
  {"D_r",    "radiation dose"              },
  {"Act",    "activity"                    },  

  // quantum mechanics
  {"S_a",    "action"                      },
  {"spin",   "spin"                        },
  
};

#endif // PUQ_QUANTITIES_H