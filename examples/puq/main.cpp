#import<iostream>
#import "../../src/puq.h"

class InputParser{
public:
  InputParser (int &argc, char **argv){
    for (int i=1; i < argc; ++i)
      this->tokens.push_back(std::string(argv[i]));
  }
  /// @author iain
  const std::vector<std::string> getCmdOption(const std::string &option, const int nstr=1) const{
    std::vector<std::string>::const_iterator itr;
    std::vector<std::string> strs;
    strs.reserve(nstr);
    itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
    for (int i=0;i<nstr;i++) {
      if (itr != this->tokens.end() && ++itr != this->tokens.end()){
	strs.push_back(*itr);
      }
    }
    return strs;
  }
  /// @author iain
    bool cmdOptionExists(const std::string &option) const{
      return std::find(this->tokens.begin(), this->tokens.end(), option)
	!= this->tokens.end();
    }
private:
  std::vector <std::string> tokens;
};

int main(int argc, char * argv[]) {
  InputParser input(argc, argv);
  if(input.cmdOptionExists("-h")){
    std::cout << "Help section" << std::endl;
  }
  std::vector<std::string> convert = input.getCmdOption("solve");
  if (!convert.empty()){
    UnitSolver solver;  
    UnitAtom atom = solver.solve(convert[0]);
    std::cout << convert[0] << " == " << atom.value.to_string() << std::endl;
  }
  convert = input.getCmdOption("-c",2);
  if (!convert.empty()){
    std::cout << convert[0] << " " << convert[1] << std::endl;
  }
}
