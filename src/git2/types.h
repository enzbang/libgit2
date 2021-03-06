/*
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2,
 * as published by the Free Software Foundation.
 *
 * In addition to the permissions in the GNU General Public License,
 * the authors give you unlimited permission to link the compiled
 * version of this file into combinations with other programs,
 * and to distribute those combinations without any restriction
 * coming from the use of this file.  (The General Public License
 * restrictions do apply in other respects; for example, they cover
 * modification of the file, and distribution when not linked into
 * a combined executable.)
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#ifndef INCLUDE_git_types_h__
#define INCLUDE_git_types_h__

/**
 * @file git2/types.h
 * @brief libgit2 base & compatibility types
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL

/**
 * Cross-platform compatibility types for off_t / time_t
 *
 * NOTE: This needs to be in a public header so that both the library
 * implementation and client applications both agree on the same types.
 * Otherwise we get undefined behavior.
 *
 * Use the "best" types that each platform provides. Currently we truncate
 * these intermediate representations for compatibility with the git ABI, but
 * if and when it changes to support 64 bit types, our code will naturally
 * adapt.
 * NOTE: These types should match those that are returned by our internal
 * stat() functions, for all platforms.
 */
#include <sys/types.h>

#if defined(_MSC_VER)

typedef __int64 git_off_t;
typedef __time64_t git_time_t;

#elif defined(__MINGW32__)

typedef off64_t git_off_t;
typedef time_t git_time_t;

#else  /* POSIX */

/* 
 * Note: Can't use off_t since if a client program includes <sys/types.h>
 * before us (directly or indirectly), they'll get 32 bit off_t in their client
 * app, even though /we/ define _FILE_OFFSET_BITS=64.
 */
typedef long long git_off_t;
typedef time_t git_time_t;

#endif


/** Basic type (loose or packed) of any Git object. */
typedef enum {
	GIT_OBJ_ANY = -2,		/**< Object can be any of the following */
	GIT_OBJ_BAD = -1,       /**< Object is invalid. */
	GIT_OBJ__EXT1 = 0,      /**< Reserved for future use. */
	GIT_OBJ_COMMIT = 1,     /**< A commit object. */
	GIT_OBJ_TREE = 2,       /**< A tree (directory listing) object. */
	GIT_OBJ_BLOB = 3,       /**< A file revision object. */
	GIT_OBJ_TAG = 4,        /**< An annotated tag object. */
	GIT_OBJ__EXT2 = 5,      /**< Reserved for future use. */
	GIT_OBJ_OFS_DELTA = 6,  /**< A delta, base is given by an offset. */
	GIT_OBJ_REF_DELTA = 7,  /**< A delta, base is given by object id. */
} git_otype;

/** An open object database handle. */
typedef struct git_odb git_odb;

/** A custom backend in an ODB */
typedef struct git_odb_backend git_odb_backend;

/**
 * Representation of an existing git repository,
 * including all its object contents
 */
typedef struct git_repository git_repository;

/** Representation of a generic object in a repository */
typedef struct git_object git_object;

/** Representation of an in-progress walk through the commits in a repo */
typedef struct git_revwalk git_revwalk;

/** Parsed representation of a tag object. */
typedef struct git_tag git_tag;

/** In-memory representation of a blob object. */
typedef struct git_blob git_blob;

/** Parsed representation of a commit object. */
typedef struct git_commit git_commit;

/** Representation of each one of the entries in a tree object. */
typedef struct git_tree_entry git_tree_entry;

/** Representation of a tree object. */
typedef struct git_tree git_tree;

/** Memory representation of an index file. */
typedef struct git_index git_index;

/** Time in a signature */
typedef struct git_time {
	time_t time; /** time in seconds from epoch */
	int offset; /** timezone offset, in minutes */
} git_time;

/** An action signature (e.g. for committers, taggers, etc) */
typedef struct git_signature {
	char *name; /** full name of the author */
	char *email; /** email of the author */
	git_time when; /** time when the action happened */
} git_signature;

/** In-memory representation of a reference. */
typedef struct git_reference git_reference;

/** Basic type of any Git reference. */
typedef enum {
	GIT_REF_INVALID = -1, /** Invalid reference */
	GIT_REF_OID = 1, /** A reference which points at an object id */
	GIT_REF_SYMBOLIC = 2, /** A reference which points at another reference */
} git_rtype;

/** @} */
GIT_END_DECL

#endif
