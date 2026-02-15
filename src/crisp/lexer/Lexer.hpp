#pragma once

#include <crab/collections/Vec.hpp>
#include <crab/mem/forward.hpp>
#include <crab/num/range.hpp>
#include <crab/rc/Rc.hpp>
#include <crab/result/Result.hpp>
#include <crab/result/forward.hpp>
#include "crisp/token/IToken.hpp"
#include "crisp/token/Spanned.hpp"
#include "Error.hpp"

namespace crisp::lexer {
  using tok::IToken;

  using TokenList = Vec<Rc<IToken>>;

  class Lexer final {
  public:

    explicit Lexer(StringView source, Option<String> source_file = {});

    /// Consumes self and attempts to fully tokenize input
    [[nodiscard]] auto tokenize() && -> Result<TokenList>;

  private:

    /// Emplaces a new token to the token list
    template<typename T, typename... Args>
    auto emplace(Args&&... args) -> void {
      tokens.push_back(crab::make_rc<T>(crab::forward<Args>(args)...));
    }

    [[nodiscard]] auto span(usize length = 1) const -> SrcSpan;

    [[nodiscard]] auto span(crab::Range<> range) const -> SrcSpan;

    [[nodiscard]] auto skip_whitespace() -> bool;

    [[nodiscard]] auto scan_keyword() -> bool;

    [[nodiscard]] auto current() const -> Option<char>;

    [[nodiscard]] auto consume() -> Option<char>;

    auto advance(usize i = 1) -> void;

    [[nodiscard]] auto not_finished() const -> bool;

    StringView source;
    TokenList tokens;
    Option<String> file;
    usize index = 0;
  };

  [[nodiscard]] auto is_identifier_char(char c) -> bool;

  [[nodiscard]] auto is_whitespace(char c) -> bool;
}
