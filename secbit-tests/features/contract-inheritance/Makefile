include ../../test.mk

TEST_SOL:=test.sol

tests: gen-output cmp-output

gen-output:
	@$(SOLC) $(TEST_SOL) 2> $(output) || exit 0
