#include "node.h"

	DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : _cmp(cmp), _date(date) {}

	bool DateComparisonNode::Evaluate(const Date& date, const string& event) {
		switch (_cmp) {
		case Comparison::Less:

			if (date.GetYear() < _date.GetYear()) {
				return true;
			}
			else if (date.GetYear() == _date.GetYear()) {

				if (date.GetMonth() < _date.GetMonth()) {
					return true;
				}
				else if (date.GetMonth() == _date.GetMonth()) {

					if (date.GetDay() < _date.GetDay()) {
						return true;
					}
					else if (date.GetDay() == _date.GetDay()) {
						return false;
					}
					else return false;
				}
				else return false;
			}
			else return false;

		case Comparison::LessOrEqual:

			if (date.GetYear() < _date.GetYear()) {
				return true;
			}
			else if (date.GetYear() == _date.GetYear()) {

				if (date.GetMonth() < _date.GetMonth()) {
					return true;
				}
				else if (date.GetMonth() == _date.GetMonth()) {

					if (date.GetDay() < _date.GetDay()) {
						return true;
					}
					else if (date.GetDay() == _date.GetDay()) {
						return true;
					}
					else return false;
				}
				else return false;
			}
			else return false;

		case Comparison::Greater:

			if (date.GetYear() > _date.GetYear()) {
				return true;
			}
			else if (date.GetYear() == _date.GetYear()) {

				if (date.GetMonth() > _date.GetMonth()) {
					return true;
				}
				else if (date.GetMonth() == _date.GetMonth()) {

					if (date.GetDay() > _date.GetDay()) {
						return true;
					}
					else if (date.GetDay() == _date.GetDay()) {
						return false;
					}
					else return false;
				}
				else return false;
			}
			else return false;

		case Comparison::GreaterOrEqual:

			if (date.GetYear() > _date.GetYear()) {
				return true;
			}
			else if (date.GetYear() == _date.GetYear()) {

				if (date.GetMonth() > _date.GetMonth()) {
					return true;
				}
				else if (date.GetMonth() == _date.GetMonth()) {

					if (date.GetDay() > _date.GetDay()) {
						return true;
					}
					else if (date.GetDay() == _date.GetDay()) {
						return true;
					}
					else return false;
				}
				else return false;
			}
			else return false;

		case Comparison::Equal:

			if (_date.GetYear() == date.GetYear()) {
				if (_date.GetMonth() == date.GetMonth()) {
					if (_date.GetDay() == date.GetDay()) {
						return true;
					}
					else return false;
				}
				else return false;
			}
			else return false;

		case Comparison::NotEqual:
			if (_date.GetYear() != date.GetYear()) {
				return true;
			}
			else if (_date.GetMonth() != date.GetMonth()) {
				return true;
			}
			else if (_date.GetDay() != date.GetDay()) {
				return true;
			}
			else return false;
		}
		return false;
	}

	EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& value) : _cmp(cmp), _value(value) {}

	bool EventComparisonNode::Evaluate(const Date& date, const string& event) {
		switch(_cmp) {
		case Comparison::Less:

			if (event < _value) {
				return true;
			}
			else return false;

		case Comparison::LessOrEqual:

			if (event <= _value) {
				return true;
			}
			else return false;

		case Comparison::Greater:

			if (event > _value) {
				return true;
			}
			else return false;

		case Comparison::GreaterOrEqual:

			if (event >= _value) {
				return true;
			}
			else return false;

		case Comparison::Equal:

			if (event == _value) {
				return true;
			}
			else return false;

		case Comparison::NotEqual:

			if (event != _value) {
				return true;
			}
			else return false;
		}
		return false;
	}

	LogicalOperationNode::LogicalOperationNode(const LogicalOperation& log_operation, const shared_ptr<Node>& left, shared_ptr<Node> parse_expression)
		: log_op(log_operation), _left(left), par_expr(parse_expression) {}

	bool LogicalOperationNode::Evaluate(const Date& date, const string& event) {
		if (log_op == LogicalOperation::And) return _left->Evaluate(date, event) && par_expr->Evaluate(date, event);
		else if (log_op == LogicalOperation::Or) return _left->Evaluate(date, event) || par_expr->Evaluate(date, event);
		else return false;
	}

	bool EmptyNode::Evaluate(const Date& date, const string& event) {
		return true;
	}

