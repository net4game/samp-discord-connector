VERSION 0.7

build:
    FROM ubuntu:20.04
    WORKDIR /work

    ARG DEBIAN_FRONTEND=noninteractive
    ARG BUILD_TYPE=Release
    ARG DCC_VERSION=dev
    ARG GH_ACBUILD=TRUE

    RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        gcc-multilib \
        g++-multilib \
        git \
        ninja-build \
        pkg-config \
        python3 \
        python3-pip \
        && rm -rf /var/lib/apt/lists/*

    RUN python3 -m pip install --no-cache-dir "conan<2" "cmake>=3.19,<4"

    ENV CMAKE_POLICY_VERSION_MINIMUM=3.5

    COPY . /work

    RUN test -d libs/log-core
    RUN test -d libs/cmake

    RUN cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
        -DCMAKE_C_FLAGS=-m32 \
        -DCMAKE_CXX_FLAGS=-m32 \
        -DCMAKE_EXE_LINKER_FLAGS=-m32 \
        -DCMAKE_SHARED_LINKER_FLAGS=-m32 \
        -DGH_ACBUILD=$GH_ACBUILD \
        -DDCC_VERSION=$DCC_VERSION
    RUN cmake --build build --config $BUILD_TYPE
    RUN mkdir -p build/artifact

    SAVE ARTIFACT build/artifact AS LOCAL build/artifact
