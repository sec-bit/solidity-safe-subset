pragma solidity 0.4.18;

contract NewContract {
	uint8 public decimals;
	string public name;
	string public symbol;

	modifier onlyPayloadSize(uint size) {
		require(msg.data.length >= size + 4);
		_;
	}
	function transfer(address to, uint tokens) public returns (bool success) {
		require(msg.data.length >= 2*32);
		return false;
	}
}
