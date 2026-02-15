#include "Identifier.hpp"

namespace crisp::tok {
  Identifier::Identifier(String name, SrcSpan span): IToken{crab::move(span)}, name{crab::move(name)} {}

  [[nodiscard]] auto Identifier::get_name() const -> const String& {
    return name;
  }

  [[nodiscard]] auto Identifier::to_string() const -> String {
    return name;
  }
}
