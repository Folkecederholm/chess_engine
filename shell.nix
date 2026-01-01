{ pkgs ? import <nixpkgs> {} }:

let
  system = builtins.currentSystem;
  isMac = builtins.substring 6 6 system == "darwin";
  clangPackage = if isMac then [] else [pkgs.clang];
in

pkgs.mkShell {
  packages = [
    pkgs.rustc
  ] ++ clangPackage;
}
