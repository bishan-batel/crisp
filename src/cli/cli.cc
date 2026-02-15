#include <crisp/lib.hpp>
#include "crisp/lexer/Lexer.hpp"
#include "crisp/token/IToken.hpp"

i32 main() {
  using namespace crisp;

  String test{R"( if let else )"};

  lexer::TokenList tokens = crisp::lexer::Lexer{test}.tokenize().unwrap();

  fmt::println("Tokens: ");

  for (const tok::IToken& token: tokens) {
    fmt::println("\t - {}", token.to_string());
  }
}
