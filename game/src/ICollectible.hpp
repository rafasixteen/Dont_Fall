#pragma once

class ICollectible
{
public:
	virtual void Collect() const = 0;

	~ICollectible() = default;
};
