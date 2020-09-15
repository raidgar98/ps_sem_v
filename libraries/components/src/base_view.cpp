#include "../include/base_view.hpp"

base_view::base_view(const paint_config* cfg, paint_visitor& pv)
	:_painter{pv} 
{
	set_config(cfg);
}