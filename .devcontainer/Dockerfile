FROM git.justmichael.xyz/containers/basedevcontainer:debian

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    gcc-multilib \
    g++-multilib \
    libc6-dev-i386 \
    cmake \
    make \
    git \
    pkg-config \
    python3 \
    python3-pip \
    ca-certificates \
    curl \
    unzip \
    && python3 -m pip install --no-cache-dir --break-system-packages "conan<2" \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
