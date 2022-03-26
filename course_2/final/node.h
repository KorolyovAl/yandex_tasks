#pragma once
#include "date.h"
#include "comparison.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

enum struct LogicalOperation {
	And,
	Or,
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event) = 0;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date);
	bool Evaluate(const Date& date, const string& event);
	const Comparison _cmp;
	const Date _date;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string& value);
	bool Evaluate(const Date& date, const string& event);
	const Comparison _cmp;
	const string _value;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& log_operation, const shared_ptr<Node>& left, shared_ptr<Node> parse_expression);
	bool Evaluate(const Date& date, const string& event);
	const LogicalOperation log_op;
	const shared_ptr<Node> _left;
	const shared_ptr<Node> par_expr;
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const string& event);

};
