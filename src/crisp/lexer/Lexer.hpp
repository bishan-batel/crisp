#pragma once

#include <crab/collections/Vec.hpp>
#include <crab/rc/Rc.hpp>
#include <crab/result/Result.hpp>
#include <crab/result/forward.hpp>
#include "crisp/token/IToken.hpp"
#include "crisp/token/Spanned.hpp"

namespace crisp::lexer {
  using tok::IToken;

  using TokenList = Vec<Rc<Spanned<IToken>>>;

  class Error final : crab::IError {
  public:

    enum class Type {
      UnknownCharacter
    };

    explicit Error(Type type, SrcSpan span);

    [[nodiscard]] auto get_type() const -> Type;

    [[nodiscard]] auto get_span() const -> const SrcSpan&;

    [[nodiscard]] auto what() const -> String override;

  private:

    Type type;
    SrcSpan span;
  };

  template<typename... Args>
  [[nodiscard]] CRAB_INLINE auto make_err(Args&&... args) -> crab::Err<Error> {
    return crab::Err<Error>(Error(crab::forward<Args>(args)...));
  };

  template<typename T>
  using Result = crab::result::Result<T, Error>;

  class Lexer final {

    explicit Lexer(StringView source);

    [[nodiscard]] auto tokenize() && -> Result<Vec<Rc<IToken>>>;

  private:

    [[nodiscard]] auto scan_keyword() -> bool;

    [[nodiscard]] auto current() const -> Option<char>;

    [[nodiscard]] auto consume() -> Option<char>;

    auto advance(usize i = 1) -> void;

    [[nodiscard]] auto not_finished() const -> bool;

    StringView source;
    Vec<Rc<IToken>> tokens;
    usize index = 0;
  };
}
