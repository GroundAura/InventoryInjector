#pragma once

namespace Hooks
{
	class IconSetter final
	{
	public:
		IconSetter() = delete;

		static void Install(RE::GFxMovieView* a_view, const char* a_pathToObj);

		static void ProcessEntry(RE::GFxValue* a_thisPtr, RE::GFxValue* a_entryObject);

	private:
		static void ProcessIconInternal(RE::GFxValue* a_thisPtr, RE::GFxValue* a_entryObject);

		class ProcessListFunc : public RE::GFxFunctionHandler
		{
		public:
			ProcessListFunc(const RE::GFxValue& a_oldFunc) : _oldFunc{ a_oldFunc } {}

			void Call(Params& a_params) override;

		private:
			RE::GFxValue _oldFunc;
		};
	};
}