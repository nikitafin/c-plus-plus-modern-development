.PHONY: base clean workflow workflow-ci build-image all ci

base: workflow

workflow:
	docker run -it --rm -v $(CURDIR):/src -w /src dev cmake --workflow --preset work-clang-testing

workflow-ci:
	docker run --rm -v $(CURDIR):/src -w /src dev cmake --workflow --preset work-clang-testing

clean:
	rm -rf out

build-image:
	docker build -t dev -f util/Dockerfile .

all: clean build-image workflow-ci

ci: clean workflow-ci
