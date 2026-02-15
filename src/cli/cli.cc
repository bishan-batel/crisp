#include <crisp/lib.hpp>
#include <fstream>
#include "crisp/lexer/Lexer.hpp"
#include "crisp/token/IToken.hpp"

i32 main(i32 argc, char* argv[]) {
  using namespace crisp;

  String source{R"( if let else )"};
  Option<String> file_name{};

  if (argc > 1) {
    file_name = argv[1];

    StringStream stream{};
    stream << std::ifstream{argv[1]}.rdbuf();
    source = crab::move(stream).str();
  }

  lexer::TokenList tokens = crisp::lexer::Lexer{source, file_name}.tokenize().unwrap();

  fmt::println("Tokens: ");

  for (const tok::IToken& token: tokens) {
    fmt::println("\t - {1} ({0})", typeid(token).name(), token.to_string());
  }
}
