/**
 *	@brief	The implementation of a simple tlv parser and composer.
 *
 *	Copyright Brian Carrigan 2014.
 *	Distributed under the MIT License. See accompanying file license.txt or copy 
 *	at http://opensource.org/licenses/MIT.
 */

#include <stddef.h>
#include <string.h>
#include "stlv.h"

#define STLV_OVERHEAD	sizeof(stlv_tag_t) + sizeof(stlv_len_t)

/**
 *	@brief	A function to index the pointer of a tag-length-value struct pointer, 
 *			p_tlv_chain, to the beginning of the next tlv in the chain.
 */
void stlv_next(void **p_tlv_chain)
{
	stlv_len_t *current_length = (stlv_len_t *)(*p_tlv_chain + offsetof(stlv_t, length));
	*p_tlv_chain += *current_length + STLV_OVERHEAD;
}

/**
 *	@brief	A function to retrieve the tag from tlv data block p_tlv. 
 *
 *	This function is word boundary safe.
 */
stlv_tag_t stlv_get_tag(const void *p_tlv)
{
	stlv_tag_t tag_return;
	void *tag_location = (void *)p_tlv + offsetof(stlv_t, tag);
	memcpy(&tag_return, tag_location, sizeof(stlv_tag_t));
	return tag_return;
}

/**
 *	@brief	A function to retrieve the length of the value of tlv data block p_tlv. 
 *	
 *	This function is word boundary safe.
 */
stlv_len_t stlv_get_length(const void *p_tlv)
{
	stlv_len_t length_return;
	void *length_location = (void *)p_tlv + offsetof(stlv_t, length);
	memcpy(&length_return, length_location, sizeof(stlv_len_t));
	return length_return;
}

/**
 *	@brief	Retrieve a pointer to the raw value block of p_tlv. 
 *
 *	This is intended for reading out or parsing string data without making a copy 
 *	of the data. This pointer is not guarenteed to be word aligned, so care should
 *	be taken when accessing it.
 */
void *stlv_get_raw_value(const void *p_tlv)
{
	return ((void *)p_tlv + STLV_OVERHEAD);
}

/**
 *	@brief	Copy the value of tlv block p_tlv into the dataspace given by p_out_buffer.
 *			
 *	The amount of data copied out is determined by the length entry of the tlv block.
 *	This function is intended to copy data in a word boundary safe mannor.
 */
void stlv_copy_value(const void *p_tlv, void *p_out_buffer)
{
	stlv_len_t length = stlv_get_length(p_tlv);
	void *value = stlv_get_raw_value(p_tlv);
	memcpy(p_out_buffer, value, length);
}

/**
 *	@brief	Compose a single tlv entry into the buffer pointed to by p_tlv_chain. 
 *			
 *	When finished, p_tlv_chain will be indexed to the next available byte in the 
 *	buffer, making this callable multiple times in a row to create a chain.
 */
void stlv_compose(void **p_tlv_chain, stlv_tag_t p_tag, stlv_len_t p_length, const void *p_value)
{
	memcpy(*p_tlv_chain + offsetof(stlv_t, tag), &p_tag, sizeof(stlv_tag_t));
	memcpy(*p_tlv_chain + offsetof(stlv_t, length), &p_length, sizeof(stlv_len_t));
	memcpy(*p_tlv_chain + offsetof(stlv_t, value), p_value, p_length);
	*p_tlv_chain += STLV_OVERHEAD + p_length;
}
