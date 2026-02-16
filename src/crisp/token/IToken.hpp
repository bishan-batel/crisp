#pragma once

#include <crab/str/str.hpp>
#include <typeinfo>

#include <crab/ref/is_exact.hpp>
#include "crisp/span/Spanned.hpp"

namespace crisp::tok {
  class IToken {

  public:

    inline explicit IToken(SrcSpan span): span{crab::move(span)} {}

    IToken(const IToken&) = delete;

    IToken(IToken&&) = delete;

    IToken& operator=(const IToken&) = delete;

    IToken& operator=(IToken&&) = delete;

    virtual ~IToken() = default;

    [[nodiscard]] virtual auto to_string() const -> String = 0;

    [[nodiscard]] inline auto get_span() const -> SrcSpan {
      return span;
    }

  private:

    SrcSpan span;
  };
}
