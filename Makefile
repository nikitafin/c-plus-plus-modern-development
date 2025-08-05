.PHONY: base clean workflow build-image all

base: workflow

workflow:
	docker run -it --rm -v $(CURDIR):/src -w /src dev cmake --workflow --preset work-clang-testing

clean:
	rm -rf out

build-image:
	docker build -t dev -f util/Dockerfile .

all: clean build-image workflow
