pragma solidity ^0.4.18;

contract Test {

    function factorial(uint8 n) internal pure {
	uint fact = 1;
        for (uint8 i = n; i > 1; i--) {
	     fact *= i;
	     fact += fact -
		     (
			     fact +
			     uint256(1)
		     );
	     fact -= i * fact;
        }
    }
}

contract TestOk {
	function ok() internal pure {
		uint8 i = 255;
		i = i + i;
	}
}
