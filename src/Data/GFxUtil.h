#pragma once

#include "RE/G/GFxValue.h"

#include <string>

namespace Data
{
	class GFxUtil final
	{
	public:
		static std::string Stringify(const RE::GFxValue& a_value);

	private:
		struct IndentState
		{
			// Set to nullptr to disable indentation.
			const char* indentString = "  ";
			int indentDepth;

			void WriteIndent(std::stringstream& a_stream) const;
		};

		static void Serialize(
			const RE::GFxValue& a_value,
			std::stringstream& a_stream,
			const IndentState& a_state);
	};
}
