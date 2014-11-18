#include <stddef.h>
#include <string.h>
#include "stlv.h"

void stlv_next(void **p_tlv_chain)
{
	tlv_len_t *current_length = (tlv_len_t *)(*p_tlv_chain + offsetof(stlv_t, length));
	*p_tlv_chain += *current_length + STLV_OVERHEAD;
}

tlv_tag_t stlv_get_tag(const void *p_tlv)
{
	tlv_tag_t tag_return;
	void *tag_location = (void *)p_tlv + offsetof(stlv_t, tag);
	memcpy(&tag_return, tag_location, sizeof(tlv_tag_t));
	return tag_return;
}

tlv_len_t stlv_get_length(const void *p_tlv)
{
	tlv_len_t length_return;
	void *length_location = (void *)p_tlv + offsetof(stlv_t, length);
	memcpy(&length_return, length_location, sizeof(tlv_len_t));
	return length_return;
}

void *stlv_get_raw_value(const void *p_tlv)
{
	return ((void *)p_tlv + STLV_OVERHEAD);
}

void stlv_copy_value(const void *p_tlv, void *p_out_buffer)
{
	tlv_len_t length = stlv_get_length(p_tlv);
	void *value = stlv_get_raw_value(p_tlv);
	memcpy(p_out_buffer, value, length);
}

void stlv_compose(void **p_tlv_chain, tlv_tag_t p_tag, tlv_len_t p_length, const void *p_value)
{
	memcpy(*p_tlv_chain + offsetof(stlv_t, tag), &p_tag, sizeof(tlv_tag_t));
	memcpy(*p_tlv_chain + offsetof(stlv_t, length), &p_length, sizeof(tlv_len_t));
	memcpy(*p_tlv_chain + offsetof(stlv_t, value), p_value, p_length);
	*p_tlv_chain += STLV_OVERHEAD + p_length;
}
