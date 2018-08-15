# The Solidity Safe Subset 

This repository is forked from the [Solidity Compiler](https://github.com/ethereum/solidity).

The purpose is to provide a safe subset of the Solidity language.

## Build

Please follow the same instruction for building Solidity compiler to build the SECBIT-extended `solc`.

## Usage

The basic command line is the same as `solc`, additional compiler errors are generated for Solidity
language features that are not within the safe subset.

## Modifications

Source code modifications from SECBIT are enclosed in `#ifdef SECBIT` directives.

## License

SECBIT Labs retains copyright to all above mentioned source code modifications. And the modifications
are licensed under the same license as Solidity.
