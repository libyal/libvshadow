/*
 * The internal extern definition
 *
 * Copyright (C) 2011-2026, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBVSHADOW_INTERNAL_EXTERN_H )
#define _LIBVSHADOW_INTERNAL_EXTERN_H

#include <common.h>

#if !defined( __CYGWIN__ ) && !defined( _WIN32 ) && defined( __has_attribute )
#if __has_attribute( visibility )
#define LIBVSHADOW_INTERNAL	__attribute__((visibility("hidden"))) extern

#else
#define LIBVSHADOW_INTERNAL	extern

#endif /* __has_attribute( visibility ) */
#else
#define LIBVSHADOW_INTERNAL	extern

#endif /* !defined( __CYGWIN__ ) && !defined( _WIN32 ) && defined( __has_attribute ) */

/* Define HAVE_LOCAL_LIBVSHADOW for local use of libvshadow
 */
#if !defined( HAVE_LOCAL_LIBVSHADOW )

#include <libvshadow/extern.h>

#else
#define LIBVSHADOW_EXTERN		/* extern */
#define LIBVSHADOW_EXTERN_VARIABLE	LIBVSHADOW_INTERNAL

#endif /* !defined( HAVE_LOCAL_LIBVSHADOW ) */

#endif /* !defined( _LIBVSHADOW_INTERNAL_EXTERN_H ) */

