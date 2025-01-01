/*
 * Listener.cc - Copyright (c) 2023-2025 - Olivier Poncet
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
#include "State.h"
#include "Listener.h"

// ---------------------------------------------------------------------------
// rpn::Listener
// ---------------------------------------------------------------------------

namespace rpn {

void Listener::op_st0()
{
    op_i64(Registers::R00);
    op_sto();
}

void Listener::op_st1()
{
    op_i64(Registers::R01);
    op_sto();
}

void Listener::op_st2()
{
    op_i64(Registers::R02);
    op_sto();
}

void Listener::op_st3()
{
    op_i64(Registers::R03);
    op_sto();
}

void Listener::op_st4()
{
    op_i64(Registers::R04);
    op_sto();
}

void Listener::op_st5()
{
    op_i64(Registers::R05);
    op_sto();
}

void Listener::op_st6()
{
    op_i64(Registers::R06);
    op_sto();
}

void Listener::op_st7()
{
    op_i64(Registers::R07);
    op_sto();
}

void Listener::op_st8()
{
    op_i64(Registers::R08);
    op_sto();
}

void Listener::op_st9()
{
    op_i64(Registers::R09);
    op_sto();
}

void Listener::op_rc0()
{
    op_i64(Registers::R00);
    op_rcl();
}

void Listener::op_rc1()
{
    op_i64(Registers::R01);
    op_rcl();
}

void Listener::op_rc2()
{
    op_i64(Registers::R02);
    op_rcl();
}

void Listener::op_rc3()
{
    op_i64(Registers::R03);
    op_rcl();
}

void Listener::op_rc4()
{
    op_i64(Registers::R04);
    op_rcl();
}

void Listener::op_rc5()
{
    op_i64(Registers::R05);
    op_rcl();
}

void Listener::op_rc6()
{
    op_i64(Registers::R06);
    op_rcl();
}

void Listener::op_rc7()
{
    op_i64(Registers::R07);
    op_rcl();
}

void Listener::op_rc8()
{
    op_i64(Registers::R08);
    op_rcl();
}

void Listener::op_rc9()
{
    op_i64(Registers::R09);
    op_rcl();
}

void Listener::op_rnd()
{
    op_i64(Registers::R30);
    op_rcl();
}

void Listener::op_now()
{
    op_i64(Registers::R31);
    op_rcl();
}

void Listener::op_fib()
{
    op_dup();
    op_i64(Registers::R20);
    op_sto();
    op_add();
    op_i64(Registers::R20);
    op_rcl();
    op_xch();
}

void Listener::op_run()
{
    throw std::runtime_error("op_run() is not implemented");
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
