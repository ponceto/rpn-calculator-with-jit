/*
 * Listener.h - Copyright (c) 2023 - Olivier Poncet
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
#ifndef __RPN_Listener_h__
#define __RPN_Listener_h__

// ---------------------------------------------------------------------------
// rpn::Listener
// ---------------------------------------------------------------------------

namespace rpn {

class Listener
{
public: // public interface
    Listener() = default;

    virtual ~Listener() = default;

    virtual void op_nop() = 0;

    virtual void op_i64(const int64_t operand) = 0;

    virtual void op_top() = 0;

    virtual void op_pop() = 0;

    virtual void op_clr() = 0;

    virtual void op_dup() = 0;

    virtual void op_xch() = 0;

    virtual void op_sto() = 0;

    virtual void op_rcl() = 0;

    virtual void op_abs() = 0;

    virtual void op_neg() = 0;

    virtual void op_add() = 0;

    virtual void op_sub() = 0;

    virtual void op_mul() = 0;

    virtual void op_div() = 0;

    virtual void op_mod() = 0;

    virtual void op_cpl() = 0;

    virtual void op_and() = 0;

    virtual void op_ior() = 0;

    virtual void op_xor() = 0;

    virtual void op_shl() = 0;

    virtual void op_shr() = 0;

    virtual void op_inc() = 0;

    virtual void op_dec() = 0;

    virtual void op_hlt() = 0;

    virtual void op_st0();

    virtual void op_st1();

    virtual void op_st2();

    virtual void op_st3();

    virtual void op_st4();

    virtual void op_st5();

    virtual void op_st6();

    virtual void op_st7();

    virtual void op_st8();

    virtual void op_st9();

    virtual void op_rc0();

    virtual void op_rc1();

    virtual void op_rc2();

    virtual void op_rc3();

    virtual void op_rc4();

    virtual void op_rc5();

    virtual void op_rc6();

    virtual void op_rc7();

    virtual void op_rc8();

    virtual void op_rc9();

    virtual void op_rnd();

    virtual void op_now();

    virtual void op_fib();

    virtual void op_run();
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __RPN_Listener_h__ */
