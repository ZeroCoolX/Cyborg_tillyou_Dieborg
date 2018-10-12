#ifndef RES_PATH_H
#define RES_PATH_H

#include<iostream>
#include<string>
#include<SDL.h>

/*
	Get the resource path for resources located in res/subDir
	ITs's assumed the project directory is structured like:
	bin/
		exe
	res/
		topic1
		topic2
*/

std::string get_resource_path(const std::string &subDir = "");

#endif

