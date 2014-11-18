#ifndef STLV_H
#define STLV_H
#include <stdint.h>

typedef uint16_t tlv_tag_t;
typedef uint8_t  tlv_len_t;
#define STLV_OVERHEAD	sizeof(tlv_tag_t) + sizeof(tlv_len_t)

typedef struct __attribute__((packed))
{
	tlv_tag_t tag;
	tlv_len_t length;
	char value[128];
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
