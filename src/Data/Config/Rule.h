#pragma once

#include "CustomData.h"
#include "Property.h"

namespace Data
{
	class Rule final : public IPropertyContainer, public ICustomDataContainer
	{
	public:
		void AddProperty(const std::string& a_name, std::shared_ptr<Property> a_property) override;

		void AddCustomData(const std::string& a_name, const CustomData& a_data) override;

		bool Validate();

		bool SetInfo(RE::GFxValue* a_entryObject, bool& a_needsIconUpdate) const;

		void SetIcon(RE::GFxValue* a_entryObject) const;

	private:
		bool Match(const RE::GFxValue* a_entryObject) const;

		bool HasInfo() const;

		static bool ValidateIconSource(std::string a_iconSource);

		inline static util::istring_map<bool> _validatedSources;

		std::map<std::string, std::shared_ptr<Property>> _properties;
		std::map<std::string, CustomData> _customData;
	};
}
