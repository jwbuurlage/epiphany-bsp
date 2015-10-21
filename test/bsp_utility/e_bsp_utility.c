/*
This file is part of the Epiphany BSP library.

Copyright (C) 2014-2015 Buurlage Wits
Support e-mail: <info@buurlagewits.nl>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License (LGPL)
as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
and the GNU Lesser General Public License along with this program,
see the files COPYING and COPYING.LESSER. If not, see
<http://www.gnu.org/licenses/>.
*/

#include <e_bsp.h>
#include "../common.h"

int main() {
    bsp_begin();

    EBSP_MSG_ORDERED("%i", 0);
    // expect_for_pid: ("0")

    // We test if we can use many barriers stably
    for (int i = 0; i < 1000; ++i)
        ebsp_barrier();

    EBSP_MSG_ORDERED("%i", 1);
    // expect_for_pid: ("1")

    for (int i = 0; i < 1000; ++i)
        ebsp_barrier();

    EBSP_MSG_ORDERED("%i %i %i", 1, 2, 3);
    // expect_for_pid: ("1 2 3")

    bsp_end();
    return 0;
}