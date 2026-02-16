#pragma once

#include <crab/result/Err.hpp>
#include <crab/result/Result.hpp>
#include <crab/str/str.hpp>
#include "crisp/span/Spanned.hpp"

namespace crisp::lexer {

  class Error final {
  public:

    enum class Type {
      UnknownCharacter
    };

    explicit Error(Type type, SrcSpan span);

    [[nodiscard]] auto get_type() const -> Type;

    [[nodiscard]] auto get_span() const -> const SrcSpan&;

    [[nodiscard]] auto what() const -> String;

  private:

    Type type;
    SrcSpan span;
  };

  [[nodiscard]] inline auto format_as(const Error& err) -> String {
    return err.what();
  }

  template<typename... Args>
  [[nodiscard]] CRAB_INLINE auto make_err(Args&&... args) -> crab::Err<Error> {
    return crab::Err<Error>(Error(crab::forward<Args>(args)...));
  };

  template<typename T>
  using Result = crab::result::Result<T, Error>;

}
