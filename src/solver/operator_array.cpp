#include "unit_solver.h"

#ifdef MAGNITUDE_ARRAYS

void OperatorArray::parse(exs::Expression &expr) {
  OperatorGroup<UnitAtom>::parse(expr);
};

void OperatorArray::operate_group(exs::TokenListBase<UnitAtom> *tokens) {
};

#endif
