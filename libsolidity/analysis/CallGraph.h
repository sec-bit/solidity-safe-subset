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

#include <libsolidity/ast/AST.h>
#include <libsolidity/ast/ASTVisitor.h>
#include <libsolidity/interface/ErrorReporter.h>

#include <vector>

namespace dev
{
namespace solidity
{

struct CallGraphEdge
{
	FunctionDefinition const* m_caller;
	FunctionDefinition const* m_callee;
};

class CallGraph: public ASTConstVisitor
{
public:
	explicit CallGraph(ErrorReporter& _errorReporter): m_errorReporter(_errorReporter) {}

	// build call graph.
	bool build(ASTNode const& _astRoot);
	// check if there're recursive calls in call graph.
	bool checkRecursiveCall();
	// return the index of _callee in _visited.
	std::vector<CallGraphEdge const*>::iterator findCycle(std::vector<CallGraphEdge const*>& _visited,
							      CallGraphEdge const* _callee);

	virtual bool visit(ContractDefinition const& _contract) override;
	virtual bool visit(FunctionDefinition const& _function) override;
	virtual bool visit(FunctionCall const& _function) override;

	virtual void endVisit(ContractDefinition const& _contract) override;
	virtual void endVisit(FunctionDefinition const& _function) override;

	void addEdge(FunctionDefinition const* _caller, FunctionDefinition const* _callee);
	void deleteEdge(FunctionDefinition const* _caller, FunctionDefinition const* _callee);
	std::vector<CallGraphEdge>::iterator findEdge(FunctionDefinition const* _caller,
						      FunctionDefinition const* _callee);
	std::vector<CallGraphEdge const*> edgesOutOf(FunctionDefinition const* _caller);
	std::vector<CallGraphEdge const*> edgesInTo(FunctionDefinition const* _callee);

	// print call graph edges.
	void print();

private:
	ErrorReporter m_errorReporter;
	std::vector<CallGraphEdge> m_edges;
	std::vector<FunctionDefinition const*> m_currentFunction;
	std::vector<FunctionDefinition const*> m_definedFunctions;
};
 
}
}

#endif
