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
typedef uint16_t tlv_tag_t;

//! The type to be used for the length.
typedef uint8_t  tlv_len_t;

//! A castable tag-length-value type. This is used to calculate serialization
//! and offsets, but can also be used to directly write tlv structures. Care
//! should be taken for word alignment since this is a packed structure.
typedef struct __attribute__((packed))
{
	tlv_tag_t tag;
	tlv_len_t length;
	char value[256];
} stlv_t;

// TLV Indexing
void		stlv_next(void **p_tlv_chain);

// TLV Read
tlv_tag_t	stlv_get_tag(const void *p_tlv);
tlv_len_t	stlv_get_length(const void *p_tlv);
void*		stlv_get_raw_value(const void *p_tlv);
void		stlv_copy_value(const void *p_tlv, void *p_out_buffer);

// TLV Write
void		stlv_compose(void **p_tlv_chain, tlv_tag_t p_tag, tlv_len_t p_length, const void *p_value);

#endif
