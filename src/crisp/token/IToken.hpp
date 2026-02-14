#pragma once

#include <crab/str/str.hpp>
#include <typeinfo>

#include <crab/ref/is_exact.hpp>

namespace crisp::tok {
  class IToken {

  public:

    IToken() = default;

    IToken(const IToken&) = delete;

    IToken(IToken&&) = delete;

    IToken& operator=(const IToken&) = delete;

    IToken& operator=(IToken&&) = delete;

    virtual ~IToken() = default;

    [[nodiscard]] virtual auto to_string() const -> String = 0;
  };
}
