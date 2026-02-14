#pragma once

#include "crisp/token/IToken.hpp"

namespace crisp::tok {

  class Keyword final : IToken {

  public:

    enum class Word {
      If,
      Else,
      Let,
      Func
    };

    explicit Keyword(Word word);

    [[nodiscard]] auto to_string() const -> String override;

  private:

    Word word;
  };
}
