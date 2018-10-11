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

#include <libsolidity/analysis/CallGraph.h>

using namespace std;

namespace dev
{
namespace solidity
{

bool CallGraph::build(ASTNode const& _astRoot)
{
	_astRoot.accept(*this);
	return Error::containsOnlyWarnings(m_errorReporter.errors());
}

bool CallGraph::checkRecursiveCall()
{
	vector<CallGraphEdge const*> visited;
	visited.clear();
	for (vector<CallGraphEdge>::iterator edge = m_edges.begin(); edge != m_edges.end(); edge++)
	{
		visited.push_back(&(*edge));

		vector<CallGraphEdge const*> outEdges = edgesOutOf(edge->m_callee);
		for (vector<CallGraphEdge const*>::iterator iter = outEdges.begin(); iter != outEdges.end(); iter++)
		{
			vector<CallGraphEdge const*>::iterator index = findCycle(visited, *iter);
			if (index != visited.end())
			{
				string callring = "";
				for (vector<CallGraphEdge const*>::iterator calls = index; calls != visited.end(); calls++)
					callring += (*calls)->m_caller->name() + " -> " + (*calls)->m_callee->name() + "\n";

				m_errorReporter.fatalParserError(
					(*index)->m_caller->location(),
					"Found recursive function calls:\n" + callring +
					"Recursive Calls can be used in gas limit attack," +
					" forbidden by SECBIT Solidity safe subset.");
				return false;
			}
		}
		visited.pop_back();
	}

	return true;
}

vector<CallGraphEdge const*>::iterator CallGraph::findCycle(vector<CallGraphEdge const*>& _visited,
							    CallGraphEdge const* _outEdge)
{
	// check if _outEdge in _visited.
	for (vector<CallGraphEdge const*>::iterator iter = _visited.begin(); iter != _visited.end(); iter++)
	{
		if (*iter == _outEdge)
			return iter;
	}

	// otherwise
	_visited.push_back(_outEdge);
	vector<CallGraphEdge const*> calls = edgesOutOf(_outEdge->m_callee);	  
	for (vector<CallGraphEdge const*>::iterator iter = calls.begin(); iter != calls.end(); iter++)
	{
		vector<CallGraphEdge const*>::iterator ret = findCycle(_visited, *iter);
		if (ret != _visited.end())
			return ret;
	}
	_visited.pop_back();
	return _visited.end();
}

bool CallGraph::visit(ContractDefinition const& _contract)
{
	m_definedFunctions = _contract.definedFunctions();
	return true;
}

void CallGraph::endVisit(ContractDefinition const&)
{
	m_definedFunctions.clear();
}

bool CallGraph::visit(FunctionDefinition const& _function)
{
	m_currentFunction.push_back(&_function);
	return true;
}

void CallGraph::endVisit(FunctionDefinition const&)
{
	m_currentFunction.pop_back();
}
  
bool CallGraph::visit(FunctionCall const& _function)
{
	FunctionDefinition const* callee = nullptr;

	// find FunctionDefinition in definedFunctions for callee
	auto functionName = dynamic_cast<Identifier const*>(&_function.expression());
	for (vector<FunctionDefinition const*>::iterator iter = m_definedFunctions.begin();
	     iter != m_definedFunctions.end(); iter++)
	{
		// we disable function overloading, so name matching is enough.
		if (functionName->name() == (*iter)->name())
		{
			callee = *iter;
			break;
		}
	}

	if (callee == nullptr)
		return false;
  
	// add Edge
	if (findEdge(m_currentFunction.back(), callee) == m_edges.end())
		addEdge(m_currentFunction.back(), callee);
	return false;
}

void CallGraph::addEdge(FunctionDefinition const* _caller, FunctionDefinition const* _callee)
{
	CallGraphEdge edge;
	edge.m_caller = _caller;
	edge.m_callee = _callee;
	m_edges.push_back(edge);
}

void CallGraph::deleteEdge(FunctionDefinition const* _caller, FunctionDefinition const* _callee)
{
	vector<CallGraphEdge>::iterator iter = findEdge(_caller, _callee);
	if (iter != m_edges.end())
		m_edges.erase(iter);
	return;
}

vector<CallGraphEdge>::iterator CallGraph::findEdge(FunctionDefinition const* _caller,
						    FunctionDefinition const* _callee)
{
	for (vector<CallGraphEdge>::iterator iter = m_edges.begin(); iter != m_edges.end(); iter++)
		if (iter->m_caller == _caller && iter->m_callee == _callee)
			return iter;
	return m_edges.end();
}

void CallGraph::print()
{
	for (vector<CallGraphEdge>::iterator iter = m_edges.begin(); iter != m_edges.end(); iter++)
		cout << iter->m_caller->name() << " -> " << iter->m_callee->name() << endl;
}

vector<CallGraphEdge const*> CallGraph::edgesOutOf(FunctionDefinition const* _caller)
{
	vector<CallGraphEdge const*> ret;
	for (vector<CallGraphEdge>::iterator iter = m_edges.begin(); iter != m_edges.end(); iter++)
	{
		if (iter->m_caller == _caller)
			ret.push_back(&(*iter));
	}
	return ret;
}

vector<CallGraphEdge const*> CallGraph::edgesInTo(FunctionDefinition const* _callee)
{
	vector<CallGraphEdge const*> ret;
	for (vector<CallGraphEdge>::iterator iter = m_edges.begin(); iter != m_edges.end(); iter++)
	{
		if (iter->m_callee == _callee)
			ret.push_back(&(*iter));
	}
	return ret;
}

}
}

#endif
