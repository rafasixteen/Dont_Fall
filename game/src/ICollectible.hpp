#pragma once

namespace Dont_Fall
{
	class ICollectible
	{
	public:
		virtual void Collect() const = 0;

		~ICollectible() = default;
	};
}