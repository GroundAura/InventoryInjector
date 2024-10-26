#include "GFxUtil.h"

namespace Data
{
	void GFxUtil::IndentState::WriteIndent(std::stringstream& a_stream) const
	{
		if (!indentString) {
			a_stream << ' ';
			return;
		}

		for (int i = 0; i < indentDepth; ++i) {
			a_stream << indentString;
		}
	}

	std::string GFxUtil::Stringify(const RE::GFxValue& a_value)
	{
		std::stringstream stream{};
		constexpr IndentState state{ .indentString = nullptr, .indentDepth = 0 };

		Serialize(a_value, stream, state);

		return stream.str();
	}

	void GFxUtil::Serialize(
		const RE::GFxValue& a_value,
		std::stringstream& a_stream,
		const IndentState& a_state)
	{
		switch (a_value.GetType()) {
		case RE::GFxValue::ValueType::kUndefined:
			a_stream << "undefined";
			break;

		case RE::GFxValue::ValueType::kNull:
			a_stream << "null";
			break;

		case RE::GFxValue::ValueType::kBoolean:
			a_stream << (a_value.GetBool() ? "true" : "false");
			break;

		case RE::GFxValue::ValueType::kNumber:
			a_stream << a_value.GetNumber();
			break;

		case RE::GFxValue::ValueType::kString:
			// TODO escape this
			a_stream << '"' << a_value.GetString() << '"';
			break;

		case RE::GFxValue::ValueType::kStringW:
			// TODO
			a_stream << "<wstring>";
			break;

		case RE::GFxValue::ValueType::kObject:
		{
			a_stream << '{';
			auto nestedState = a_state;
			nestedState.indentDepth++;

			a_value.VisitMembers(
				[&a_stream, nestedState](const char* name, const RE::GFxValue& member)
				{
					nestedState.WriteIndent(a_stream);
					a_stream << name << ": ";
					Serialize(member, a_stream, nestedState);
					a_stream << ',';
				});

			a_state.WriteIndent(a_stream);
			a_stream << '}';
			break;
		}

		case RE::GFxValue::ValueType::kArray:
		{
			a_stream << '[';
			auto nestedState = a_state;
			nestedState.indentDepth++;

			const auto count = a_value.GetArraySize();
			for (uint32_t i = 0; i < count; ++i) {
				RE::GFxValue element;
				a_value.GetElement(i, &element);
				Serialize(element, a_stream, nestedState);
				a_stream << ',';
			}

			a_state.WriteIndent(a_stream);
			a_stream << ']';
			break;
		}

		case RE::GFxValue::ValueType::kDisplayObject:
			a_stream << "<display object>";
			break;

		case RE::GFxValue::ValueType::kManagedBit:
		case RE::GFxValue::ValueType::kConvertBit:
		case RE::GFxValue::ValueType::kValueMask:
		case RE::GFxValue::ValueType::kTypeMask:
		case RE::GFxValue::ValueType::kConvertBoolean:
		case RE::GFxValue::ValueType::kConvertNumber:
		case RE::GFxValue::ValueType::kConvertString:
		case RE::GFxValue::ValueType::kConvertStringW:
			a_stream << "<invalid>";
			break;
		}
	}
}
