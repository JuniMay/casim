#include "core/utils.hpp"

namespace casim {
namespace core {

const std::string& raise_error_msg(const std::string& desc) {
  std::string msg = "[ CASIM CORE ERROR ] " + desc;
  return msg;
}

}  // namespace core
}  // namespace casim