#ifndef CODEGEN_MACRO_HPP
#define CODEGEN_MACRO_HPP
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#define SER_SCOPE_BEGIN \
namespace boost {\
namespace serialization {

#define SER_SCOPE_END }}

#endif