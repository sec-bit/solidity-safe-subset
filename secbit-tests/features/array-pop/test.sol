pragma solidity ^0.4.16;

contract ArrayContract {
    bool[2][] m_a;

    bool[][2] m_b;
    
    function f() public {
	bool[2] memory a;
	a[0] = true;
	a[1] = false;
        m_b[1].push(false);
	m_a.push(a);
	m_b[1].pop();
	m_a.pop();
    }
}
