pragma solidity 0.4.18;

contract ERC20Interface {
    function totalSupply() public view returns (uint);
    function balanceOf(address tokenOwner) public view returns (uint balance);
    function allowance(address tokenOwner, address spender) public view returns (uint remaining);
    function transfer(address to, uint tokens) public returns (bool success);
    function approve(address spender, uint tokens) public returns (bool success);
    function transferFrom(address from, address to, uint tokens) public returns (bool success);

    event Transfer(address indexed from, address indexed to, uint tokens);
    event Approval(address indexed tokenOwner, address indexed spender, uint tokens);
}

contract NewContract1 is ERC20Interface {
	uint8 public decimals;
	string public name;
	string public symbol;
	using SafeMath for uint;
	mapping(address => uint) balances;
	mapping(address => mapping (address => uint)) allowed;
}
