/*
 * main.cc - Copyright (c) 2023 - Olivier Poncet
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <climits>
#include <algorithm>
#include <chrono>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Console.h"
#include "Program.h"
#include "main.h"

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    rpn::ArgList arglist ( argv
                         , argv + argc );

    rpn::Console console ( std::cin
                         , std::cout
                         , std::cerr );

    try {
        rpn::Program program(arglist, console);

        program.run();
    }
    catch(const std::exception& e) {
        console.log_error(e.what());
        return EXIT_FAILURE;
    }
    catch(...) {
        console.log_error("unhandled exception");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
