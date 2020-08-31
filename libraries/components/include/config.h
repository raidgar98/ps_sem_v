#pragma once

#include "../../types.hpp"

class config
{
protected:
	virtual bool dump_config(const char* file_name) const { return false; };
	virtual bool load_config(const char* file_name) { return false; }
};

// config data is not deleted, only release!!!
class configurable
{
protected:
	config* _config{ nullptr };

	~configurable()
	{
		_config = nullptr;
	}

	template<typename T>
	const T* get_config() const 
	{
		require( _config );
		return dynamic_cast<T*>(_config);
	}
};
