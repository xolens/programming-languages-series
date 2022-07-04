all: build test

build:
	$(MAKE) -C ../build

test: 
	reset
	@printf "\033[1mExecuting test suite...\033[0m\n"
	$(MAKE) -C ./expressions --no-print-directory
	@printf "\033[1mDone...\033[0m\n"
