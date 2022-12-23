#pragma once

#define NO_NAME_MANGLING extern "C"

#include <string>

NO_NAME_MANGLING

void serialize (       lists lst 
                       std::string const& base_filename
                       std::string const& ids)


void deserialize (      std::string const& filename
                        std::string const& ids)


void singular__compute (    std::string const& input_filename 
																				
                            std::string const& mod_input
                                                                                                        
                            std::string const& function_name
                                                                                                        
                            std::string const& needed_library
                                                                                                        
                            std::string const& base_filename	);