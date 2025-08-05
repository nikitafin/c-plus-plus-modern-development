FROM dev
ARG source_path=/src

WORKDIR ${source_path}
CMD ["cmake", "--workflow", "--preset", "work-clang-testing"]
