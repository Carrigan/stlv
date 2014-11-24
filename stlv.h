/**
 *	@brief	The interface definitions for a simple tlv parser and composer.
 *	
 *	See stlv.c for more information and use cases.
 *
 *	Copyright Brian Carrigan 2014.
 *	Distributed under the MIT License. See accompanying file license.txt or copy 
 *	at http://opensource.org/licenses/MIT.
 */

#ifndef STLV_H
#define STLV_H
#include <stdint.h>

//! The type to be used for a tag.
typedef uint16_t stlv_tag_t;

//! The type to be used for the length.
typedef uint16_t  stlv_len_t;

//! Type type to be used as the length of a chain.
typedef uint8_t tlv_chain_len_t;

//! A castable tag-length-value type. This is used to calculate serialization
//! and offsets, but can also be used to directly write tlv structures. Care
//! should be taken for word alignment since this is a packed structure.
typedef struct __attribute__((packed))
{
	stlv_tag_t tag;
	stlv_len_t length;
	char value[256];
} stlv_t;

//! When chaining TLVs, they should be serialized starting with a length entry
//! denoting how many are in the chain. This structure can be cast to begin a
//! parser.
typedef struct __attribute__((packed))
{
	tlv_chain_len_t length;
	stlv_t first_entry;
} stlv_chain_t;

// TLV Indexing
void		stlv_next(void **p_tlv_chain);

// TLV Read
stlv_tag_t	stlv_get_tag(const void *p_tlv);
stlv_len_t	stlv_get_length(const void *p_tlv);
void*		stlv_get_raw_value(const void *p_tlv);
void		stlv_copy_value(const void *p_tlv, void *p_out_buffer);

// TLV Write
void		stlv_compose(void **p_tlv_chain, stlv_tag_t p_tag, stlv_len_t p_length, const void *p_value);

#endif
