#include <Singular/libsingular.h>

#include <share/include/interface.hpp>

#include <iostream>
#include <stdexcept>
#include <unistd.h>

#include "config.hpp"
#include "singular_functions.hpp"
NO_NAME_MANGLING


std::string serialize (lists lst , std::string const& base_filename, std::string const& ids)
{
	std::string out_filename = filename_generator ();
	out_filename = base_filename +  out_filename + ids;
	si_link l  = ssi_open_for_write (out_filename);
	ssi_write_newstruct (l, STRUCT_NAME, lst);
	ssi_close_and_remove (l);
	return out_filename;
}

std::pair<int, lists> deserialize (std::string const& filename, std::string const& ids)
{
	if (!(register_struct (STRUCT_NAME, STRUCT_DESC)))
	{
		 throw std::runtime_error (ids + ": singular_parallel_all_compute: could not register structs");
	}
	int type;
	blackboxIsCmd (STRUCT_NAME.c_str(), type);
	si_link l = ssi_open_for_read (filename);
	lists lst = ssi_read_newstruct (l, STRUCT_NAME);
	ssi_close_and_remove (l);
	return {type, lst};
}


std::string singular_compute( std::string const& input_filename 
																				
std::string const& mod_input
																			 
std::string const& function_name
																			 
std::string const& needed_library
																			 
std::string const& base_filename			)
{
	init_singular (config::library().string());
	load_singular_library(needed_library);
	std::pair<int, lists> p;
	std::pair<int,lists> input;
	std::pair<int, lists> out;
	std::string ids;
	std::string out_filename;
	ids = worker();
	std::cout << ids << " in singular_..._compute" << std::endl;
	p = deserialize(mod_input,ids);
	input = deserialize(input_filename,ids);
	ScopedLeftv args( input.first, lCopy(input.second));
	ScopedLeftv arg(args,p.first,lCopy(p.second));
	out = call_user_proc(function_name, needed_library, args);
	out_filename = serialize(out.second, base_filename, ids);
	return out_filename;
}
