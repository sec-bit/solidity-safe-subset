# The Solidity Safe Subset 

This repository is forked from the [Solidity Compiler](https://github.com/ethereum/solidity).

The purpose is to provide a safe subset of the Solidity language.

The compiler `solc` now works in two steps:
1. the first step invokes `solc-safe-subset` which
will fail on language features not allowed by the safe subset;
2. the second step invokes `solc-release` (a release version
of `solc` from ethereum/solidity repo) to actually
compile the source file

This is to make sure that the compilation result is 100% compatible with the result from a stock `solc`
compiler. `solc-safe-subset` only does screening of the source code.

## Build

The build process also includes a build of the release version of `solc` as `solc-release`.

The whole build process could be triggered by
```
$ cd <repo-root>
$ mkdir build
$ cd build
$ cmake ..
$ make solc-safe-subset
```

The resulting binaries would be
```
<repo-root>/build/solc/solc             // the two-stage compiler
<repo-root>/build/solc/solc-safe-subset // the safe subsect checker
<repo-root>/build/solc/solc-release     // the stock solc
```

## Usage

The basic command line is the same as `solc`, additional compiler errors are generated for Solidity
language features that are not within the safe subset.

## Modifications

Source code modifications from SECBIT are enclosed in `#ifdef SECBIT` directives.

## License

SECBIT Labs retains copyright to all above mentioned source code modifications. And the modifications
are licensed under the same license as Solidity.
