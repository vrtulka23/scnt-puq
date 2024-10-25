# Physical Units and Quantities (PUQ)

Implementation of physical unit calculations in C++.
The original project written in Python is available in the [scinumtools](https://github.com/vrtulka23/scinumtools) package.

## Documentation

For more details please refer to `SciNumTool` [documentation](https://vrtulka23.github.io/scnt-docs/).

## Example of use

In order to compile PUQ you can use the following setup script.

``` bash
./setup.sh -h         # display help
./setup.sh -b -t      # build and test
sudo ./setup.sh -i    # install `puq` executable into bin directory
...
```

Compiled PUQ executable can be then run directly from a terminal.

``` bash
puq -h                 # display help
puq -i "J/s"           # expression information
puq -c "12*J" "erg"    # conversion of units
puq -c US "yd" SI "au" # conversion between unit systems
...
```

Lists of all units, quantities and unit sytems are accessible using `-l` flag:

``` bash
puq -l base
puq -l US deriv
puq -l AU quant
```

## Homebrew installation on Mac OS

On Mac OS it is possible to install PUQ using Homebrew package manager.
For now, you have to tap the scinumtools brew repository and install the code as follows:

``` bash
brew tap vrtulka23/scinumtools
brew install vrtulka23/scinumtools/scnt-puq
```
