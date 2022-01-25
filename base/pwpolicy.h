/* Copyright (C) 2013-2022 Greenbone Networks GmbH
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/**
 * @file
 * @brief Protos and data structures for pwpolicy checking.
 *
 * This file contains the protos for \ref pwpolicy.c
 */

#ifndef _GVM_PWPOLICY_H
#define _GVM_PWPOLICY_H

char *
gvm_validate_password (const char *, const char *);
void
gvm_disable_password_policy (void);

#endif /*_GVM_PWPOLICY_H*/
