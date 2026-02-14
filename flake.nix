{
  description = "Crisp";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";

    crab.url = "github:bishan-batel/crab";
  };

  outputs = { 
    self, nixpkgs, flake-utils, crab, ...
    }: flake-utils.lib.eachDefaultSystem (system: let
      pkgs = nixpkgs.legacyPackages.${system};
      crabPkgs = crab.packages.${system};
      libPath = [ crabPkgs.default pkgs.fmt ]; 
    in {

      devShells = { 
        default = pkgs.mkShell {
            name = "na-engine";
            packages = with pkgs; [
              ninja
              sccache
              cmake
              unzip
              doxygen
              llvmPackages.clang-tools 
            ];

            buildInputs = [ pkgs.pkg-config ];
            nativeBuildInputs = [] ++ libPath;

            LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath libPath;
          };
      };
    });
}
