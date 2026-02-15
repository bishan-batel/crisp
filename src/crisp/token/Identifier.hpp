#pragma once

#include <crab/preamble.hpp>

#include "crisp/token/IToken.hpp"
#include "crisp/token/Spanned.hpp"

namespace crisp::tok {

  class Identifier final : public IToken {

  public:

    explicit Identifier(String name, SrcSpan span);

    [[nodiscard]] auto get_name() const -> const String&;

    [[nodiscard]] auto to_string() const -> String override;

  private:

    String name;
  };
}
