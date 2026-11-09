// The input table at 0x6FCA2C uses the existing bootstrap input class.
// Its 0x43B300 accessor is VC8 vector::operator[], not authored range policy.
#include "engine/SceneResourceBootstrap.cpp"

template std::vector<th105::SceneBootstrapInputEx>::reference
std::vector<th105::SceneBootstrapInputEx>::operator[](size_type);
