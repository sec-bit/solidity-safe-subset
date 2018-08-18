include ../../test.mk

TEST_SOL:=test.sol

tests: gen-output cmp-output

gen-output:
	@$(SOLC) $(TEST_SOL) --abi > $(output) 2>&1 || exit 0
