/*
 * Date and time functions
 *
 * Copyright (C) 2011-2022, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _PYVSHADOW_DATETIME_H )
#define _PYVSHADOW_DATETIME_H

#include <common.h>
#include <types.h>

#include "pyvshadow_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

PyObject *pyvshadow_datetime_new_from_time_elements(
           uint16_t year,
           uint64_t number_of_days,
           uint8_t hours,
           uint8_t minutes,
           uint8_t seconds,
           uint32_t micro_seconds );

PyObject *pyvshadow_datetime_new_from_fat_date_time(
           uint32_t fat_date_time );

PyObject *pyvshadow_datetime_new_from_filetime(
           uint64_t filetime );

PyObject *pyvshadow_datetime_new_from_floatingtime(
           uint64_t floatingtime );

PyObject *pyvshadow_datetime_new_from_hfs_time(
           uint32_t hfs_time );

PyObject *pyvshadow_datetime_new_from_posix_time(
           int64_t posix_time );

PyObject *pyvshadow_datetime_new_from_posix_time_in_micro_seconds(
           int64_t posix_time );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSHADOW_DATETIME_H ) */

