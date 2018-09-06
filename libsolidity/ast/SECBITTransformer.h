/*
    The SECBIT Solidity Safe Subsect.

    Copyright (c) SECBIT Labs 2018.

    This file is part of solidity.

    solidity is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    solidity is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifdef SECBIT

#pragma once

#include <ostream>
#include <libsolidity/ast/ASTVisitor.h>
#include <libsolidity/interface/GasEstimator.h>

namespace dev
{
namespace solidity
{

class SECBITTransformer: public ASTConstVisitor
{
public:
	SECBITTransformer(
		ASTNode const& _ast,
		std::string const& _source = std::string()
	);
	/// Output the transformed source code.
	void print(std::ostream& _stream);

	bool visit(ContractDefinition const&) override;
	bool visit(UsingForDirective const&) override;
	bool visit(ForStatement const&) override;

	void endVisit(ContractDefinition const&) override;
	void endVisit(Assignment const&) override;
	void endVisit(BinaryOperation const&) override;
	void endVisit(FunctionCall const&) override;
	void endVisit(Identifier const&) override;

private:
	// Source code.
	std::string m_source;
	// AST.
	ASTNode const* m_ast;

	// A cache for AST node and their replacement text.
	std::map<SourceLocation, std::string> m_replacements;

	// Get the replacement text for _node. Using the above cache.
	std::string getReplacement(ASTNode const& _node);

	// Get the replacement text for _loc to _stream.
	void getReplacement(SourceLocation const& _loc,
			    std::ostream& _stream);

	// True if the current contract need safemath replacements.
	bool m_needReplace = false;
	// True if the current contract has safemath replacements.
	bool m_hasReplace = false;
	// True if we are still in the first contract in the source file.
	bool m_firstContract = true;

	// Loop variable declaration and replacement for for-each loops.
	std::map<Declaration const*, std::string> m_forEachLoopVarReplacement;
};

}
}

#endif
