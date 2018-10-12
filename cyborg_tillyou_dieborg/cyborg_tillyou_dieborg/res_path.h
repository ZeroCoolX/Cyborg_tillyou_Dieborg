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

std::string getResourcePath(const std::string &subDir = "");

#endif

