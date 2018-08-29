# The Solidity Safe Subset 

This repository is forked from the [Solidity Compiler](https://github.com/ethereum/solidity).

The purpose is to provide a safe subset of the Solidity language.

The compiler `solc` now works in two steps:
1. the first step invokes `solc-safe-subset` which
will fail on language features not allowed by the safe subset,
and make source-level transformation if needed;
2. the second step invokes `solc-release` (a release version
of `solc` from ethereum/solidity repo) to actually
compile the source file

This is to make sure that the compilation result is 100% compatible with the result from a stock `solc`
compiler. `solc-safe-subset` only does screening and transformation of the source code.

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

The basic command line is the same as `solc`, but additional compiler errors are generated for Solidity
language features that are not within the safe subset.

The binary `solc-safe-subset` also provides an additional option
`--transform` for performing source-level transformation.
The currently supported transformations including:
* changing overflowing `+`, `-`, and `*` to `SafeMath` calls
* changing `array.pop()` to `array.length > 0 ? delete array[array.length--] : ()`

## Modifications

Source code modifications from SECBIT are enclosed in `#ifdef SECBIT` directives.

## License

SECBIT Labs retains copyright to all above mentioned source code modifications. And the modifications
are licensed under the same license as Solidity.
