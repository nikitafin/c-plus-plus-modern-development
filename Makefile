.PHONY: base clean
.PHONY: workflow-clang workflow-gcc workflow-clang-ci workflow-gcc-ci
.PHONY: build-image-dev build-image-ci
.PHONY: ci-clang ci-gcc
.PHONY: run

base: clean workflow-clang

clean:
	rm -rf out

workflow-clang:
	docker run -it --rm -v $(CURDIR):/src -w /src dev cmake --workflow --preset work-clang-dev

workflow-gcc:
	docker run -it --rm -v $(CURDIR):/src -w /src dev cmake --workflow --preset work-gcc-dev

workflow-clang-ci:
	docker run --rm -v $(CURDIR):/src -w /src ci cmake --workflow --preset work-clang-dev

workflow-gcc-ci:
	docker run --rm -v $(CURDIR):/src -w /src ci cmake --workflow --preset work-gcc-dev

build-image-dev:
	docker build -t dev -f util/Dockerfile.dev .

build-image-ci:
	docker build -t ci -f util/Dockerfile.ci .

ci-clang: clean workflow-clang-ci

ci-gcc: clean workflow-gcc-ci

run:
	docker run -it --rm -v $(CURDIR):/src -w /src dev bash
