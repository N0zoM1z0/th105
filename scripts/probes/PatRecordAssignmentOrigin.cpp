#include "../../src/battle/PatResourceContracts.hpp"

// Request the real implicit assignment operator; no copied implementation.
typedef th105::PatRecord88 &(th105::PatRecord88::*PatAssignmentMember)(
    const th105::PatRecord88 &);
PatAssignmentMember instantiate_pat_record_assignment =
    &th105::PatRecord88::operator=;
