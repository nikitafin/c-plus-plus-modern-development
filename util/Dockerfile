FROM ubuntu:plucky-20250714

RUN apt update \
    && apt upgrade -y \
    && apt install -y --no-install-recommends \
    git \
    build-essential ninja-build cmake \
    gcc g++ \
    clang clang-format clang-tidy

CMD ["/usr/bin/bash"]
