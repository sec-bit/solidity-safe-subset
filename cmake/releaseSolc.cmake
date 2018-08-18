include(ExternalProject)

include(GNUInstallDirs)
set(prefix "${CMAKE_BINARY_DIR}/deps")

ExternalProject_Add(release-solc-project
    PREFIX "${prefix}"
    DOWNLOAD_DIR "${CMAKE_SOURCE_DIR}/deps/downloads"
    DOWNLOAD_NAME solidity_0.4.24.tag.gz
    URL https://github.com/ethereum/solidity/releases/download/v0.4.24/solidity_0.4.24.tar.gz
    URL_HASH SHA256=b6828266d9b108a035f44127a6107c9fbc516018b0fcf5de370196306cddb2a8
    BUILD_COMMAND cmake ../release-solc-project -DCMAKE_BUILD_TYPE="Release" && make solc -j2 && cp solc/solc "${CMAKE_BINARY_DIR}/solc/solc-release"
    INSTALL_COMMAND cmake ../release-solc-project -DCMAKE_BUILD_TYPE="Release" && make solc -j2 && cp solc/solc "${CMAKE_BINARY_DIR}/solc/solc-release"
)
